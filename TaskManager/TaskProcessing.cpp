#include "TaskProcessing.h"
#include "TaskManager.h"
#include <ctime>
#include <iostream>
#include <string>

void TaskProcessing::addTask(std::vector<Task> &arr) {
    std::string title;
    std::string description;
    std::tm start_date;
    std::tm end_date;
    std::cout << "Enter title:\n";
    std::cin.ignore(); // Очищаем буфер ввода перед считыванием строки
    std::getline(std::cin, title);
    std::cout << "Enter description:\n";
    std::getline(std::cin, description);
    std::cout << "Enter start date (YYYY MM DD HH MM SS):\n";
    std::cin >> start_date.tm_year >> start_date.tm_mon >> start_date.tm_mday
             >> start_date.tm_hour >> start_date.tm_min >> start_date.tm_sec;
    start_date.tm_year -= 1900;
    start_date.tm_mon -= 1;
    std::cout << "Enter end date (YYYY MM DD HH MM):\n";
    std::cin >> end_date.tm_year >> end_date.tm_mon >> end_date.tm_mday
             >> end_date.tm_hour >> end_date.tm_min;
    end_date.tm_year -= 1900;
    end_date.tm_mon -= 1;
    Task task(title, description, start_date, end_date, false);
    arr.push_back(task);
}
