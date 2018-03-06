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

namespace flw {
namespace flf {

template <class TValueType>
class AllocatorHeap {
 public:
  using value_type = TValueType;
  using propagate_on_container_move_assignment = std::true_type;
  using is_always_equal = std::true_type;

  AllocatorHeap() noexcept
    : mSizeBytes (1 << 14)
    , mSizeElements (mSizeBytes / sizeof(TValueType))
    , mValues (new GLubyte[mSizeBytes]) {
    // nothing
  }

  AllocatorHeap(AllocatorHeap const& allocator) noexcept {
    *this = allocator;
  }

  template <class TAllocatorType>
  AllocatorHeap(AllocatorHeap<TAllocatorType> const& allocator) noexcept {
    *this = allocator;
  }

  virtual ~AllocatorHeap() {
    delete [] mValues;
  }

  TValueType* allocate(size_t size) {
    if (size > mSizeElements) {
      // container overloaded
      return nullptr;
    }
    return ::new (mValues) TValueType;
  }

  void deallocate(TValueType*, size_t) {
    // nothing
  }

  size_t getMaxMemorySize() {
    return mSizeBytes;
  }

 private:
  size_t mSizeBytes;
  size_t mSizeElements;
  GLubyte* mValues;
};

template <class TValueType>
bool operator == (AllocatorHeap<TValueType> const& , AllocatorHeap<TValueType> const&) {
  return true;
}

template <class TValueType>
bool operator != (AllocatorHeap<TValueType> const&, AllocatorHeap<TValueType> const&) {
  return false;
}

} /* flf */
} /* flw */
