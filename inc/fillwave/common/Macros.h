#pragma once

/*
 * macros.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
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

#include <algorithm>

namespace flw {
namespace flf {

template <class T>
void remove(std::vector<T> &vec, T &item) {
  auto new_end = std::remove_if(vec.begin(), vec.end(), [item](const std::unique_ptr<T> &l) {
    return item == l.get();
  });
  vec.erase(new_end, vec.end());
}

/* Forgive me, but i needed this so badly ... */
template <typename CONTAINER>
void vectorForward(std::unique_ptr<CONTAINER> &) {
}

template <typename CONTAINER, typename TCURRENT, typename... TNEXT>
void vectorForward(std::unique_ptr<CONTAINER> &container, TCURRENT &&t, TNEXT &&... args) {
  container->push_back(std::move(t));
  vectorForward(container, args...);
}

template <typename CONTAINER, typename TCURRENT, typename... TNEXT>
std::unique_ptr<CONTAINER> make_unique_container(TCURRENT &&t, TNEXT &&... args) {
  std::unique_ptr<CONTAINER> container = std::make_unique<CONTAINER>();
  container->push_back(std::move(t));
  vectorForward<CONTAINER>(container, args...);
  return std::move(container);
}

#if (!defined UINT_MAX)
#   define UINT_MAX (~((unsigned int)0))
#endif

#ifdef __unix
static int fopen_s(FILE **f, const char *name, const char *mode) {
    int ret = 0;
    *f = fopen(name, mode);
    if (!*f) {
        ret = errno;
    }
    return ret;
}
#endif

/*
 template<typename T>
 using shared_ptr_unsynchronized = std::__shared_ptr<T, __gnu_cxx::_S_single>;
 */

} /* namespace flf */
} /* namespace flw */
