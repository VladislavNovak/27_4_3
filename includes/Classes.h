#ifndef INC_27_4_3_CLASSES_H
#define INC_27_4_3_CLASSES_H

#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Base {
    string name{};
    explicit Base(const string &inName) { name = inName; }
};

struct Supervisor;
struct Manager;

struct Worker: public Base {
    Manager* parent = nullptr;
    explicit Worker(const string &inName): Base(inName) {}
};

struct Manager: public Base {
    int number{};
    Supervisor* parent = nullptr;
    vector<Worker*> children;
    explicit Manager(const string &inName, int inNumber): Base(inName) {
        number = inNumber;
    }
    ~Manager() {
        if (!children.empty()) {
            for (auto &item : children) {
                delete item;
                item = nullptr;
            }
            children.clear();
        }
    }
    void addChild(Worker* b) {
        b->parent = this;
        children.emplace_back(b);
    }
    void createChild(const std::string &inName) {
        auto* item = new Worker(inName);
        item->parent = this;
        children.emplace_back(item);
    }
    void printChildren(int indent = 0) {
        if (!children.empty()) {
            cout << std::setw(indent) << this->name << "(Manager):" << endl;
            for (auto &item: children) {
                cout << std::setw(indent * 2) << item->name << "(Worker)" << endl;
            }
        }
    }
};

struct Supervisor: public Base {
    vector<Manager*> children;
    explicit Supervisor(const string &inName): Base(inName) {}
    ~Supervisor() {
        if (!children.empty()) {
            for (auto &item : children) {
                delete item;
                item = nullptr;
            }
            children.clear();
        }
    }
    void addChild(Manager* b) {
        b->parent = this;
        children.emplace_back(b);
    }
    void printChildren() {
        if (!children.empty()) {
            cout << this->name << "(Supervisor):" << endl;
            for (auto &item: children) {
                item->printChildren(4);
            }
        }
    }
};

#endif //INC_27_4_3_CLASSES_H
