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

private:
    std::string dbName;
    // Add any other necessary private members
};

#endif // DATABASE_H