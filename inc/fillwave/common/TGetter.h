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
/*! \class TGetter
 * \brief Wrapper which makes the wrapped pointer not storable and not copyable
 */
template <class TPtr>
class TGetter {
private:
  class TGetterHelper {
    friend class TGetter;
  public:
    TGetterHelper(TPtr *ptr)
        : mPtr(ptr) {
    }

    TPtr *operator->() && {
      return mPtr;
    }

  private:

    TGetterHelper(TGetterHelper &&) = default;

    TGetterHelper(const TGetter &) = delete;

    TGetterHelper operator = (TGetterHelper getter) = delete;

    TGetterHelper operator = (TGetterHelper &&getter) = delete;

    TPtr *operator->()& = delete;

    TPtr *mPtr;
  };

public:
  TGetter(TPtr* p)
      : mHelper(p) {

  }

  TGetterHelper && operator->() && {
    return std::move(mHelper);
  }

  TGetter(TGetter &&) = default;

  TGetter(const TGetter &) = delete;

  TGetter *operator->()& = delete;

  TGetter operator = (TGetter getter) = delete;

  TGetter operator = (TGetter &&getter) = delete;

private:
  TGetterHelper mHelper;
};
} /* flw */
