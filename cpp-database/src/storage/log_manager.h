#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace mandb {

class LogManager {
public:
    LogManager();
    ~LogManager();
    
    void initialize(const std::string& log_path);
    void beginTransaction();
    void logWrite(const std::string& table_name, const std::string& data);
    void commitTransaction();
    void rollbackTransaction();
    void recover();

private:
    std::string log_file_path;
    std::ofstream log_file;
    uint64_t current_transaction_id;
    std::vector<std::string> pending_operations;
};

}