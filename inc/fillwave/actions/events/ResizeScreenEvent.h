/*
 * ResizeScreenEvent.h
 *
 *  Created on: Jan 6, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENEVENT_H_
#define INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENEVENT_H_

#include <fillwave/actions/events/Event.h>

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

class ResizeScreenEvent: public Event<ResizeScreenEventData> {
public:
	ResizeScreenEvent(ResizeScreenEventData& data)
			: Event<ResizeScreenEventData>(data) {

	}
	virtual ~ResizeScreenEvent() = default;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_ACTIONS_EVENTS_RESIZESCREENEVENT_H_ */
