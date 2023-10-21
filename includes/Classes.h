#ifndef INC_27_4_3_CLASSES_H
#define INC_27_4_3_CLASSES_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include "constance.h"
#include "utilities.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Base {
protected:
    string name{};
public:
    explicit Base(const string &inName) { name = inName; }
};

class Supervisor;
class Manager;

class Worker: public Base {
    Manager* parent = nullptr;
    TaskType taskType = TaskType::NONE;
public:
    explicit Worker(const string &inName): Base(inName) {}
    TaskType getTaskType() { return taskType; }
    void setTaskType(TaskType inType) { taskType = inType; }
    std::string getName() { return name; }
    void setParent(Manager* manager) { parent = manager; }
};

class Manager: public Base {
    int number{};
    Supervisor* parent = nullptr;
    vector<Worker*> children;
public:
    explicit Manager(const string &inName, int inNumber): Base(inName) {
        number = inNumber;
    }
    ~Manager() {
        if (!children.empty()) {
            for (auto &item : children) {
                delete item;
                item = nullptr;
            }
            children.clear();
        }
    }
    void setParent(Supervisor* supervisor) { parent = supervisor; }
    // Передает команду элементу. Возвращает оставшееся количество свободных работников
    int setTask(int task) {
        // Количество ещё доступных рабочих
        int availableWorkersCount = 0;
        for (const auto &worker : children) {
            if (worker->getTaskType() == TaskType::NONE) { ++availableWorkersCount; }
        }
        // Если рабочих нет, выходим
        if (!availableWorkersCount) { return 0; }

        // В противном случае - даём случайному количеству незанятых работников новые задачи:
        std::srand(task + this->number);
        int taskCount = getRandomIntInRange(1, availableWorkersCount);

        cout << "Manager " << this->name << "(group #" << this->number << ")"  << " transfer task to:" << endl;

        for (auto &worker : children) {
            if (worker->getTaskType() == TaskType::NONE) {
                // Генерируем и даём задачу
                int realTask = getRandomIntInRange(0, (int)TaskType::C);
                worker->setTaskType(static_cast<TaskType>(realTask));
                cout << " - Worker " << worker->getName() << " got task #" << tasksTitles[realTask] << endl;
                --taskCount;
                --availableWorkersCount;
                if (!taskCount) { break; }
            }
        }
        // Если будет 0, значит свободных рабочих больше нет
        return availableWorkersCount;
    }
    void addChild(Worker* b) {
        b->setParent(this);
        children.emplace_back(b);
    }
    void printChildren(int indent = 0) {
        if (!children.empty()) {
            cout << std::setw(indent) << this->name << "(Manager):" << endl;
            for (auto &worker: children) {
                cout << std::setw(indent * 2) << worker->getName() << "(Worker)";
                if (worker->getTaskType() == TaskType::NONE) { cout << " without task" << endl; }
                else { cout << "with task " << tasksTitles[static_cast<int>(worker->getTaskType())] << endl; }
            }
        }
    }
};

class Supervisor: public Base {
    vector<Manager*> children;
public:
    explicit Supervisor(const string &inName): Base(inName) {}
    ~Supervisor() {
        if (!children.empty()) {
            for (auto &item : children) {
                delete item;
                item = nullptr;
            }
            children.clear();
        }
    }
    void addChild(Manager* b) {
        b->setParent(this);
        children.emplace_back(b);
    }
    // Получает начальную задачу. Возвращает true, если есть хоть один незанятый worker
    bool setTask(int task) {
        int availableWorkers = 0;

        if (!children.empty()) {
            for (const auto &manager : children) {
                availableWorkers += manager->setTask(task);
            }
        }

        cout << "Available workers: " << availableWorkers << endl;

        return availableWorkers;
    }
    void printChildren() {
        if (!children.empty()) {
            cout << this->name << "(Supervisor):" << endl;
            for (auto &item: children) {
                item->printChildren(4);
            }
        }
    }
};

#endif //INC_27_4_3_CLASSES_H
