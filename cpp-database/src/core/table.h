#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>

class Table {
public:
    Table(const std::string& name);
    void create(const std::vector<std::string>& columns);
    void insert(const std::map<std::string, std::string>& row);
    std::vector<std::map<std::string, std::string>> select() const;

private:
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::map<std::string, std::string>> rows;
};

#endif // TABLE_H