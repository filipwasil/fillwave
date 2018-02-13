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
namespace flf {

enum class EEventType {
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
	Event(EEventType type, EventData data)
			: mType(type)
			, mData(data) {
    // nothing
	}

	EEventType getType() const {
		return mType;
	}

	EventData getData() const {
		return mData;
	}

 private:
	EEventType mType;
	EventData mData;
};

} /* flf */
} /* flw */
