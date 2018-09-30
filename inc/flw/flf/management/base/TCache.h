#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <unordered_map>

namespace flw {
namespace flf {

constexpr size_t MAX_CACHE_SIZE = 1000;

/**
 * \brief Basic manager of composites
 *
 * \param T - Item type
 *
 * \param K - Key class
 *
 * \param M - Maximum items
 *
 * \param P - T constructor parameters
 */

template <size_t M, class T, class K, typename ... P>
struct TCache final {
 private:
  std::unordered_map<K, std::unique_ptr<T>> mStored;

 public:
  /**
   * \brief Add new allocated item to manager.
   */
  T *store(const K &key, const P&... parameters) {
    if (mStored.find(key) != mStored.end()) {
      return mStored[key].get();
    }
    if (mStored.size() >= M) {
      return nullptr;
    }
    mStored[key] = std::make_unique<T>(parameters...);
    return mStored[key].get();
  }

  /**
   * \brief Add already allocated item to manager.
   */
  T *store(T *item, const K &key) {
    if (mStored.find(key) != mStored.end()) {
      if (nullptr != item) {
        delete item;
      }
      return mStored[key].get();
    }
    if (mStored.size() >= M) {
      return nullptr;
    }
    mStored[key] = std::unique_ptr<T>(item);
    return mStored[key].get();
  }

  /**
   * \brief return nullptr when item not present
   */
  T* get(const K &key) {
    if (mStored.find(key) != mStored.end()) {
      return mStored[key].get();
    }
    return nullptr;
  }

  /**
   * \brief begin
   */
  decltype(std::begin(mStored)) begin() {
    return std::begin(mStored);
  }

  /**
   * \brief end
   */
  decltype(std::end(mStored)) end() {
    return std::end(mStored);
  }

  /**
   * \brief erase
   */
  decltype(mStored.erase(K())) erase (const K& key) {
    return mStored.erase(key);
  }

  /**
   * \brief return current size
   */
  size_t size() {
    return mStored.size();
  }
};

} /* flf */
} /* flw */
