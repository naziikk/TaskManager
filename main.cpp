#include "TaskManager/TaskManager.h"
#include "TaskManager/TaskProcessing.h"
#include "HelperMethods.h"
#include <iostream>
#include <vector>

class Program {
public:
    static int main() {
        std::vector<Task> userTasksInfo;
        HelperMethods helper;
        bool flag = true;
        while (flag) {
            std::cout << "Choose an option:\n"
                         "1. Add a new task.\n"
                         "2. View my tasks.\n"
                         "3. View details of a specific task.\n"
                         "4. Modify task parameters.\n"
                         "5. Delete a task.\n"
                         "6. Mark a task as completed.\n"
                         "7. Exit.\n";
            int response = helper.getCorrectInput(1, 7);
            switch (response) {
                case 1:

                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:

                    break;
                case 6:

                    break;
                case 7:
                    flag = false;
                    break;
                default:
                    std::cout << "Wrong enter!\n";
                    break;
            }
        }
        return 0;
    }
};

int main() {
    return Program::main();
}
