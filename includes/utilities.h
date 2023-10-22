#ifndef INC_27_4_3_UTILITIES_H
#define INC_27_4_3_UTILITIES_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <limits>

template<typename T, typename N>
bool isIncludes(const T &range, const N &item);

int putInput();

template<typename T>
std::stringstream joinListToStream(const std::vector<T> &list, const char* delim = ", ");

// Любое число - если ничего не передать в массиве.
// В диапазоне - если передать два числа (меньшее и большее) в массиве.
// В перечне - если передать массив НЕ из двух элементов или из двух, в котором первый элемент больше второго
// За исключением - если добавить перечень во второй аргумент
int putNumeric(const std::vector<int> &list = {}, const std::vector<int> &excludedList = {}, const std::string &msg = "");

std::string putLineString(const std::string &msg);

int selectMenuItem(const std::vector<std::string> &list, const std::string &msg = "Choose between options");

template<typename T>
int findKeyIndexInVector(const T &key, const std::vector<T> &list) {
    const int NOT_FOUND = -1;
    auto it = std::find_if(list.cbegin(), list.cend(), [key](const T &i){ return i == key; });

    if (it != list.cend()) {
        return (int)std::distance(list.cbegin(), it);
    }

    return NOT_FOUND;
}

template<typename T>
bool removeKeyFromVector(const T &key, std::vector<T> &list) {
    auto foundIndex = findKeyIndexInVector(key, list);
    if (foundIndex == -1) return false;

    list.erase(list.begin() + foundIndex);

    return true;
}

int getRandomIntInRange(int from, int to);

#endif //INC_27_4_3_UTILITIES_H
