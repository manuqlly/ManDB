#include <iostream>
#include "core/database.h"
#include "parser/sql_parser.h"

int main() {
    try {
        // Initialize database
        Database db("test_db");
        if (!db.connect()) {
            std::cerr << "Failed to connect to database\n";
            return 1;
        }

        // Create SQL parser
        SQLParser parser;

        // Test basic SQL commands
        std::vector<std::string> test_queries = {
            "SUMMON TABLE users (id INT, name TEXT)",
            // "STUFF IN users (id, name) VALUES (1, 'Selva')",
            // "GIMME * FROM users",
            // "MORPH users SET name = 'Jane' WHERE id = 1",
            // "VANISH FROM users WHERE id = 1"
        };

        // Execute each query
        for (const auto& query : test_queries) {
            std::cout << "\nExecuting: " << query << std::endl;
            
            // Validate query
            if (!parser.validate(query)) {
                std::cout << "Invalid query syntax\n";
                continue;
            }

            // Execute query
            if (!db.executeQuery(query)) {
                std::cout << "Query execution failed\n";
                continue;
            }

            std::cout << "Query executed successfully\n";

            // Display table contents after each query
            if (query.find("GIMME") != std::string::npos) {
                db.displayTable("users");
            }
        }

        // Display table contents before VANISH
        std::cout << "\nDisplaying table contents before VANISH:\n";
        db.displayTable("users");

        // Execute VANISH query
        std::string vanish_query = "VANISH FROM users WHERE id = 1";
        std::cout << "\nExecuting: " << vanish_query << std::endl;
        if (parser.validate(vanish_query) && db.executeQuery(vanish_query)) {
            std::cout << "Query executed successfully\n";
        } else {
            std::cout << "Query execution failed\n";
        }

        // Display table contents after VANISH
        std::cout << "\nDisplaying table contents after VANISH:\n";
        db.displayTable("users");

        db.disconnect();
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}