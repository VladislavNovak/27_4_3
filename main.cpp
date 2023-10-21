#include <iostream>
#include <vector>
#include "includes/utilities.h"
#include "includes/Classes.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    auto* supervisor = new Supervisor(putLineString("Enter name of supervisor"));
    int teamsCount = putNumeric({1, 10},{}, "count of teams");

    for (int j = 0; j < teamsCount; ++j) {

        cout << "----- Teams #" << j << " -----" << endl;
        auto* manager = new Manager(putLineString("Enter name of manager"), j);

        int workerCount = putNumeric({1, 10},{}, "count of workers");

        for (int i = 0; i < workerCount; ++i) {
            manager->addChild(new Worker(putLineString("Enter name of worker")));
        }

        supervisor->addChild(manager);
    }

    supervisor->printChildren();
    delete supervisor;

    return 0;
}
