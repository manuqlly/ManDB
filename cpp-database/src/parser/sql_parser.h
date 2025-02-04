#ifndef SQL_PARSER_H
#define SQL_PARSER_H

#include <string>
#include <vector>

class SQLParser {
public:
    SQLParser();
    ~SQLParser();

    // Parses a SQL query and returns the components
    std::vector<std::string> parse(const std::string& query);

    // Validates the SQL query syntax
    bool validate(const std::string& query);

private:
    // Helper methods for parsing different SQL commands
    void parseSelect(const std::string& query);
    void parseInsert(const std::string& query);
    void parseUpdate(const std::string& query);
    void parseDelete(const std::string& query);
};

#endif // SQL_PARSER_H