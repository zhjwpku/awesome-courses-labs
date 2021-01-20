#include <list>
#include <utility>
#include <iostream>

#include "hash/extendible_hash.h"
#include "page/page.h"

#define GET_BUCKET_ID(key, len) (key & (((1U << len) - 1)))
#define GET_MASK(depth) ((1U << depth) - 1)

namespace cmudb {

/*
 * constructor
 * array_size: fixed array size for each bucket
 */
template <typename K, typename V>
ExtendibleHash<K, V>::ExtendibleHash(size_t size) {
  global_depth = 0;
  bucket_size = size;
  bucket *buk = new bucket(0, 0);
  buckets.push_back(buk);
}

/*
 * helper function to calculate the hashing address of input key
 */
template <typename K, typename V>
size_t ExtendibleHash<K, V>::HashKey(const K &key) {
  return std::hash<K>{}(key);
}

/*
 * helper function to return global depth of hash table
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetGlobalDepth() const {
  std::unique_lock<std::mutex> lock(mtx);
  return global_depth;
}

/*
 * helper function to return local depth of one specific bucket
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetLocalDepth(int bucket_id) const {
  std::unique_lock<std::mutex> lock(mtx);
  return buckets[bucket_id]->local_depth;
}

/*
 * helper function to return current number of bucket in hash table
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetNumBuckets() const {
  std::unique_lock<std::mutex> lock(mtx);
  return buckets.size();
}

/*
 * lookup function to find value associate with input key
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Find(const K &key, V &value) {
  std::unique_lock<std::mutex> lock(mtx);
  size_t slot = HashKey(key) & GET_MASK(global_depth);
  // std::cout << key << '\t' << slot << std::endl;
  auto iter = buckets[slot]->data.find(key);
  if (iter == buckets[slot]->data.end()) {
    return false;
  }

  value = iter->second;
  return true;
}

/*
 * delete <key,value> entry in hash table
 * Shrink & Combination is not required for this project
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Remove(const K &key) {
  std::unique_lock<std::mutex> lock(mtx);
  size_t slot = HashKey(key) & GET_MASK(global_depth);
  return buckets[slot]->data.erase(key) > 0;
}

/*
 * insert <key,value> entry in hash table
 * Split & Redistribute bucket when there is overflow and if necessary increase
 * global depth
 */
template <typename K, typename V>
void ExtendibleHash<K, V>::Insert(const K &key, const V &value) {
  std::unique_lock<std::mutex> lock(mtx);
  size_t slot = HashKey(key) & ((1 << global_depth) - 1);
  bucket *buk = buckets[slot];
  if (buk->data.size() >= bucket_size) {
    int bucket_id = buk->bucket_id;
    assert(bucket_id >= 0);
    int new_bucket_id = bucket_id | 1 << (buk->local_depth);
    buk->local_depth ++;
    bucket *new_buk = new bucket(buk->local_depth, new_bucket_id);
    if (buk->local_depth > global_depth) { // double the vector
      assert(buk->local_depth == global_depth + 1);
      global_depth ++;
      auto origin_size = buckets.size();
      buckets.resize(origin_size << 1);
      for (size_t i = origin_size, j = 0; i < buckets.size(); i++, j++) {
        buckets[i] = buckets[j];
      }
    }

    /* split the bucket */
    for (auto &ele: buk->data) {
      if (GET_BUCKET_ID(HashKey(ele.first), global_depth) != bucket_id) {
        new_buk->data.insert(ele);
      }
    }

    for (auto &ele: new_buk->data) {
      buk->data.erase(ele.first);
    }

    /* assign new bucket pointer to buckets slots */
    int step = 1 << (global_depth - buk->local_depth + 1);
    int cnt = global_depth - buk->local_depth;
    for (int i = 0; i <= cnt; i ++) {
      buckets[new_bucket_id] = new_buk;
      new_bucket_id += step;
    }

    // print();
    lock.unlock();  // have to unlock to insert iteratively
    Insert(key, value);
  } else {
    buk->data.insert(std::make_pair(key, value));
    // print();
  }
}

template <typename K, typename V>
void ExtendibleHash<K, V>::print() {
  std::cout << "-------" << std::endl;
  for (size_t i = 0; i < buckets.size(); i++) {
    bucket *buk = buckets[i];
    std::cout << i << ": " << buk->local_depth << std::endl;
    for (auto &ele: buk->data) {
      std::cout << '\t' << ele.first << std::endl;
    }
  }
}

template class ExtendibleHash<page_id_t, Page *>;
template class ExtendibleHash<Page *, std::list<Page *>::iterator>;
// test purpose
template class ExtendibleHash<int, std::string>;
template class ExtendibleHash<int, std::list<int>::iterator>;
template class ExtendibleHash<int, int>;
} // namespace cmudb
