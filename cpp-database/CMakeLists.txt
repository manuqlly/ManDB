cmake_minimum_required(VERSION 3.10)

project(cpp-database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(LIB_SOURCE_FILES
    src/core/database.cpp
    src/core/table.cpp
    src/parser/sql_parser.cpp
    src/storage/log_manager.cpp
    src/storage/page_cache.cpp
    src/storage/storage_engine.cpp
)

# Create library
add_library(cpp-database-lib STATIC ${LIB_SOURCE_FILES})
target_include_directories(cpp-database-lib PUBLIC src)

# Create main executable
add_executable(cpp-database src/main.cpp)
target_link_libraries(cpp-database PRIVATE cpp-database-lib)

# Tests (commented for now)
# enable_testing()
# add_subdirectory(tests)