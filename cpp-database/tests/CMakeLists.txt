cmake_minimum_required(VERSION 3.10)

project(cpp-database-tests)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test files
set(TEST_FILES
    core_tests.cpp
    database_tests.cpp
    parser_tests.cpp
    sql_parser_tests.cpp
    storage_engine_tests.cpp
)

# Create test executable
add_executable(runTests ${TEST_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread cpp-database-lib)

# Enable testing
enable_testing()

# Add tests
add_test(NAME runTests COMMAND runTests)