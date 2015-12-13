/*
 * FPSCallback.h
 *
 *  Created on: Jan 1, 2015
 *      Author: Filip Wasil
 */

#ifndef FPSCALLBACK_H_
#define FPSCALLBACK_H_

#include <fillwave/actions/Callback.h>
#include <fillwave/actions/TimeEvent.h>
#include <fillwave/actions/Callback.h>
#include <fillwave/models/Text.h>

namespace fillwave {
class Engine;
namespace actions {

/*! \class FPSCallback
 * \brief ItemCallback to display and refresh FPS as a renderable text.
 */

class FPSCallback: public Callback {
public:
	FPSCallback(Engine* engine, pText text);
	virtual ~FPSCallback() = default;
	void perform(EventType& event);

private:
	pText mText;
	GLfloat mTimePassed;
	Engine* mEngine;
};

} /* actions */
} /* fillwave */

#endif /* FPSCALLBACK_H_ */
