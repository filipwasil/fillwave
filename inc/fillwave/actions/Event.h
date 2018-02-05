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
namespace flf {

enum class eEventType {
  mouseButton
  , cursorPosition
  , cursorEnter
  , scroll
  , key
  , character
  , characterMods
  , time
  , touch
  , resizeScreen
  , custom
};

struct CursorEnterEventData {
	int direction;
};

struct CursorPositionEventData {
	double xPosition;
	double yPosition;
};

struct KeyboardEventData {
	int key;
  int scanCode;
  int action;
  int mode;
};

struct MouseButtonEventData {
	float whereX;
  float whereY;
	int button;
	int action;
	int mods;
};

struct MouseScrollEventData {
	double offsetX;
	double offsetY;
};

struct CharacterEventData {
	unsigned int character;
};

struct ResizeScreenEventData {
	unsigned int width;
	unsigned int height;
};

struct TouchEventData {
	int xPos;
	int yPos;
	int action;
};

struct TimeEventData {
	float timePassed;
};

union CustomEventData {
	float* dataFloat;
	int* dataInt;
	unsigned int* dataUint;
	char* dataChar;
	unsigned int size;
};

union EventData {
	CursorEnterEventData mCursorEnter;
	CursorPositionEventData mCursorPosition;
	KeyboardEventData mKey;
	MouseButtonEventData mMouseButton;
	MouseScrollEventData mMouseScroll;
	CharacterEventData mChar;
	ResizeScreenEventData mResize;
	TouchEventData mTouch;
	TimeEventData mTime;
	CustomEventData mCustom;

	operator CursorEnterEventData () const {
		return mCursorEnter;
	}

	operator CursorPositionEventData () const {
		return mCursorPosition;
	}

	operator KeyboardEventData () const {
		return mKey;
	}

	operator MouseButtonEventData () const {
		return mMouseButton;
	}

	operator MouseScrollEventData () const {
		return mMouseScroll;
	}

	operator CharacterEventData () const {
		return mChar;
	}

	operator ResizeScreenEventData () const {
		return mResize;
	}

	operator TouchEventData () const {
		return mTouch;
	}

	operator TimeEventData () const {
		return mTime;
	}

	operator CustomEventData () const {
		return mCustom;
	}
};

/*!
 * \brief Event
 */

class Event {
 public:
	Event(eEventType type, EventData data)
			: mType(type)
			, mData(data) {
    // nothing
	}

	eEventType getType() const {
		return mType;
	}

	EventData getData() const {
		return mData;
	}

 private:
	eEventType mType;
	EventData mData;
};

} /* flf */
} /* flw */
