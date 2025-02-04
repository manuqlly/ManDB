#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "storage/storage_engine.h"
#include "core/table.h"

class Database {
public:
    Database(const std::string& dbName);
    ~Database();

    bool connect();
    void disconnect();
    bool isConnected() const;
    bool executeModifyQuery(const std::string& query);  // For INSERT, UPDATE, DELETE, CREATE
    std::vector<std::string> executeSelectQuery(const std::string& query) const;  // For SELECT

private:
    std::string dbName;
    bool connected;
    std::unique_ptr<mandb::StorageEngine> storage;
    std::unordered_map<std::string, Table> tables;

    void displayTable(const std::string& tableName) const;
};

#endif // DATABASE_H

