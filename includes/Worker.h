#ifndef INC_27_4_3_WORKER_H
#define INC_27_4_3_WORKER_H

#include "constance.h"
#include "Base.h"
#include "Manager.h"

class Base;
class Manager;

class Worker : public Base {
    Manager* parent = nullptr;
    TaskType taskType = TaskType::NONE;
public:
    explicit Worker(const string &inName);

    TaskType getTaskType();

    void setTaskType(TaskType inType);

    std::string getName();

    void setParent(Manager* manager);
};

#endif //INC_27_4_3_WORKER_H
