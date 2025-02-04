add_executable(db_tests
    sql_parser_tests.cpp
    storage_engine_tests.cpp
    database_tests.cpp
)

target_link_libraries(db_tests PRIVATE cpp-database-lib)

add_test(NAME parser_tests COMMAND db_tests)