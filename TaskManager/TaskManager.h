// Task.h
#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

class Task {
private:
    std::string title;
    std::string description;
    std::tm start_date;
    std::tm end_date;
    bool completed;

public:
    Task(std::string title, std::string description, std::tm start_date, std::tm end_date, bool completed);

    std::string getTitle() const;
    void setTitle(const std::string &title);
    std::string getDescription() const;
    void setDescription(const std::string &description);
    const tm getStartDate() const;
    void setStartDate(const std::tm &start_date);
    const tm getEndDate() const;
    void setEndDate(const std::tm &end_date);
    bool isCompleted() const;
    void setCompleted(bool completed);
    void printTask() const;
};

#endif // TASK_H
