#include "storage/page_cache.h"
#include "storage/storage_engine.h"

namespace mandb {

PageCache::PageCache(size_t capacity) : capacity(capacity) {}

void PageCache::put(StorageEngine::Page* page) {
    if (pages.size() >= capacity && !lru_list.empty()) {
        pages.erase(lru_list.front());
        lru_list.pop_front();
    }
    
    unsigned int pageNum = page->page_number;
    pages[pageNum] = std::unique_ptr<StorageEngine::Page>(page);
    lru_list.push_back(pageNum);
}

StorageEngine::Page* PageCache::get(unsigned int pageNumber) {
    auto it = pages.find(pageNumber);
    if (it != pages.end()) {
        auto pos = std::find(lru_list.begin(), lru_list.end(), pageNumber);
        if (pos != lru_list.end()) {
            lru_list.erase(pos);
            lru_list.push_back(pageNumber);
        }
        return it->second.get();
    }
    return nullptr;
}

size_t PageCache::getDirtyPageCount() const {
    size_t count = 0;
    for (const auto& [_, page] : pages) {
        if (page->is_dirty) count++;
    }
    return count;
}

std::vector<StorageEngine::Page*> PageCache::getAllPages() const {
    std::vector<StorageEngine::Page*> result;
    for (const auto& [_, page] : pages) {
        result.push_back(page.get());
    }
    return result;
}

} // namespace mandb