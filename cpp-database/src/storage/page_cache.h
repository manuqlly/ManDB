#pragma once
#include <list>
#include <unordered_map>
#include "storage_engine.h"

namespace mandb {

class PageCache {
public:
    PageCache(size_t capacity);
    
    StorageEngine::Page* get(uint32_t page_id);
    void put(StorageEngine::Page* page);
    void remove(uint32_t page_id);
    void clear();
    size_t getDirtyPageCount() const;
    std::vector<StorageEngine::Page*> getAllPages() const;

private:
    size_t capacity;
    std::list<StorageEngine::Page*> lru_list;
    std::unordered_map<uint32_t, std::list<StorageEngine::Page*>::iterator> cache_map;
    
    void evict();
};

}