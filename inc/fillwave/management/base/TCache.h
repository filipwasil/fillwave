#pragma once

/*
* Copyright (c) 2017, Fillwave developers
* All rights reserved.
*
* Fillwave C++14 graphics engine.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
