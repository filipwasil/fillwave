/*
 * ResizeScreenEvent.h
 *
 *  Created on: Jan 6, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENTEVENT_H_
#define INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENTEVENT_H_

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct ResizeScreenEventData
 * \brief Event data structure to store the new windows size.
 */

struct ResizeScreenEventData {
	unsigned int width;
	unsigned int height;
	const eEventType type = eEventType::eResizeScreen;
};

/*! \struct ResizeScreenEvent
 * \brief Event introduced when the window is resized.
 */

class ResizeScreenEvent: public TEvent<ResizeScreenEventData> {
  public:
	ResizeScreenEvent(ResizeScreenEventData& data) :
		TEvent(data) {

	}
	virtual ~ResizeScreenEvent() = default;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENTEVENT_H_ */
