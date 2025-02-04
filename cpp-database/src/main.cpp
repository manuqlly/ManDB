#include <iostream>
#include "core/database.h"

int main() {
    Database db;

    // Initialize the database
    if (db.connect("my_database")) {
        std::cout << "Database connected successfully." << std::endl;

        // Example of executing a query
        db.executeQuery("CREATE TABLE users (id INT, name TEXT);");
        
        // Disconnect from the database
        db.disconnect();
    } else {
        std::cerr << "Failed to connect to the database." << std::endl;
    }

    return 0;
}