#pragma once

/*
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

#include <fillwave/common/Finishable.h>
#include <fillwave/actions/events/TEvent.h>
#include <memory>
#include <algorithm>
#include <vector>

namespace flw {
namespace flf {

/*! \class Callback
 * \brief Base for all callbacks.
 */
class Callback : public Finishable {
public:
  Callback(eEventType eventType, float timeToFinish = FILLWAVE_ENDLESS)
      : Finishable(timeToFinish), mEnabled(true), mEventType(eventType) {
  }

  virtual void perform(EventType &event) = 0;

  ~Callback() = default;

  bool isEnabled() {
    return mEnabled;
  }

  void enable() {
    mEnabled = true;
  }

  void disable() {
    mEnabled = false;
  }

  eEventType getEventType() {
    return mEventType;
  }

  template <class T>
  static void handleEvent(std::vector<T> &callbacks, EventType &event) {
    /* Run callbacks */
    for (auto &it : callbacks) {
      if (it->isEnabled()) {
        if (it->getEventType() == event.getType()) {
          it->perform(event);
        }
      }
    }

    /* Erase finished callbacks */
    auto _find_finished_function = [](T &m) -> bool {
      return m->isFinished();
    };
    auto _begin = callbacks.begin();
    auto _end = callbacks.end();
    auto it = std::remove_if(_begin, _end, _find_finished_function);
    callbacks.erase(it, _end);
  }

protected:
  bool mEnabled;
  eEventType mEventType;
};

} /* flf */
typedef std::unique_ptr<flf::Callback> puCallback;
} /* flw */
