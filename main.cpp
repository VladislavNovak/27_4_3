#include <iostream>
#include <vector>
#include "constance.h"
#include "utilities.h"
#include "Worker.h"
#include "Manager.h"
#include "Supervisor.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;


int main() {
    std::vector<std::string> menuTitles = { "exit", "print", "task" };

    // initial
    cout << "---Initial---" << endl;
    auto* supervisor = new Supervisor(putLineString("Enter name of supervisor"));
    int teamsCount = putNumeric({1, 10},{}, "count of teams");

    for (int j = 0; j < teamsCount; ++j) {

        cout << "---Teams #" << j << "---" << endl;
        auto* manager = new Manager(putLineString("Enter name of manager"), j);

        int workerCount = putNumeric({1, 50},{}, "count of workers");

        for (int i = 0; i < workerCount; ++i) {
            manager->addChild(new Worker(putLineString("Enter name of worker")));
        }

        supervisor->addChild(manager);
    }

    // end initial

    while (true) {
        std::cout << "--- Main menu ---" << std::endl;
        int command = selectMenuItem(menuTitles);

        if (command == static_cast<int>(Menu::EXIT)) {
            std::cout << "Menu --> exit mode -->" << std::endl;
            delete supervisor;
            supervisor = nullptr;
            break;
        }
        else if (command == static_cast<int>(Menu::PRINT)) {
            std::cout << "Menu --> print mode -->" << std::endl;
            supervisor->printChildren();
        }
        else if (command == static_cast<int>(Menu::TASK)) {
            std::cout << "Menu --> task mode -->" << std::endl;
            // Задаем новую команду
            int task = putNumeric({},{}, "new task");
            bool isWorkerAvailable = supervisor->setTask(task);
            // Если работников свободных не осталось, удаляем пункт меню
            if (!isWorkerAvailable) { removeKeyFromVector(menuTitles[static_cast<int>(Menu::TASK)], menuTitles); }
        }
    }

    cout << "THE END!" << endl;

    return 0;
}
