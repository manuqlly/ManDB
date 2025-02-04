#include "sql_parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

SQLParser::SQLParser() {}

bool SQLParser::validate(const std::string& query) {
    std::regex createPattern(
        R"(CREATE TABLE (\w+) \(((?:\w+ (?:INT|TEXT)(?:,\s*)?)+)\))",
        std::regex_constants::icase
    );

    if (std::regex_match(query, createPattern)) {
        return true;
    }
    
    std::istringstream stream(query);
    std::string cmd;
    stream >> cmd;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    
    std::cout << "Command: " << cmd << std::endl; // Debugging output
    
    return (cmd == "SELECT" || cmd == "INSERT INTO" || 
            cmd == "UPDATE" || cmd == "DELETE" ||
            cmd == "CREATE TABLE");
}

bool SQLParser::parse(const std::string& sql) {
    std::istringstream stream(sql);
    std::string command;
    
    stream >> command;
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "SELECT") {
        return parseSelect(stream);
    } else if (command == "INSERT INTO") {
        return parseInsert(stream);
    } else if (command == "UPDATE") {
        return parseUpdate(stream);
    } else if (command == "DELETE") {
        return parseDelete(stream);
    } else if (command == "CREATE TABLE") {
        return parseCreate(stream);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return false;
    }
}

bool SQLParser::parseSelect(std::istringstream& stream) {
    std::string token;
    std::vector<std::string> columns;
    
    // Parse columns
    while (stream >> token && token != "FROM") {
        if (token != ",") columns.push_back(token);
    }
    
    // Parse table name
    std::string tableName;
    stream >> tableName;
    
    // Parse WHERE clause if exists
    std::string whereClause;
    stream >> token;
    if (token == "WHERE") {
        std::getline(stream, whereClause);
    }
    
    return true;
}

bool SQLParser::parseInsert(std::istringstream& stream) {
    std::string token, tableName;
    std::vector<std::string> columns, values;
    
    stream >> token; // Skip "INTO"
    stream >> tableName;
    
    // Parse column names
    stream >> token; // Skip "("
    while (stream >> token && token != ")") {
        if (token != ",") columns.push_back(token);
    }
    
    // Parse values
    stream >> token; // Skip "VALUES"
    stream >> token; // Skip "("
    while (stream >> token && token != ")") {
        if (token != ",") values.push_back(token);
    }
    
    return columns.size() == values.size();
}

bool SQLParser::parseUpdate(std::istringstream& stream) {
    std::string tableName, token;
    stream >> tableName;
    if (tableName.empty()) return false;
    
    stream >> token;
    if (token != "SET") return false;
    
    // Parse SET clause
    std::string setClause;
    while (stream >> token && token != "WHERE") {
        setClause += token + " ";
    }
    if (setClause.empty()) return false;
    
    // Parse WHERE clause
    std::string whereClause;
    if (token == "WHERE") {
        std::getline(stream, whereClause);
        if (whereClause.empty()) return false;
    }
    
    return true;
}

bool SQLParser::parseDelete(std::istringstream& stream) {
    std::string token;
    stream >> token;
    if (token != "FROM") return false;
    
    std::string tableName;
    stream >> tableName;
    if (tableName.empty()) return false;
    
    // Parse WHERE clause if exists
    stream >> token;
    if (token == "WHERE") {
        std::string whereClause;
        std::getline(stream, whereClause);
        if (whereClause.empty()) return false;
    }
    
    return true;
}

bool SQLParser::parseCreate(std::istringstream& stream) {
    std::string token;
    stream >> token; // Should be "TABLE"
    
    if (token != "TABLE") {
        std::cerr << "Expected 'TABLE', got '" << token << "'" << std::endl;
        return false;
    }
    
    std::string tableName;
    stream >> tableName;
    
    // Parse column definitions
    std::vector<std::string> columnDefs;
    stream >> token; // Skip "("
    std::string columnDef;
    while (std::getline(stream, token, ',')) {
        columnDefs.push_back(token);
    }
    
    return !tableName.empty() && !columnDefs.empty();
}