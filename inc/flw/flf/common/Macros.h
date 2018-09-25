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

#include <algorithm>
#include <memory>
#include <vector>

namespace flw {
namespace flf {

template <class T>
void remove(std::vector<T> &vec, T &item) {
  auto new_end = std::remove_if(vec.begin(), vec.end(), [item](const std::unique_ptr<T> &l) {
    return item == l.get();
  });
  vec.erase(new_end, vec.end());
}

template <typename TContainer>
void vectorForward(std::unique_ptr<TContainer> &) {
}

template <typename TContainer, typename TCurrent, typename... TNext>
void vectorForward(std::unique_ptr<TContainer> &container, TCurrent &&t, TNext &&... args) {
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

/*
 template<typename T>
 using shared_ptr_unsynchronized = std::__shared_ptr<T, __gnu_cxx::_S_single>;
 */

} /* flf */
} /* flw */

#ifdef __unix
int fopen_s(FILE **f, const char *name, const char *mode);
#else
#include <stdio.h>
#endif
