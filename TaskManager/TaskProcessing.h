#ifndef UNTITLED8_TASKPROCESSING_H
#define UNTITLED8_TASKPROCESSING_H
#include <vector>
#include <TaskManager.h>

class TaskProcessing {
private:

public:
    void addTask(std::vector<Task> &arr);
    void viewAllTasks();
    void viewTaskDetails();
    void editTask();
    void deleteTask();
    void completeTask();
};


#endif //UNTITLED8_TASKPROCESSING_H
