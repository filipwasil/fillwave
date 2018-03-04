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
class AllocatorStack {
 public:
  using value_type = TValueType;
  AllocatorStack() {
    // nothing
  }

  template <class TAllocatorType>
  AllocatorStack(AllocatorStack<TAllocatorType> const& allocator) {
    *this = allocator;
  }

  // todo confirm. Arg means that allocated element id equals size
  TValueType* allocate(size_t size) {
    if (size > mSizeElements) {
      std::cout
        << "Exceeded maximum memory reserved (" << mSizeBytes << " bytes)"
        << " of " << typeid(TValueType).name() << "Stack allocator" << std::endl;
      return nullptr;
    }
    return ::new (mValues) TValueType;
  }

  void deallocate(TValueType* ptr, size_t size) {
    memcpy(mValues, ptr, size);
  }

  static size_t getMaxMemorySize() {
    return mSizeBytes;
  }

 private:
  static constexpr size_t mSizeBytes = 1 << 16;
  static constexpr size_t mSizeElements = mSizeBytes / sizeof(TValueType);
  TValueType mValues[mSizeElements];
};

template <class TValueType>
bool operator == (AllocatorStack<TValueType> const& rhs, AllocatorStack<TValueType> const& lhs) = delete;;

template <class TValueType>
bool operator != (AllocatorStack<TValueType> const& rhs, AllocatorStack<TValueType> const& lhs) = delete;;

} /* flf */
} /* flw */
