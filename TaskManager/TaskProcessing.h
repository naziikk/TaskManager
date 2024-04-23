#ifndef UNTITLED8_TASKPROCESSING_H
#define UNTITLED8_TASKPROCESSING_H
#include <vector>
#include <TaskManager.h>
class TaskProcessing {
private:

public:
    void addTask(std::vector<Task> &arr);
    void viewAllTasks(std::vector<Task> arr);
    void viewTaskDetails(std::vector<Task> arr);
    void editTask(std::vector<Task> &arr);
    std::vector<Task> deleteTask(std::vector<Task> &arr);
    std::vector<Task> completeTask(std::vector<Task> &arr);
    int getCorrectResponse(int left, int right);
};

#endif //UNTITLED8_TASKPROCESSING_H
