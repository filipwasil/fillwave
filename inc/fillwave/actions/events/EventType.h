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

namespace flw {

enum class EEventType {
  eMouseButton
  , eCursorPosition
  , eCursorEnter
  , eScroll
  , eKey
  , eCharacter
  , eCharacterMods
  , eTime
  , eTouch
  , eResizeScreen
  , eCustom0
  , eCustom1
  , eCustom2
  , eCustom3
  , eCustom4
  , eCustom5
  , eCustom6
  , eCustom7
  , eCustom8
  , eCustom9
  , eCustom10
  , eCustom11
  , eCustom12
  , eCustom13
  , eCustom14
  , eCustom15
};

namespace flf {

/*! \class EventType
 * \brief Base class for all events.
 * This class needs only the event type (literally - an enumerator)
 * to initialize. Event type defines by which callback the event will be handled.
 */

class EventType {
public:
  EventType(EEventType type)
      : mType(type) {
  }

  virtual ~EventType() = default;

  EEventType getType() {
    return mType;
  }

private:
  EEventType mType;
};

} /* flf */
} /* flw */
