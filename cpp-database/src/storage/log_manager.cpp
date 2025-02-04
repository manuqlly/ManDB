#include "log_manager.h"
#include <iostream>
#include <fstream>

namespace mandb {

LogManager::LogManager() : current_transaction_id(0) {}

LogManager::~LogManager() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void LogManager::initialize(const std::string& log_path) {
    log_file_path = log_path;
    log_file.open(log_file_path, std::ios::out | std::ios::app);
    if (!log_file.is_open()) {
        throw std::runtime_error("Failed to open log file: " + log_file_path);
    }
}

void LogManager::beginTransaction() {
    current_transaction_id++;
    pending_operations.clear();
    log_file << "BEGIN TRANSACTION " << current_transaction_id << std::endl;
}

void LogManager::logWrite(const std::string& table_name, const std::string& data) {
    pending_operations.push_back("WRITE " + table_name + " " + data);
}

void LogManager::commitTransaction() {
    for (const auto& operation : pending_operations) {
        log_file << operation << std::endl;
    }
    log_file << "COMMIT TRANSACTION " << current_transaction_id << std::endl;
    log_file.flush();
}

void LogManager::rollbackTransaction() {
    log_file << "ROLLBACK TRANSACTION " << current_transaction_id << std::endl;
    log_file.flush();
    pending_operations.clear();
}

void LogManager::recover() {
    std::ifstream log_file_in(log_file_path);
    if (!log_file_in.is_open()) {
        throw std::runtime_error("Failed to open log file for recovery: " + log_file_path);
    }

    std::string line;
    while (std::getline(log_file_in, line)) {
        std::cout << "Recovery log: " << line << std::endl;
        // Implement recovery logic based on log entries
    }
}

} // namespace mandb