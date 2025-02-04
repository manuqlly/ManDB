#ifndef SQL_PARSER_H
#define SQL_PARSER_H

#include <string>
#include <vector>
#include <map>

struct SQLStatement {
    std::string command;
    std::string table;
    std::vector<std::string> columns;
    std::vector<std::string> values;
    std::string whereClause;
};

class SQLParser {
public:
    SQLParser();
    ~SQLParser() = default;

    bool parse(const std::string& query);
    bool validate(const std::string& query);

private:
    bool parseSelect(std::istringstream& stream);
    bool parseInsert(std::istringstream& stream);
    bool parseUpdate(std::istringstream& stream);
    bool parseDelete(std::istringstream& stream);
    bool parseCreate(std::istringstream& stream);
};

#endif // SQL_PARSER_H