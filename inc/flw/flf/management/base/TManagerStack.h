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

/**
 * \brief Basic manager of composites
 *
 * \param T - Stored item type
 *
 * \param M - Maximum items
 *
 * \param K - Key class
 *
 * \param P - T constructor parameters
 */
template <class T, class K, size_t M, typename ... P>
class TCacheStack : public std::unordered_map<K, T> {
public:
  TCacheStack() = default;

  virtual ~TCacheStack() = default;

  T &store(const K &key, P ... parameters) {
    if ((*this).find(key) != (*this).end()) {
      return (*this)[key];
    }

    if ((*this).size() >= M) {
      abort();
    }

    return (*this)[key] = T(parameters...);
  }
};

} /* flf */
} /* flw */
