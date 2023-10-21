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

struct Base {
    string name{};
    explicit Base(const string &inName) { name = inName; }
};

struct Supervisor;
struct Manager;

struct Worker: public Base {
    TaskType taskType = TaskType::NONE;
    Manager* parent = nullptr;
    explicit Worker(const string &inName): Base(inName) {}
};

struct Manager: public Base {
    int number{};
    Supervisor* parent = nullptr;
    vector<Worker*> children;
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
    // Передает команду элементу. Возвращает оставшееся количество свободных работников
    int setTask(int task) {
        cout << "Manager " << this->name << "(group #" << this->number << ")"  << " got a task (" << task << ")" << endl;
        // Количество ещё доступных рабочих
        int availableWorkersCount = 0;
        for (const auto &item : children) {
            if (item->taskType == TaskType::NONE) { ++availableWorkersCount; }
        }
        // Если рабочих нет, выходим
        if (!availableWorkersCount) { return 0; }
        // В противном случае - даём случайному количеству незанятых работников новые задачи:
        std::srand(task + this->number);
        int taskCount = getRandomIntInRange(1, availableWorkersCount);

        for (auto &worker : children) {
            if (worker->taskType == TaskType::NONE) {
                // Генерируем и даём задачу
                int realTask = getRandomIntInRange(0, (int)TaskType::C);
                worker->taskType = static_cast<TaskType>(realTask);
                cout << "Worker " << worker->name << " got task #" << tasksTitles[realTask] << endl;
            }
        }
        // Если будет 0, значит свободных рабочих больше нет
        return (availableWorkersCount - taskCount);
    }
    void addChild(Worker* b) {
        b->parent = this;
        children.emplace_back(b);
    }
    void createChild(const std::string &inName) {
        auto* item = new Worker(inName);
        item->parent = this;
        children.emplace_back(item);
    }
    void printChildren(int indent = 0) {
        if (!children.empty()) {
            cout << std::setw(indent) << this->name << "(Manager):" << endl;
            for (auto &item: children) {
                cout << std::setw(indent * 2) << item->name << "(Worker)" << endl;
            }
        }
    }
};

struct Supervisor: public Base {
    vector<Manager*> children;
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
        b->parent = this;
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
