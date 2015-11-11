/*
 * TimedCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/Callback.h>
#include <fillwave/actions/TimedCallback.h>
#include <fillwave/common/Easing.h>
#include <iostream>

namespace fillwave {
namespace actions {

TimedCallback::TimedCallback(GLfloat timeToFinish, eEasing easing)
		: ItemCallback(eEventType::time, timeToFinish), mEasing(easing) {
}

void TimedCallback::perform(EventType* event) {
	TimeEventData e = TimeEvent::getData(event);
	performTime(e);
	checkTime(e.mTimePassed);
}

void TimedCallback::performTime(TimeEventData&) {
	// just wait
}

GLfloat TimedCallback::ease(GLfloat progress) {
	switch (mEasing) {
		case eEasing::None:
			return progress;

		case eEasing::SineIn:
			return SineEaseIn(progress);
		case eEasing::SineOut:
			return SineEaseOut(progress);
		case eEasing::SineInOut:
			return SineEaseInOut(progress);

		case eEasing::QuadIn:
			return QuadraticEaseIn(progress);
		case eEasing::QuadOut:
			return QuadraticEaseOut(progress);
		case eEasing::QuadInOut:
			return QuadraticEaseInOut(progress);

		case eEasing::CubicIn:
			return CubicEaseIn(progress);
		case eEasing::CubicOut:
			return CubicEaseOut(progress);
		case eEasing::CubicInOut:
			return CubicEaseInOut(progress);

		case eEasing::QuartIn:
			return QuarticEaseIn(progress);
		case eEasing::QuartOut:
			return QuarticEaseOut(progress);
		case eEasing::QuartInOut:
			return QuarticEaseInOut(progress);

		case eEasing::QuintIn:
			return QuinticEaseIn(progress);
		case eEasing::QuintOut:
			return QuinticEaseOut(progress);
		case eEasing::QuintInOut:
			return QuinticEaseInOut(progress);

		case eEasing::ExpoIn:
			return ExponentialEaseIn(progress);
		case eEasing::ExpoOut:
			return ExponentialEaseOut(progress);
		case eEasing::ExpoInOut:
			return ExponentialEaseInOut(progress);

		case eEasing::CircIn:
			return CircularEaseIn(progress);
		case eEasing::CircOut:
			return CircularEaseOut(progress);
		case eEasing::CircInOut:
			return CircularEaseInOut(progress);

		case eEasing::BackIn:
			return BackEaseIn(progress);
		case eEasing::BackOut:
			return BackEaseOut(progress);
		case eEasing::BackInOut:
			return BackEaseInOut(progress);

		case eEasing::ElasticIn:
			return ElasticEaseIn(progress);
		case eEasing::Elastic:
			return ElasticEaseOut(progress);
		case eEasing::ElasticInOut:
			return ElasticEaseInOut(progress);

		case eEasing::BounceIn:
			return BounceEaseIn(progress);
		case eEasing::Bounce:
			return BounceEaseOut(progress);
		case eEasing::BounceInOut:
			return BounceEaseInOut(progress);

		case eEasing::Custom:
			return easeCustom(progress);
		default:
			return progress;
	};
	return progress;
}

GLfloat TimedCallback::easeCustom(GLfloat progress) {
	return progress;
}

} /* actions */
} /* fillwave */
