#ifndef UNTITLED8_TASKPROCESSING_H
#define UNTITLED8_TASKPROCESSING_H
#include <vector>
#include <TaskManager.h>
class TaskProcessing {
private:

public:
    void addTask() const;
    void viewAllTasks() const;
    void viewTaskDetails() const;
    void editTask() const;
    void deleteTask() const;
    void completeTask() const;
    static int getCorrectResponse(int left, int right);
    static std::string formatDateTime(const std::tm& datetime);
    const char* dbPath = "/Users/nazarzakrevskij/CLionProjects/TaskManagerProject/UsersInfo.db";
    tm validDateTime();
};

#endif //UNTITLED8_TASKPROCESSING_H
