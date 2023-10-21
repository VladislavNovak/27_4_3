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
    Supervisor* parent = nullptr;
    vector<Worker*> children;
    explicit Manager(const string &inName): Base(inName) {}
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
            cout << std::setw(indent) << this->name << ":" << endl;
            for (auto &item: children) {
                cout << std::setw(indent + 2) << item->name << endl;
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
            cout << this->name << ":" << endl;
            for (auto &item: children) {
                item->printChildren(4);
            }
        }
    }
};



int main() {
    auto* itemD = new Supervisor("D");

    auto* itemB1 = new Worker("B1");
    auto* itemB2 = new Worker("B2");
    auto* itemC1 = new Manager("C1");
    itemC1->addChild(itemB1);
    itemC1->addChild(itemB2);
    itemC1->createChild("B3");
    itemC1->createChild("B4");

    auto* itemC2 = new Manager("C2");
    itemC2->createChild("B5");
    itemC2->createChild("B6");
    itemD->addChild(itemC1);
    itemD->addChild(itemC2);
    itemD->printChildren();
    delete itemD;

    return 0;
}
