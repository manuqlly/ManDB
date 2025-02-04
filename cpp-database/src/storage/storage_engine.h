#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include <string>
#include <memory>
#include <map>
#include <shared_mutex>

namespace mandb {

class LogManager;
class PageCache;

class StorageEngine {
public:
    StorageEngine(const std::string& dir);
    ~StorageEngine();

    bool writeData(const std::string& table_name, const std::string& data);
    std::string readData(const std::string& table_name, uint32_t page_id);

private:
    static const size_t PAGE_SIZE = 4096;
    static const size_t CACHE_SIZE = 1000;

    struct Page {
        uint32_t page_id;
        char data[PAGE_SIZE];
        uint32_t checksum;
        bool is_dirty;
    };

    void initializeStorage();
    bool verifyChecksum(const Page* page);
    uint32_t calculateChecksum(const char* data, size_t size);
    void flushPage(Page* page);
    bool shouldFlushToDisk();
    Page* getPageForWrite(const std::string& table_name);
    Page* getPageFromCache(const std::string& table_name, uint32_t page_id);
    std::string readFromDisk(const std::string& table_name, uint32_t page_id);
    std::string getPageFilePath(uint32_t page_id);

    std::string data_directory;
    std::shared_mutex access_mutex;
    std::map<std::string, std::shared_ptr<PageCache>> page_cache;
    LogManager* log_manager;
};

} // namespace mandb

#endif // STORAGE_ENGINE_H