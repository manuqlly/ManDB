#include "../src/core/database.h"
#include <cassert>
#include <iostream>

void test_database_operations() {
    Database db("test_db");
    assert(db.connect());
    
    // Test query execution
    assert(db.executeQuery("SUMMON TABLE users (id INT, name TEXT)"));
    assert(db.executeQuery("STUFF IN users (id, name) VALUES (1, 'John')"));
    
    std::cout << "Database tests passed!\n";
}

int main() {
    try {
        test_database_operations();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}