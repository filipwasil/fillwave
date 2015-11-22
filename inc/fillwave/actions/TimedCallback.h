/*
 * TimedCallback.h
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#ifndef TIMEDCALLBACK_H_
#define TIMEDCALLBACK_H_

#include <fillwave/OpenGL.h>
#include <fillwave/actions/ItemCallback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/models/Moveable.h>

namespace fillwave {

enum class eEasing {
	None,

	SineIn, SineOut, SineInOut,

	QuadIn, QuadOut, QuadInOut,

	CubicIn, CubicOut, CubicInOut,

	QuartIn, QuartOut, QuartInOut,

	QuintIn, QuintOut, QuintInOut,

	ExpoIn, ExpoOut, ExpoInOut,

	CircIn, CircOut, CircInOut,

	BackIn, BackOut, BackInOut,

	ElasticIn, Elastic, ElasticInOut,

	BounceIn, Bounce, BounceInOut,

	Custom
};

namespace actions {

/*! \class TimedCallback
 *
 * \brief ItemCallback to be finished after a period of time.
 *
 */

class TimedCallback: public ItemCallback {
public:
	TimedCallback(GLfloat timeToFinish, eEasing easing = eEasing::None);

	virtual ~TimedCallback() = default;

	/*	perform
	 * \brief Performs ItemCallback action.
	 */

	void perform(EventType* eventType);

	virtual void performTime(TimeEventData& e);

	virtual GLfloat easeCustom(GLfloat progress);

	GLfloat ease(GLfloat progress);

private:
	eEasing mEasing;
};

} /* actions */
} /* fillwave */

#endif /* TIMEDCALLBACK_H_ */

