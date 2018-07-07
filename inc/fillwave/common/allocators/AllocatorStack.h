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

#include <fillwave/OpenGL.h>
#include <memory>
#include <array>

namespace flw {
namespace flf {

/*
 * Limitations
 *
 * - TValueType must have a default cconstructor
 * - Size is limited to  1kB
 *
 * */

template <class TValueType>
class AllocatorStack {

 public:

  using value_type = TValueType;

  using pointer = TValueType*;

  using difference_type = typename std::pointer_traits<pointer>::difference_type;

  using size_type = std::make_unsigned_t<difference_type>;

  using propagate_on_container_copy_assignment = std::true_type;

  using propagate_on_container_move_assignment = std::true_type;

  using propagate_on_container_swap = std::true_type;

  using is_always_equal = std::true_type;

  AllocatorStack() noexcept {
    // nothing
  }

  AllocatorStack(AllocatorStack const& allocator) noexcept {
    *this = allocator;
  }

  template <class TAllocatorType>
  AllocatorStack(const AllocatorStack<TAllocatorType> & allocator) noexcept {
    // nothing
  }

  ~AllocatorStack() {
    // nothing
  }

  template <class... Args>
  void construct(TValueType* p, Args&& ... args) {
    *p = TValueType(std::forward<Args...>(args...));
  }

  void destroy(TValueType* ) {
    // nothing
  }

  size_type max_size() {
    return mSizeElements;
  }

  TValueType* allocate(size_t) {
    return static_cast<TValueType*>(mValues.data());
  }

  void deallocate(TValueType*, size_t) {
    // nothing
  }

 private:

  static constexpr size_t mSizeBytes = 1 << 10;

  static constexpr size_t mSizeElements = mSizeBytes / sizeof(TValueType);

  std::array<TValueType, mSizeElements> mValues;
};

template <class TValueType>
bool operator == (AllocatorStack<TValueType> const&, AllocatorStack<TValueType> const&) {
  return true;
}

template <class TValueType>
bool operator != (AllocatorStack<TValueType> const&, AllocatorStack<TValueType> const&) {
  return false;
}

} /* flf */
} /* flw */