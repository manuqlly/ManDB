cmake_minimum_required(VERSION 3.10)

project(cpp-database)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES
    src/core/*.cpp
    src/storage/*.cpp
    src/parser/*.cpp
    src/main.cpp
)

add_executable(cpp-database ${SOURCES})

enable_testing()
add_subdirectory(tests)