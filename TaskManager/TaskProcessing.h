#ifndef UNTITLED8_TASKPROCESSING_H
#define UNTITLED8_TASKPROCESSING_H
#include <vector>
#include <TaskManager.h>
class TaskProcessing {
private:

public:
    void addTask();
    void viewAllTasks();
    void viewTaskDetails();
    void editTask();
    void deleteTask();
    void completeTask();
    int getCorrectResponse(int left, int right);
    std::string formatDateTime(const std::tm& datetime);
    const char* dbPath = "/Users/nazarzakrevskij/CLionProjects/TaskManagerProject/UsersInfo.db";
};

#endif //UNTITLED8_TASKPROCESSING_H
