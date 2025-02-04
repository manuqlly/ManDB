#include "database.h"
#include <iostream>

Database::Database() : connected(false) {}

bool Database::connect(const std::string& dbName) {
    // Simulate a database connection
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
    // Simulate query execution
    std::cout << "Executing query: " << query << std::endl;
    return true; // Assume query execution is successful
}