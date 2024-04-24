// Task.cpp
#include "TaskManager.h"
#include <iostream>
#include <iomanip>

Task::Task(std::string title, std::string description, std::tm start_date, std::tm end_date, bool completed) :
        title(title), description(description), start_date(start_date), end_date(end_date), completed(completed) {}

std::string Task::getTitle() const {
    return title;
}

void Task::setTitle(const std::string &title) {
    this->title = title;
}

std::string Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string &description) {
    this->description = description;
}

const tm Task::getStartDate() const {
    return start_date;
}

void Task::setStartDate(const std::tm &start_date) {
    this->start_date = start_date;
}

const tm Task::getEndDate() const {
    return end_date;
}

void Task::setEndDate(const std::tm &end_date) {
    this->end_date = end_date;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool completed) {
    this->completed = completed;
}

