#include "TaskProcessing.h"
#include "TaskManager.h"
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include "SQLite.cpp"
#include <sqlite3.h>
#include <iomanip>
std::string TaskProcessing::formatDateTime(const std::tm& datetime) {
    std::ostringstream oss;
    oss << std::put_time(&datetime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
void TaskProcessing::addTask() {
    std::string title;
    std::string description;
    std::tm start_date;
    std::tm end_date;
    std::cout << "Enter title:\n";
    std::cin.ignore();
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
    Task task(title, description, start_date, end_date, 0);
    Sqlite con(dbPath);
    std::ostringstream query;
    query << "INSERT INTO tasks (title, description, start_date, end_date, completed) "
          << "VALUES ('" << task.getTitle() << "', '"
          << task.getDescription() << "', '"
          << formatDateTime(task.getStartDate()) << "', '"
          << formatDateTime(task.getEndDate()) << "', "
          << (task.isCompleted() ? 1 : 0) << ");";

    std::string queryString = query.str();
    const char* q2 = queryString.c_str();
    std::cout << "Query: " << query.str() << std::endl;
    int rc = con.execute(q2, callback);
    if (rc == SQLITE_OK) {
        std::cout << "Task successfully added to the database.\n";
    }
    else {
        std::cerr << "Error adding task to the database. \n";
    }
}
void TaskProcessing::viewAllTasks() {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback1);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
}
void TaskProcessing::viewTaskDetails() {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback1);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "Enter the title of task you want to see." << '\n';
    std::string response;
    std::cin >> response;
    Sqlite::sqlSelectionRequest(response, con);
}

void TaskProcessing::editTask() {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback1);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "Enter the title of task you want to edit." << '\n';
    std::string response;
    std::cin >> response;
    Sqlite::sqlSelectionRequest(response, con);
    std::cout << "Choose the field you want to edit:\n"
                 "1. title.\n"
                 "2. description.\n"
                 "3. start_date.\n"
                 "4. end_date.\n";
    int selection = getCorrectResponse(1, 4);
    std::string ans;
    switch (selection) {
        case 1:
            std::cout << "Enter new title:\n";
            std::cin >> ans;
            Sqlite::sqlEditingRequest("title" ,ans, response);
            break;
        case 2:
            std::cout << "Enter new description:\n";
            std::cin >> ans;
            Sqlite::sqlEditingRequest("description" ,ans, response);
            break;
        case 3:
            std::cout << "Enter new start_date:\n";
            std::cin >> ans;
            Sqlite::sqlEditingRequest("start_date",ans, response);
            break;
        case 4:
            std::cout << "Enter new end_date:\n";
            std::cin >> ans;
            Sqlite::sqlEditingRequest("end_date" ,ans, response);
            break;
        default:
            std::cout << "Wrong enter!\n";
             break;
    }
}
//std::vector<Task> TaskProcessing::deleteTask(std::vector<Task> &arr) {
//    if (arr.size() != 0) {
//        std::cout << "What task you want to delete:\n";
//        for (int i = 0; i < arr.size(); i++) {
//            std::cout << i + 1 << '.' << ' ' << arr[i].getTitle() << '\n';
//        }
//        int response = getCorrectResponse(1, arr.size());
//        std::cout << "Are you sure? (y/n)\n";
//        std::string ans;
//        std::vector<Task> newarr;
//        if (ans == "Y" || ans == "y") {
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//        }
//        else {
//            std::cout << "Select one more time:";
//            response = getCorrectResponse(1, arr.size());
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//        }
//        return newarr;
//    }
//    else {
//        std::cout << "Arr is empty, add some tasks and repeat.\n";
//    }
//}

//std::vector<Task> TaskProcessing::completeTask(std::vector<Task> &arr) {
//    if (arr.size() != 0) {
//        std::cout << "What task was completed?:\n";
//        for (int i = 0; i < arr.size(); i++) {
//            std::cout << i + 1 << '.' << ' ' << arr[i].getTitle() << '\n';
//        }
//        int response = getCorrectResponse(1, arr.size());
//        std::cout << "Are you sure? (y/n)\n";
//        std::string ans;
//        std::vector<Task> newarr;
//        if (ans == "Y" || ans == "y") {
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//        }
//        else {
//            std::cout << "Select one more time:";
//            response =  getCorrectResponse(1, arr.size());
//            for (int i = 0; i < arr.size(); i++) {
//                if (i != response - 1) {
//                    newarr.push_back(arr[i]);
//                }
//            }
//        }
//        return newarr;
//    }
//    else {
//        std::cout << "Arr is empty, add some tasks and repeat.\n";
//    }
//}
int TaskProcessing::getCorrectResponse(int left, int right) {
    int num;
    while (true) {
        std::cin >> num;
        if (std::cin.fail() || num < left || num > right) {
            std::cout << "Please, choose a number from " << left << " to " << right << "." << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return num;
}
