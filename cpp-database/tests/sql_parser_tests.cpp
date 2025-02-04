#include "../src/parser/sql_parser.h"
#include <cassert>
#include <iostream>

void test_basic_queries() {
    SQLParser parser;
    
    // Test CREATE TABLE
    assert(parser.validate("SUMMON TABLE users (id INT, name TEXT)"));
    
    // Test INSERT
    assert(parser.validate("STUFF IN users (id, name) VALUES (1, 'John')"));
    
    // Test SELECT
    assert(parser.validate("GIMME * FROM users"));
    
    // Test UPDATE
    assert(parser.validate("MORPH users SET name = 'Jane' WHERE id = 1"));
    
    // Test DELETE
    assert(parser.validate("VANISH FROM users WHERE id = 1"));
    
    std::cout << "Basic query tests passed!\n";
}

int main() {
    try {
        test_basic_queries();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}