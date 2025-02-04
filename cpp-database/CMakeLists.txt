cmake_minimum_required(VERSION 3.10)

project(cpp-database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (excluding main.cpp)
set(LIB_SOURCE_FILES
    src/parser/sql_parser.cpp
    src/core/database.cpp
    src/storage/storage_engine.cpp
    src/storage/crc32.cpp
)

# Create library
add_library(cpp-database-lib STATIC ${LIB_SOURCE_FILES})
target_include_directories(cpp-database-lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Create main executable
add_executable(cpp-database src/main.cpp)
target_link_libraries(cpp-database PRIVATE cpp-database-lib)

# Comment out tests for now until test files are ready
# enable_testing()
# add_subdirectory(tests)