#include "page_cache.h"

namespace mandb {

size_t PageCache::getDirtyPageCount() const {
    size_t count = 0;
    for (const auto& page : lru_list) {
        if (page->is_dirty) count++;
    }
    return count;
}

std::vector<StorageEngine::Page*> PageCache::getAllPages() const {
    std::vector<StorageEngine::Page*> pages;
    pages.reserve(lru_list.size());
    for (auto page : lru_list) {
        pages.push_back(page);
    }
    return pages;
}

} // namespace mandb