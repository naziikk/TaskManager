//
// Created by Назар Закревский on 23.04.2024.
//

#ifndef UNTITLED8_HELPERMETHODS_H
#define UNTITLED8_HELPERMETHODS_H

#include "HelperMethods.h"
#include <iostream>
#include <vector>
#include "TaskManager/TaskManager.h"
class HelperMethods {
public:
    int getCorrectInput(int left, int right);
    void printTasks(std::vector<Task> arr);
};


#endif //UNTITLED8_HELPERMETHODS_H
