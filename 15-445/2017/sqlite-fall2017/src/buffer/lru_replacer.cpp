/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace cmudb {

template <typename T> LRUReplacer<T>::LRUReplacer() {}

template <typename T> LRUReplacer<T>::~LRUReplacer() {}

/*
 * Insert value into LRU
 */
template <typename T> void LRUReplacer<T>::Insert(const T &value) {
  std::unique_lock<std::mutex> lock(mtx);
  auto iter = umap.find(value);
  if (iter != umap.end()) { // exists
    lst.splice(lst.begin(), lst, iter->second);
  } else {
    umap[value] = lst.insert(lst.begin(), value);
  }
}

/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
template <typename T> bool LRUReplacer<T>::Victim(T &value) {
  std::unique_lock<std::mutex> lock(mtx);
  if (umap.size() > 0) {
    value = lst.back();
    umap.erase(value);
    lst.pop_back();
    return true;
  }
  return false;
}

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
  std::unique_lock<std::mutex> lock(mtx);
  auto iter = umap.find(value);
  if (iter != umap.end()) {
    lst.erase(iter->second);
    umap.erase(value);
    return true;
  }
  return false;
}

template <typename T> size_t LRUReplacer<T>::Size() {
  std::unique_lock<std::mutex> lock(mtx);
  return umap.size();
}

template class LRUReplacer<Page *>;
// test only
template class LRUReplacer<int>;

} // namespace cmudb
