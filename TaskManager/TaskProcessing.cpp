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
tm inputDateTime() {
    tm date{};
    bool flag;
    do {
        std::cin >> date.tm_year >> date.tm_mon >> date.tm_mday
                 >> date.tm_hour >> date.tm_min ;
        date.tm_year -= 1900;
        date.tm_mon -= 1;
        flag = !(std::cin.fail() || date.tm_mon < 0 || date.tm_mon > 11 ||
                       date.tm_mday < 1 || date.tm_mday > 31 ||
                       date.tm_hour < 0 || date.tm_hour > 23 ||
                       date.tm_min < 0 || date.tm_min > 59);
        if (!flag) {
            std::cout << "Invalid input. Please enter date and time in correct format.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!flag);
    return date;
}

void TaskProcessing::addTask() const {
    std::string title;
    std::string description;
    std::tm start_date{};
    std::tm end_date{};
    std::cout << "Enter the title:\n";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter description:\n";
    std::getline(std::cin, description);
    std::cout << "Enter start date (YYYY MM DD HH MM):\n";
    start_date = inputDateTime();

    std::cout << "Enter end date (YYYY MM DD HH MM):\n";
    end_date = inputDateTime();

    Task task(title, description, start_date, end_date, false);
    // connection to database
    Sqlite con(dbPath);
    std::ostringstream query;
    // request to database
    query << "INSERT INTO tasks (title, description, start_date, end_date, completed) "
          << "VALUES ('" << task.getTitle() << "', '"
          << task.getDescription() << "', '"
          << formatDateTime(task.getStartDate()) << "', '"
          << formatDateTime(task.getEndDate()) << "', "
          << (task.isCompleted() ? 1 : 0) << ");";

    std::string queryString = query.str();
    const char* q2 = queryString.c_str();
    std::cout << "Query: " << query.str() << '\n';
    int rc = con.execute(q2, callback);
    // check status
    if (rc == SQLITE_OK) {
        std::cout << "Task successfully added to the database.\n";
    }
    else {
        std::cerr << "Error adding task to the database. \n";
    }
}

void TaskProcessing::viewAllTasks() const {
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
void TaskProcessing::viewTaskDetails() const {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback2);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "Enter the title of the task you want to see." << '\n';
    std::string response;
    std::getline(std::cin >> std::ws, response);
    Sqlite::sqlSelectionRequest(response, con);
}

void TaskProcessing::editTask() const {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback2);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "Enter the title of the task you want to edit." << '\n';
    std::string response;
    std::getline(std::cin >> std::ws, response);
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
            std::getline(std::cin >> std::ws, ans);
            Sqlite::sqlEditingRequest("title" ,ans, response);
            break;
        case 2:
            std::cout << "Enter new description:\n";
            std::getline(std::cin >> std::ws, ans);
            Sqlite::sqlEditingRequest("description" ,ans, response);
            break;
        case 3:
            std::cout << "Enter new start_date:\n";
            std::getline(std::cin >> std::ws, ans);
            Sqlite::sqlEditingRequest("start_date",ans, response);
            break;
        case 4:
            std::cout << "Enter new end_date:\n";
            std::getline(std::cin >> std::ws, ans);
            Sqlite::sqlEditingRequest("end_date" ,ans, response);
            break;
        default:
            std::cout << "Wrong enter!\n";
             break;
    }
}
void TaskProcessing::deleteTask() const {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback2);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "What task you want to delete? (enter the title):\n";
    std::string response;
    std::getline(std::cin >> std::ws, response);
    std::cout << "Are you sure? (y/n)\n";
    std::string ans;
    std::cin >> ans;
    if (ans == "Y" || ans == "y") {
        Sqlite::sqlDeletingRequest(response);
    }
    else {
        std::cout << "Select one more time:";
        std::getline(std::cin >> std::ws, response);
        Sqlite::sqlDeletingRequest(response);
    }
}

void TaskProcessing::completeTask() const {
    Sqlite con(dbPath);
    const char* q1 = "SELECT * FROM tasks";
    int rc = con.execute(q1, callback2);
    if (rc == SQLITE_OK) {
        std::cout << "Look at your tasks list." <<'\n';
    }
    else {
        std::cerr << "\n";
    }
    std::cout << "What task have you completed? (enter the title):\n";
    std::string response;
    std::getline(std::cin >> std::ws, response);
    std::cout << "Are you sure? (y/n)\n";
    std::string ans;
    std::cin >> ans;
    if (ans == "Y" || ans == "y") {
        Sqlite::sqlCompletingRequest(response);
    }
    else {
        std::cout << "Select one more time:";
        std::getline(std::cin >> std::ws, response);
        Sqlite::sqlCompletingRequest(response);
    }
}

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
