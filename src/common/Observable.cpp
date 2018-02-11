/*
* Copyright (c) 2018, Fillwave developers
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

#include <fillwave/common/Observable.h>
#include <vector>
#include <algorithm>

namespace flw {
namespace flf {

Observable::Observable() = default;

Observable::~Observable() {
  for (auto &it : mObservers) {
    it->onDeath(this);
  }
}

Observable::Observable(const Observable &) = default;

Observable& Observable::operator=(const Observable &) = default;

Observable& Observable::operator=(Observable &&) = default;

Observable::Observable (Observable &&) = default;

void Observable::addObserver(IObserver* observer) {
  if (nullptr == observer) {
    return;
  }
  for (auto &it : mObservers) {
    if (it == observer) {
      return;
    }
  }
  mObservers.push_back(observer);
}

void Observable::dropObserver(IObserver* observer) {
  mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
}

void Observable::notifyObservers() {
  for (auto &it : mObservers) {
    it->onChanged(this);
  }
}

} /* flf */
} /* flw */
