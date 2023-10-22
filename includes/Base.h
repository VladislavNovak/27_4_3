#ifndef INC_27_4_3_BASE_H
#define INC_27_4_3_BASE_H

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
    // Имя будет назначено для наследующих классов (Worker, Manager, Supervisor)
    string name{};
public:
    explicit Base(const string &inName);
};

#endif //INC_27_4_3_BASE_H
