#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include "TaskProcessing.h"
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}
static int callback1(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
    }
    std::cout << '\n';
    return 0;
}
static int callback2(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 1; i < 2; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
    }
    std::cout << '\n';
    return 0;
}

class Sqlite {
private:
    sqlite3* db;
public:
    Sqlite(const char* dbname) {
        int rc = sqlite3_open(dbname, &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Error while opening database: " << sqlite3_errmsg(db) << '\n';
            db = nullptr;
        }
    }
    ~Sqlite() {
        if (db) {
            sqlite3_close(db);
        }
    }
    int execute(const char* sql, int (*callback)(void *, int, char **, char **), char* err = nullptr) {
        if (!db) {
            std::cerr << "Database is not open.\n";
            return SQLITE_ERROR;
        }
        return sqlite3_exec(db, sql, callback, 0, &err);
    }
    static void sqlSelectionRequest(std::string response, Sqlite con) {
        std::stringstream query;
        query << "SELECT * FROM tasks WHERE title = '" << response << "'";
        std::string q = query.str();
        const char* q2 = q.c_str();
        int rc = con.execute(q2, callback1);
        if (rc == SQLITE_OK) {
            std::cout << "Look at your tasks details.\n";
        }
        else {
            std::cerr << "\n";
        }
    }
    static void sqlEditingRequest(std::string field, std::string newValue, std::string response) {
        TaskProcessing task;
        Sqlite con(task.dbPath);
        std::stringstream query;
        query << "UPDATE tasks SET " << field << " = '" << newValue << "' WHERE title = '" << response << "';";
        std::cout << query.str() << '\n';
        std::string q = query.str();
        int rc = con.execute(q.c_str(), callback);
        if (rc == SQLITE_OK) {
            std::cout << "Task details successfully updated.\n";
        }
        else {
            std::cerr << "Error updating task details.\n";
        }
    }
    static void sqlDeletingRequest(std::string response) {
        TaskProcessing task;
        Sqlite con(task.dbPath);
        std::stringstream query;
        query << "DELETE FROM tasks WHERE title = '" << response << "';";
        std::string q = query.str();
        int rc = con.execute(q.c_str(), callback);
        if (rc == SQLITE_OK) {
            std::ostringstream oss;
            oss << "Task |" << response << "| has been deleted.";
            std::string result = oss.str();
            std::cout << result << std::endl;
        }
        else {
            std::cerr << "Error deleting task.\n";
        }
    }
    static void sqlCompletingRequest(std::string response) {
        TaskProcessing task;
        Sqlite con(task.dbPath);
        std::stringstream query;
        query << "DELETE FROM tasks WHERE title = '" << response << "';";
        std::string q = query.str();
        int rc = con.execute(q.c_str(), callback);
        if (rc == SQLITE_OK) {
            std::ostringstream oss;
            oss << "You have completed |" << response << "|, task has been deleted.";
            std::string result = oss.str();
            std::cout << result << std::endl;
        }
        else {
            std::cerr << "Error completing task.\n";
        }
    }
};

