#include "query.h"
#include "database.h"
#include "sql_parser.h"

// Implementation of the Query class

Query::Query(Database& db) : database(db) {}

void Query::parse(const std::string& sql) {
    // Parse the SQL statement
    SQLParser parser;
    parsedStatement = parser.parse(sql);
}

void Query::execute() {
    // Execute the parsed SQL statement
    if (parsedStatement.isValid()) {
        database.executeQuery(parsedStatement);
    } else {
        throw std::runtime_error("Invalid SQL statement");
    }
}