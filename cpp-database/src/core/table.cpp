#include "table.h"
#include <iostream>

Table::Table(const std::string& name) : name(name) {}

void Table::create(const std::vector<std::string>& columns) {
    this->columns = columns;
    std::cout << "Table " << name << " created with columns: ";
    for (const auto& column : columns) {
        std::cout << column << " ";
    }
    std::cout << std::endl;
}

void Table::insert(const std::map<std::string, std::string>& row) {
    rows.push_back(row);
    std::cout << "Row inserted into table " << name << "." << std::endl;
}

std::vector<std::map<std::string, std::string>> Table::select() const {
    return rows;
}

const std::vector<std::map<std::string, std::string>>& Table::getRows() const {
    return rows;
}
