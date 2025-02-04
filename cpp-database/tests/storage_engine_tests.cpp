#include "../src/storage/storage_engine.h"
#include <cassert>
#include <iostream>

void test_storage_operations() {
    StorageEngine engine("test_db");
    
    // Test write
    assert(engine.writeData("users", "1,John"));
    
    // Test read
    auto data = engine.readData("users", 1);
    assert(data == "1,John");
    
    std::cout << "Storage engine tests passed!\n";
}

int main() {
    try {
        test_storage_operations();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}