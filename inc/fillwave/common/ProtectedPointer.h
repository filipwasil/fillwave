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

namespace flw {
/*! \class ProtectedPointer
 * \brief Wrapper which makes the wrapped pointer not storable and not copyable
 */
template <class TPtr>
class ProtectedPointer {
 private:
  class Helper {
    friend class ProtectedPointer;
   public:
    Helper(TPtr* ptr)
      : mPtr(ptr) {
    }

    TPtr* operator->() && {
      return mPtr;
    }

   private:

    Helper(Helper &&) = default;

    Helper(const ProtectedPointer &) = delete;

    Helper operator = (Helper) = delete;

    Helper operator = (Helper&&) = delete;

    TPtr* operator->()& = delete;

    TPtr* mPtr;
  };

 public:
  ProtectedPointer(TPtr* p)
    : mHelper(p) {

  }

  Helper && operator->() && {
    return std::move(mHelper);
  }

  ProtectedPointer(ProtectedPointer &&) = default;

  ProtectedPointer(const ProtectedPointer &) = delete;

  ProtectedPointer* operator->()& = delete;

  ProtectedPointer operator = (ProtectedPointer getter) = delete;

  ProtectedPointer operator = (ProtectedPointer&& getter) = delete;

 private:
  Helper mHelper;
};
} /* flw */
