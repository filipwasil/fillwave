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

#include <memory>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <fillwave/common/Macros.h>

namespace flw {
namespace flf {

/*! \class TManager
 * \brief Basic manager
 */
template <class T, size_t M, typename ... P>
class TManager : public std::vector<std::unique_ptr<T>> {
public:

  TManager() = default;

  virtual ~TManager() = default;

  T *add(P ... parameters) {
    if ((*this).size() >= M) {
      return nullptr;
    }
    (*this).emplace_back(std::make_unique<T>(parameters...));
    return (*this).back().get();
  }

  bool isNew(T &item) {
    for (auto &it : (*this)) {
      if (it == item) {
        return false;
      }
    }
    return true;
  }

  void log() {
    for (auto &it : (*this)) {
      it->log();
    }
  }
};

} /* namespace flf */
} /* namespace flw */
