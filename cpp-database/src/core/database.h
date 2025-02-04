#ifndef DATABASE_H
#define DATABASE_H

#include "core/table.h"
#include "storage/storage_engine.h"
#include <string>
#include <unordered_map>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();

    bool connect();
    void disconnect();
    bool executeQuery(const std::string& query);
    void displayTable(const std::string& tableName);

private:
    std::string dbName;
    bool connected;
    std::unordered_map<std::string, Table> tables;
    std::unique_ptr<mandb::StorageEngine> storage;
};

#endif // DATABASE_H

