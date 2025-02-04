#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();

    bool connect();
    void disconnect();
    bool executeQuery(const std::string& query);
    void displayTable(const std::string& tableName); // Add this line

private:
    std::string dbName;
    bool connected;
};

#endif // DATABASE_H