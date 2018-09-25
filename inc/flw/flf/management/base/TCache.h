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

constexpr size_t MAX_CACHE_SIZE = 5000;

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
struct TCache final : public std::unordered_map<K, std::unique_ptr<T>> {
  /**
   * \brief Add new allocated item to manager.
   */
  T *store(const K &key, P ... parameters) {
    if ((*this).find(key) != (*this).end()) {
      return (*this)[key].get();
    }
    return (*this).size() >= M ? nullptr : ((*this)[key] = std::make_unique<T>(parameters...)).get();
  }

  /**
   * \brief Add already allocated item to manager.
   */
  T *store(T *item, const K &key) {
    if ((*this).find(key) != (*this).end()) {
      delete item;
      return (*this)[key].get();
    }
    return (*this).size() >= M ? nullptr : ((*this)[key] = std::unique_ptr<T>(item)).get();
  }
};

} /* flf */
} /* flw */
