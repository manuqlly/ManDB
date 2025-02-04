#include <iostream>
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
            "SUMMON TABLE persons (id INT, name TEXT, age INT)",
            "STUFF IN persons (id, name, age) VALUES (1, 'John', 25)",
            "STUFF IN persons (id, name, age) VALUES (2, 'Jane', 30)",
            "GIMME * FROM persons"
        };

        for (const auto& query : queries) {
            std::cout << "Executing: " << query << std::endl;
            if (parser.validate(query)) {
                if (!db.executeQuery(query)) {
                    std::cerr << "Failed to execute query\n";
                }
            }
        }

        std::cout << "\nDisconnecting from database...\n";
        db.disconnect();
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
