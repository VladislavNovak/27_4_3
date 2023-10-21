#ifndef INC_27_4_3_CONSTANCE_H
#define INC_27_4_3_CONSTANCE_H

#include <iostream>
#include <vector>

enum class Menu { TASK, PRINT, EXIT };
std::vector<std::string> menuTitles = { "task", "print", "exit" };

enum class TaskType { A, B, C, NONE };
std::vector<char> tasksTitles = { 'A', 'B', 'C' };

#endif //INC_27_4_3_CONSTANCE_H
