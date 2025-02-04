#include <iostream>
#include <vector>
#include <string>
#include "core/database.h"
#include "parser/sql_parser.h"

int main() {
    try {
        Database db("test_db");
        if (!db.connect()) {
            std::cerr << "Failed to connect to database\n";
            return 1;
        }
        std::cout << "Connected to database: test_db\n\n";

        SQLParser parser;

        std::vector<std::string> queries = {
            "CREATE TABLE persons (id INT, name TEXT, age INT)",
            "INSERT INTO persons (id, name, age) VALUES (1, 'John', 25)",
            "INSERT INTO persons (id, name, age) VALUES (2, 'Jane', 30)"
        };

        for (const auto& query : queries) {
            std::cout << "Executing: " << query << std::endl;
            if (parser.validate(query)) {
                if (!db.executeModifyQuery(query)) {
                    std::cerr << "Failed to execute query\n";
                }
            }
        }

        // Display the contents of the table
        std::cout << "\nDisplaying contents of table: persons\n";
        auto results = db.executeSelectQuery("SELECT * FROM persons");
        for (const auto& row : results) {
            std::cout << row << std::endl;
        }

        std::cout << "\nDisconnecting from database...\n";
        db.disconnect();
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
