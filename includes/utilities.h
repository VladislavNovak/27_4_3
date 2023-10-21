#ifndef INC_27_4_3_UTILITIES_H
#define INC_27_4_3_UTILITIES_H

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <limits>

template<typename T, typename N>
bool isIncludes(const T &range, const N &item) {
    return std::any_of(range.begin(),
                       range.end(),
                       [&item](const N &c) { return c == item; });
}

int putInput() {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input is invalid. Please try again:";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
}

template<typename T>
std::stringstream joinListToStream(const std::vector<T> &list, const char* delim = ", ") {
    std::stringstream ss;
    std::copy(list.begin(), std::prev(list.end()), std::ostream_iterator<T>(ss, delim));
    if (!list.empty()) { ss << list.back(); }
    return ss;
}

// Любое число - если ничего не передать в массиве.
// В диапазоне - если передать два числа (меньшее и большее) в массиве.
// В перечне - если передать массив НЕ из двух элементов или из двух, в котором первый элемент больше второго
// За исключением - если добавить перечень во второй аргумент

int putNumeric(const std::vector<int> &list = {}, const std::vector<int> &excludedList = {}, const std::string &msg = "") {
    bool isRange = (list.size() == 2) && (list[0] < list[1]);
    bool isList = !list.empty() && (list.size() != 2 || ((list.size() == 2) && (list[0] > list[1])));
    bool isExcluded = !excludedList.empty();

    std::cout << "Enter";
    if (isRange) std::cout << " (in the range "  << joinListToStream(list, " - ").str() << ")";
    else if (isList) std::cout << " (in a list of " << joinListToStream(list).str() << ")";
    if (isExcluded) std::cout << " (excluded " << joinListToStream(excludedList).str() << ")";
    std::cout << (msg.length() ? " " + msg + ":" : ":");

    int userInput;

    while (true) {
        userInput = putInput();

        bool isTrouble = false;
        if (isRange && (userInput < list[0] || userInput > list[1])) isTrouble = true;
        if (isList && !isIncludes(list, userInput)) isTrouble = true;
        if (isExcluded && isIncludes(excludedList, userInput)) isTrouble = true;

        if (!isTrouble) { break; }
        std::cout << "Error.Try again:";
    }
    return userInput;
}

std::string putLineString(const std::string &msg) {
    std::cout << msg << ":";
    while (true) {
        std::string userLineString;
        std::getline(std::cin >> std::ws, userLineString);

        if (userLineString.empty()) {
            std::cout << "The string cannot be empty. Try again:";
            continue;
        }

        return userLineString;
    }
}

#endif //INC_27_4_3_UTILITIES_H
