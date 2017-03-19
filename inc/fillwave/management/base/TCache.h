/*
 * TManagerSmart.h
 *
 *  Created on: Mar 30, 2016
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
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

#pragma once

#include <unordered_map>
#include <fillwave/common/Macros.h>

#define FILLWAVE_FORGET_ABOUT_ME()      \
do {                                    \
   if ((*this).size() >= M) {          \
      /* Too many elements in cache */\
      abort();                        \
      return nullptr;                 \
   }                                   \
} while(0)

namespace fillwave {
namespace framework {

constexpr size_t FILLWAVE_MANAGEMENT_MAX_ITEMS = 5000;

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
class TCache : public std::unordered_map<K, std::unique_ptr<T>> {
public:
  TCache() = default;

  virtual ~TCache() = default;

  T *store(const K &key, P ... parameters) {
    if ((*this).find (key) != (*this).end ()) {
      return (*this)[key].get ();
    }
    FILLWAVE_FORGET_ABOUT_ME();
    return ((*this)[key] = std::make_unique<T> (parameters...)).get ();
  }

  /**
   * \brief Add already allocated item to manager.
   */
  T *store(T *item, const K &key) {
    if ((*this).find (key) != (*this).end ()) {
      delete item;
      return (*this)[key].get ();
    }
    FILLWAVE_FORGET_ABOUT_ME();
    return ((*this)[key] = std::unique_ptr<T> (item)).get ();
  }
};

} /* namespace framework */
} /* namespace fillwave */

#undef FILLWAVE_FORGET_ABOUT_ME