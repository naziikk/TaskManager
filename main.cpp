#include "TaskManager/TaskManager.h"
#include "TaskManager/TaskProcessing.h"
#include "HelperMethods.h"
#include <iostream>
#include <vector>
#include "SQLite.cpp"
class Program {
public:
    static int main() {
        std::cout << "\033[1;35m";
        HelperMethods helper;
        TaskProcessing processing;
        Sqlite con(processing.dbPath);
        const char* q1 = "CREATE TABLE IF NOT EXISTS tasks ("
                         "task_id INTEGER PRIMARY KEY,"
                         "title TEXT NOT NULL,"
                         "description TEXT,"
                         "start_date DATETIME,"
                         "end_date DATETIME,"
                         "completed INTEGER DEFAULT 0"
                         ");";
        int rc = con.execute(q1, callback);
        if (rc == SQLITE_OK) {
            std::cout << "Таблица tasks успешно создана или уже существует." << '\n';
        }

//        const char* q2 = "INSERT INTO tasks (title, description, start_date, end_date, completed) "
//                         "VALUES ('kill masha', 'i wanna kill her', '2024-04-25 10:00:00', '2024-04-30 20:00:00', 0);";
//        rc = con.execute(q2, callback);
//        if (rc == SQLITE_OK) {
//            std::cout << "Данные успешно добавлены в таблицу tasks." << '\n';
//        }
        bool flag = true;
        while (flag) {
            try {
                std::cout << "Choose an option:\n"
                             "1. Add a new task.\n"
                             "2. View my tasks.\n"
                             "3. View details of a specific task.\n"
                             "4. Modify task parameters.\n"
                             "5. Delete a task.\n"
                             "6. Mark a task as completed.\n"
                             "7. Exit.\n";
                int response = helper.getCorrectInput(1, 7);
                switch (response) {
                    case 1:
                        processing.addTask();
                        break;
                    case 2:
                        processing.viewAllTasks();
                        break;
                    case 3:
                        processing.viewTaskDetails();
                        break;
                    case 4:
                        processing.editTask();
                        break;
                    case 5:
                        processing.deleteTask();
                        break;
                    case 6:
                        processing.completeTask();
                        break;
                    case 7:
                        flag = false;
                        break;
                    default:
                        std::cout << "Wrong enter!\n";
                        break;
                }
            }
            catch (std::exception){
                std::cout << "Some shit happened.";
            }
        }
        return 0;
    }
};

int main() {
    return Program::main();
}
