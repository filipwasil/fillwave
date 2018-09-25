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

#include <memory>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <flw/cmn/Macros.h>

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

} /* flf */
} /* flw */
