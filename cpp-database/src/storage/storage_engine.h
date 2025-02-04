#pragma once

#include <string>
#include <memory>
#include <map>
#include <shared_mutex>
#include <array>

namespace mandb {

class LogManager;
class PageCache;

class StorageEngine {
public:
    static constexpr size_t PAGE_SIZE = 4096;
    static constexpr size_t CACHE_SIZE = 1000;

    struct Page {
        uint32_t page_id;
        uint32_t page_number;
        std::string table_name;
        std::array<char, PAGE_SIZE> data;
        uint32_t checksum;
        bool is_dirty;
    };

    explicit StorageEngine(const std::string& dbPath);
    ~StorageEngine();

    bool writeData(const std::string& tableName, const std::string& data);
    std::string readData(const std::string& tableName, unsigned int offset);

private:
    std::string dbPath;
    std::string data_directory;
    std::shared_mutex access_mutex;
    std::unique_ptr<PageCache> pageCache;
    std::unique_ptr<LogManager> logManager;

    void initializeStorage();
    Page* getPageFromCache(const std::string& tableName, unsigned int pageNumber);
    Page* getPageForWrite(const std::string& tableName);
    void flushPage(Page* page);
    bool verifyChecksum(const Page* page);
    uint32_t calculateChecksum(const char* data, size_t size);
    std::string getPageFilePath(uint32_t page_id);
    std::string readFromDisk(const std::string& table_name, uint32_t page_id);
    uint32_t getNextPageId(const std::string& table_name);
    bool shouldFlushToDisk();
};

} // namespace mandb
