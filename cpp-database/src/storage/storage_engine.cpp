#include "storage_engine.h"
#include "page_cache.h"
#include "log_manager.h"
#include "crc32.h"
#include <fstream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <filesystem>
#include <cstring>

namespace mandb {

StorageEngine::StorageEngine(const std::string& dir) 
    : data_directory(dir), log_manager(new LogManager()) {
    initializeStorage();
}

StorageEngine::~StorageEngine() {
    for (auto& [table_name, cache] : page_cache) {
        auto pages = cache->getAllPages();
        for (auto page : pages) {
            if (page->is_dirty) {
                flushPage(page);
            }
        }
    }
    page_cache.clear();
    delete log_manager;
}

bool StorageEngine::writeData(const std::string& table_name, const std::string& data) {
    std::unique_lock<std::shared_mutex> write_lock(access_mutex);
    try {
        log_manager->beginTransaction();
        log_manager->logWrite(table_name, data);

        auto page = getPageForWrite(table_name);
        if (!page) return false;

        std::memcpy(page->data.data(), data.c_str(), std::min(data.size(), PAGE_SIZE));
        page->is_dirty = true;
        page->checksum = calculateChecksum(page->data.data(), PAGE_SIZE);

        log_manager->commitTransaction();
        
        if (shouldFlushToDisk()) {
            flushPage(page);
        }

        return true;
    }
    catch (const std::exception& e) {
        log_manager->rollbackTransaction();
        return false;
    }
}

std::string StorageEngine::readData(const std::string& table_name, uint32_t page_id) {
    std::shared_lock<std::shared_mutex> read_lock(access_mutex);
    
    auto page = getPageFromCache(table_name, page_id);
    if (page) {
        if (verifyChecksum(page)) {
            return std::string(page->data.data());
        }
    }

    return readFromDisk(table_name, page_id);
}

void StorageEngine::initializeStorage() {
    if (!std::filesystem::exists(data_directory)) {
        std::filesystem::create_directories(data_directory);
    }
    log_manager->initialize(data_directory + "/wal");
}

bool StorageEngine::verifyChecksum(const Page* page) {
    return page->checksum == calculateChecksum(page->data.data(), PAGE_SIZE);
}

uint32_t StorageEngine::calculateChecksum(const char* data, size_t size) {
    return crc32(data, size);
}

void StorageEngine::flushPage(Page* page) {
    if (!page->is_dirty) return;
    
    std::string filepath = getPageFilePath(page->page_id);
    std::ofstream file(filepath, std::ios::binary);
    file.write(page->data.data(), PAGE_SIZE);
    file.close();
    
    page->is_dirty = false;
}

bool StorageEngine::shouldFlushToDisk() {
    size_t dirty_count = 0;
    for (auto& [_, cache] : page_cache) {
        dirty_count += cache->getDirtyPageCount();
    }
    return dirty_count > CACHE_SIZE / 2;
}

StorageEngine::Page* StorageEngine::getPageForWrite(const std::string& table_name) {
    if (page_cache.find(table_name) == page_cache.end()) {
        page_cache[table_name] = std::make_shared<PageCache>(CACHE_SIZE);
    }
    
    uint32_t page_id = getNextPageId(table_name);
    auto page = new Page{page_id};
    page_cache[table_name]->put(page);
    return page;
}

std::string StorageEngine::getPageFilePath(uint32_t page_id) {
    return data_directory + "/page_" + std::to_string(page_id) + ".dat";
}

std::string StorageEngine::readFromDisk(const std::string& table_name, uint32_t page_id) {
    std::string filepath = getPageFilePath(page_id);
    std::ifstream file(filepath, std::ios::binary);
    
    if (!file) {
        return "";
    }
    
    std::array<char, PAGE_SIZE> buffer;
    file.read(buffer.data(), PAGE_SIZE);
    return std::string(buffer.data(), static_cast<std::streamsize>(file.gcount()));
}

uint32_t StorageEngine::getNextPageId(const std::string& table_name) {
    std::string filepath = data_directory + "/" + table_name + "_counter.txt";
    uint32_t next_id = 0;
    
    std::ifstream in(filepath);
    if (in) {
        in >> next_id;
        in.close();
    }
    
    std::ofstream out(filepath);
    out << (next_id + 1);
    out.close();
    
    return next_id;
}

} // namespace mandb
