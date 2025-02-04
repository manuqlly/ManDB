#include "storage/storage_engine.h"
#include "storage/page_cache.h"
#include "storage/log_manager.h"
#include <fstream>
#include <stdexcept>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <filesystem>
#include <cstring>

// CRC32 table
static unsigned int crc32_table[256];
static bool crc32_initialized = false;

// Initialize CRC32 table
void init_crc32_table() {
    if (crc32_initialized) return;
    
    for (unsigned int i = 0; i < 256; i++) {
        unsigned int crc = i;
        for (unsigned int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
        }
        crc32_table[i] = crc;
    }
    crc32_initialized = true;
}

// CRC32 implementation
unsigned int crc32(const char* data, size_t length) {
    init_crc32_table();
    unsigned int crc = 0xFFFFFFFF;
    
    for (size_t i = 0; i < length; i++) {
        crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ static_cast<unsigned char>(data[i])];
    }
    
    return ~crc;
}

namespace mandb {

StorageEngine::StorageEngine(const std::string& dbPath) 
    : dbPath(dbPath), data_directory("./data/" + dbPath) {  // Initialize data_directory
    pageCache = std::make_unique<PageCache>(1000);
    logManager = std::make_unique<LogManager>();
    initializeStorage();
}

StorageEngine::~StorageEngine() = default;

StorageEngine::Page* StorageEngine::getPageFromCache(const std::string& tableName, unsigned int pageNumber) {
    return pageCache->get(pageNumber);
}

bool StorageEngine::writeData(const std::string& tableName, const std::string& data) {
    auto* page = getPageForWrite(tableName);
    if (!page) return false;
    
    // Copy data to page
    std::memcpy(page->data.data(), data.c_str(), data.length());
    page->is_dirty = true;
    
    // Log the write operation
    logManager->logWrite(tableName, data);
    
    return true;
}

std::string StorageEngine::readData(const std::string& tableName, unsigned int offset) {
    auto* page = getPageFromCache(tableName, offset);
    if (!page) return "";
    
    return std::string(page->data.data());
}

void StorageEngine::initializeStorage() {
    if (!std::filesystem::exists(data_directory)) {
        std::filesystem::create_directories(data_directory);
    }
    logManager->initialize(data_directory + "/wal");
}

bool StorageEngine::verifyChecksum(const Page* page) {
    return page->checksum == calculateChecksum(page->data.data(), PAGE_SIZE);
}

uint32_t StorageEngine::calculateChecksum(const char* data, size_t size) {
    return crc32(data, size);
}

void StorageEngine::flushPage(Page* page) {
    std::string filepath = getPageFilePath(page->page_id);
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing: " + filepath);
    }
    file.write(page->data.data(), PAGE_SIZE);
    page->is_dirty = false;
}

bool StorageEngine::shouldFlushToDisk() {
    return pageCache->getDirtyPageCount() > CACHE_SIZE / 2;
}

StorageEngine::Page* StorageEngine::getPageForWrite(const std::string& table_name) {
    uint32_t page_id = getNextPageId(table_name);
    auto page = new Page{page_id};
    pageCache->put(page);
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
