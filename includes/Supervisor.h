#ifndef INC_27_4_3_SUPERVISOR_H
#define INC_27_4_3_SUPERVISOR_H

#include <vector>
#include "Base.h"
#include "Manager.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Base;
class Manager;

class Supervisor: public Base {
    std::vector<Manager*> children;
public:
    explicit Supervisor(const string &inName);

    ~Supervisor();

    void addChild(Manager* b);

    // Получает начальную задачу. Возвращает true, если есть хоть один незанятый worker
    bool setTask(int task);

    void printChildren();
};

#endif //INC_27_4_3_SUPERVISOR_H
