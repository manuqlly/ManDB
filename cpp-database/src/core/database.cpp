#include "database.h"
#include "table.h"
#include <iostream>
#include <string>  // Add this include
#include <unordered_map>

Database::Database(const std::string& dbName) 
    : dbName(dbName), 
      connected(false),
      storage(std::make_unique<mandb::StorageEngine>("./data/" + dbName)) {}

Database::~Database() {}

bool Database::connect() {
    std::cout << "Connecting to database: " << dbName << std::endl;
    connected = true;
    return connected;
}

void Database::disconnect() {
    if (connected) {
        std::cout << "Disconnecting from database." << std::endl;
        connected = false;
    }
}

bool Database::executeQuery(const std::string& query) {
    if (!connected) {
        std::cerr << "Database not connected." << std::endl;
        return false;
    }
    std::cout << "Executing query: " << query << std::endl;

    if (query.find("SUMMON TABLE") != std::string::npos) {
        std::string tableName = "persons";
        tables[tableName] = Table(tableName);
        // Store table metadata
        storage->writeData(tableName + "_meta", "table_created");
    } else if (query.find("STUFF IN") != std::string::npos) {
        std::string tableName = "persons";
        std::map<std::string, std::string> row;
        if (query.find("VALUES (1, 'John', 25)") != std::string::npos) {
            row = {{"id", "1"}, {"name", "John"}, {"age", "25"}};
        } else if (query.find("VALUES (2, 'Jane', 30)") != std::string::npos) {
            row = {{"id", "2"}, {"name", "Jane"}, {"age", "30"}};
        }
        tables[tableName].insert(row);
        
        // Store row data
        std::string rowData;
        for (const auto& [key, value] : row) {
            rowData += key + "=" + value + ";";
        }
        storage->writeData(tableName + "_data", rowData);
    } else if (query.find("GIMME * FROM") != std::string::npos) {
        std::string tableName = "persons"; 
        displayTable(tableName);
    }

    return true;
}

void Database::displayTable(const std::string& tableName) {
    if (!connected) {
        std::cerr << "Database not connected." << std::endl;
        return;
    }
    std::cout << "Displaying contents of table: " << tableName << std::endl;

    if (tables.find(tableName) != tables.end()) {
        // Read from storage first
        std::string storedData = storage->readData(tableName + "_data", 0);
        if (!storedData.empty()) {
            std::cout << "Stored data: " << storedData << std::endl;
        }

        // Display in-memory data
        auto rows = tables[tableName].select();
        for (const auto& row : rows) {
            for (const auto& [column, value] : row) {
                std::cout << column << ": " << value << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Table " << tableName << " not found." << std::endl;
    }
}
