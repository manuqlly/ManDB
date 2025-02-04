#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <unordered_map>

namespace database {

using Row = std::unordered_map<std::string, std::string>;
using TableName = std::string;
using QueryString = std::string;
using DatabaseName = std::string;

const int MAX_ROWS = 1000;

} // namespace database

#endif // TYPES_H