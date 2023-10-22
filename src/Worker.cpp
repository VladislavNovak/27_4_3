#include "Worker.h"

Worker::Worker(const string &inName) : Base(inName) {}

TaskType Worker::getTaskType() { return taskType; }

void Worker::setTaskType(TaskType inType) { taskType = inType; }

std::string Worker::getName() { return name; }

void Worker::setParent(Manager* manager) { parent = manager; }
