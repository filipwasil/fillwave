/*
 * TManagerStack.h
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

#ifndef INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_
#define INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_

#include <unordered_map>

namespace fillwave {
namespace framework {

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
    if ((*this).find (key) != (*this).end ()) {
      return (*this)[key];
    }

    if ((*this).size () >= M) {
      abort ();
    }

    return (*this)[key] = T (parameters...);
  }
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MANAGEMENT_BASE_TMANAGERSTACK_H_ */
