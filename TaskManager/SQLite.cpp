#include <sqlite3.h>
#include <iostream>
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
};

