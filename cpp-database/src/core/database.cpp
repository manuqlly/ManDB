#include "database.h"
#include <iostream>

Database::Database(const std::string& dbName) : dbName(dbName), connected(false) {}

Database::~Database() {}

bool Database::connect() {
    std::cout << "Connecting to database: " << dbName << std::endl;
    connected = true; // Assume connection is successful
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
    return true; // Assume query execution is successful
}

void Database::displayTable(const std::string& tableName) {
    if (!connected) {
        std::cerr << "Database not connected." << std::endl;
        return;
    }
    std::cout << "Displaying contents of table: " << tableName << std::endl;
    // For demonstration, assume we have a method to fetch and display table data
    // In a real implementation, you would fetch data from the storage engine
    // std::cout << "id: 1, name: John" << std::endl; // Example output
}