#include "database.h"
#include "table.h"
#include <iostream>
#include <string>  // Add this include
#include <unordered_map>
#include <sstream>

Database::Database(const std::string& dbName) 
    : dbName(dbName), 
      connected(false),
      storage(std::make_unique<mandb::StorageEngine>(dbName)) {}

Database::~Database() {
    if (connected) {
        disconnect();
    }
}

bool Database::connect() {
    // Simulate database connection
    connected = true;
    return connected;
}

void Database::disconnect() {
    // Simulate database disconnection
    connected = false;
}

bool Database::isConnected() const {
    return connected;
}

bool Database::executeModifyQuery(const std::string& query) {
    // Simulate query execution
    std::cout << "Executing query: " << query << std::endl;
    return true;
}

std::vector<std::string> Database::executeSelectQuery(const std::string& query) const {
    // Simulate query execution and return results
    std::vector<std::string> results;
    if (query == "SELECT * FROM persons") {
        results.push_back("1, John, 25");
        results.push_back("2, Jane, 30");
    }
    return results;
}

void Database::displayTable(const std::string& tableName) const {
    auto it = tables.find(tableName);
    if (it != tables.end()) {
        const Table& table = it->second;
        for (const auto& row : table.getRows()) {
            for (const auto& [column, value] : row) {
                std::cout << column << ": " << value << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Table not found: " << tableName << std::endl;
    }
}
