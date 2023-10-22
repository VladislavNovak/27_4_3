#ifndef INC_27_4_3_MANAGER_H
#define INC_27_4_3_MANAGER_H

#include <vector>
#include "constance.h"
#include "Base.h"
#include "Worker.h"
#include "Supervisor.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Base;
class Worker;
class Supervisor;

class Manager: public Base {
    int number{};
    Supervisor* parent = nullptr;
    vector<Worker*> children;
    // Типы работ для Worker:
    std::vector<char> tasksTitles = { 'A', 'B', 'C' };
public:
    explicit Manager(const string &inName, int inNumber);

    ~Manager();

    void setParent(Supervisor* supervisor);

    // Передает команду элементу. Возвращает оставшееся количество свободных работников
    int setTask(int task);

    void addChild(Worker* b);

    void printChildren(int indent = 0);
};


#endif //INC_27_4_3_MANAGER_H
