#include "Manager.h"

Manager::Manager(const string &inName, int inNumber): Base(inName) {
    number = inNumber;
}
Manager::~Manager() {
    if (!children.empty()) {
        for (auto &item : children) {
            delete item;
            item = nullptr;
        }
        children.clear();
    }
}
void Manager::setParent(Supervisor* supervisor) { parent = supervisor; }

// Передает команду элементу. Возвращает оставшееся количество свободных работников
int Manager::setTask(int task) {
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

void Manager::addChild(Worker* b) {
    b->setParent(this);
    children.emplace_back(b);
}

void Manager::printChildren(int indent) {
    if (!children.empty()) {
        cout << std::setw(indent) << this->name << "(Manager):" << endl;
        for (auto &worker: children) {
            cout << std::setw(indent * 2) << worker->getName() << "(Worker)";
            if (worker->getTaskType() == TaskType::NONE) { cout << " without task" << endl; }
            else { cout << " with task " << tasksTitles[static_cast<int>(worker->getTaskType())] << endl; }
        }
    }
}

