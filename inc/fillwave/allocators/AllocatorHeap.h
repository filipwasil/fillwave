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
  AllocatorHeap()
    : mCurrentIdx ()
    , mOccupied {0} {
    // nothing
  }

  template <class TAllocatorType>
  AllocatorHeap(AllocatorHeap<TAllocatorType> const& allocator) {
    *this = allocator;
  }

  TValueType* allocate(size_t size) {
    GLubyte* ptr = mBytes + mCurrentIdx * sizeof(TValueType);
    while (0 != mOccupied[(++mCurrentIdx)%mSizeElements]) {

    }
    ptr += mCurrentIdx * sizeof(TValueType);
    return new (ptr) TValueType;
  }
  void deallocate(TValueType* ptr, size_t size) {

  }

 private:
  static constexpr size_t mSizeBytes = 100000;
  static constexpr size_t mSizeElements = mSizeBytes / sizeof(TValueType);
  size_t mCurrentIdx;
  // todo potential optimization, use one bit instead of int. Is it worth it anyway ?
  int mOccupied[mSizeElements];
  GLubyte mBytes[mSizeBytes];
};

template <class TValueType>
bool operator == (AllocatorHeap<TValueType> const& rhs, AllocatorHeap<TValueType> const& lhs);

template <class TValueType>
bool operator != (AllocatorHeap<TValueType> const& rhs, AllocatorHeap<TValueType> const& lhs);

} /* flf */
} /* flw */
