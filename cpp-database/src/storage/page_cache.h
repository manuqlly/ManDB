#pragma once
#include "storage/storage_engine.h"
#include <unordered_map>
#include <memory>
#include <list>
#include <vector>

namespace mandb {

class PageCache {
public:
    explicit PageCache(size_t capacity);
    void put(StorageEngine::Page* page);
    StorageEngine::Page* get(unsigned int pageNumber);
    size_t getDirtyPageCount() const;
    std::vector<StorageEngine::Page*> getAllPages() const;

private:
    size_t capacity;
    std::unordered_map<unsigned int, std::unique_ptr<StorageEngine::Page>> pages;
    std::list<unsigned int> lru_list;
};

} // namespace mandb