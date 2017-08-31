/*
 * SequenceCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/actions/callbacks/Callback.h>
#include <fillwave/actions/callbacks/SequenceCallback.h>

namespace flw {
namespace flf {

SequenceCallback::SequenceCallback()
    : Callback(EEventType::eTime)
    , mCallbackIterator(this->begin())
    , mReloaditerator(true) {
}

void SequenceCallback::perform(EventType &event) {
  if (mReloaditerator) {
    mCallbackIterator = this->begin();
    mReloaditerator = false;
  }

  (*mCallbackIterator)->perform(event);
  if ((*mCallbackIterator)->isFinished()) {
    mCallbackIterator++;
  }
  if (mCallbackIterator == end()) {
    finish();
    mCallbackIterator = this->begin();
    for (auto &it : *this) {
      it->reset();
    }
  }
}

} /* flf */
} /* flw */
