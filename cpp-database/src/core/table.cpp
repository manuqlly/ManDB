#include "table.h"
#include <vector>
#include <string>
#include <iostream>

Table::Table(const std::string& name) : tableName(name) {}

void Table::create() {
    // Logic to create a table in the database
    std::cout << "Table " << tableName << " created." << std::endl;
}

void Table::insert(const std::vector<std::string>& row) {
    // Logic to insert a row into the table
    rows.push_back(row);
    std::cout << "Row inserted into table " << tableName << "." << std::endl;
}

std::vector<std::vector<std::string>> Table::select() const {
    // Logic to retrieve all rows from the table
    return rows;
}