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
		: ItemCallback(eEventType::eTime, timeToFinish), mEasing(easing) {
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
		case eEasing::eLinear:
			return progress;

		case eEasing::eSineIn:
			return SineEaseIn(progress);
		case eEasing::eSineOut:
			return SineEaseOut(progress);
		case eEasing::eSineInOut:
			return SineEaseInOut(progress);

		case eEasing::eQuadIn:
			return QuadraticEaseIn(progress);
		case eEasing::eQuadOut:
			return QuadraticEaseOut(progress);
		case eEasing::eQuadInOut:
			return QuadraticEaseInOut(progress);

		case eEasing::eCubicIn:
			return CubicEaseIn(progress);
		case eEasing::eCubicOut:
			return CubicEaseOut(progress);
		case eEasing::eCubicInOut:
			return CubicEaseInOut(progress);

		case eEasing::eQuartIn:
			return QuarticEaseIn(progress);
		case eEasing::eQuartOut:
			return QuarticEaseOut(progress);
		case eEasing::eQuartInOut:
			return QuarticEaseInOut(progress);

		case eEasing::eQuintIn:
			return QuinticEaseIn(progress);
		case eEasing::eQuintOut:
			return QuinticEaseOut(progress);
		case eEasing::eQuintInOut:
			return QuinticEaseInOut(progress);

		case eEasing::eExpoIn:
			return ExponentialEaseIn(progress);
		case eEasing::eExpoOut:
			return ExponentialEaseOut(progress);
		case eEasing::eExpoInOut:
			return ExponentialEaseInOut(progress);

		case eEasing::eCircIn:
			return CircularEaseIn(progress);
		case eEasing::eCircOut:
			return CircularEaseOut(progress);
		case eEasing::eCircInOut:
			return CircularEaseInOut(progress);

		case eEasing::eBackIn:
			return BackEaseIn(progress);
		case eEasing::eBackOut:
			return BackEaseOut(progress);
		case eEasing::eBackInOut:
			return BackEaseInOut(progress);

		case eEasing::eElasticIn:
			return ElasticEaseIn(progress);
		case eEasing::eElastic:
			return ElasticEaseOut(progress);
		case eEasing::eElasticInOut:
			return ElasticEaseInOut(progress);

		case eEasing::eBounceIn:
			return BounceEaseIn(progress);
		case eEasing::eBounce:
			return BounceEaseOut(progress);
		case eEasing::eBounceInOut:
			return BounceEaseInOut(progress);

		case eEasing::eCustom:
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
