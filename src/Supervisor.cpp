#include "Supervisor.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;


Supervisor::Supervisor(const string &inName): Base(inName) {}

Supervisor::~Supervisor() {
    if (!children.empty()) {
        for (auto &item : children) {
            delete item;
            item = nullptr;
        }
        children.clear();
    }
}

void Supervisor::addChild(Manager* b) {
    b->setParent(this);
    children.emplace_back(b);
}

// Получает начальную задачу. Возвращает true, если есть хоть один незанятый worker
bool Supervisor::setTask(int task) {
    int availableWorkers = 0;

    if (!children.empty()) {
        for (const auto &manager : children) {
            availableWorkers += manager->setTask(task);
        }
    }

    cout << "Available workers: " << availableWorkers << endl;

    return availableWorkers;
}

void Supervisor::printChildren() {
    if (!children.empty()) {
        cout << this->name << "(Supervisor):" << endl;
        for (auto &item: children) {
            item->printChildren(4);
        }
    }
}