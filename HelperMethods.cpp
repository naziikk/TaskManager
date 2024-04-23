//
// Created by Назар Закревский on 23.04.2024.
//

#include "HelperMethods.h"
#include <iostream>
int HelperMethods::getCorrectInput(int left, int right) {
    int num;
    while (true) {
        std::cin >> num;
        if (std::cin.fail() || num < left || num > right) {
            std::cout << "Please, choose a number from " << left << " to " << right << "." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return num;
}
void HelperMethods::printTasks(std::vector<Task> arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << "Task " << i + 1 << ":" << '\n';
        arr[i].printTask();
    }
}