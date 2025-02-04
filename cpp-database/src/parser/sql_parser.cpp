#include "sql_parser.h"
#include <iostream>
#include <sstream>
#include <algorithm>

SQLParser::SQLParser() : commandAliases{
    {"GIMME", "SELECT"},
    {"STUFF IN", "INSERT INTO"},
    {"MORPH", "UPDATE"}, 
    {"VANISH", "DELETE"},
    {"SUMMON TABLE", "CREATE TABLE"}
} {}

bool SQLParser::validate(const std::string& query) {
    std::istringstream stream(query);
    std::string cmd;
    stream >> cmd;
    cmd = normalizeCommand(cmd);
    
    std::cout << "Normalized command: " << cmd << std::endl; // Debugging output
    
    return (cmd == "SELECT" || cmd == "INSERT INTO" || 
            cmd == "UPDATE" || cmd == "DELETE" ||
            cmd == "CREATE TABLE");
}

std::string SQLParser::normalizeCommand(const std::string& cmd) {
    std::string upperCmd = cmd;
    std::transform(upperCmd.begin(), upperCmd.end(), 
                  upperCmd.begin(), ::toupper);
    
    auto it = commandAliases.find(upperCmd);
    std::string normalizedCmd = (it != commandAliases.end()) ? it->second : upperCmd;
    
    std::cout << "Original command: " << cmd << ", Normalized command: " << normalizedCmd << std::endl; // Debugging output
    
    return normalizedCmd;
}

bool SQLParser::parse(const std::string& sql) {
    std::istringstream stream(sql);
    std::string command;
    
    // Handle two-word commands
    std::string word1, word2;
    stream >> word1;
    std::string upperWord1 = word1;
    std::transform(upperWord1.begin(), upperWord1.end(), upperWord1.begin(), ::toupper);
    
    if (upperWord1 == "STUFF" || upperWord1 == "SUMMON") {
        stream >> word2;
        command = normalizeCommand(word1 + " " + word2);
    } else {
        command = normalizeCommand(word1);
    }

    if (command == "SELECT") {
        return parseSelect(stream);
    } else if (command == "INSERT") {
        return parseInsert(stream);
    } else if (command == "UPDATE") {
        return parseUpdate(stream);
    } else if (command == "DELETE") {
        return parseDelete(stream);
    } else if (command == "CREATE") {
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