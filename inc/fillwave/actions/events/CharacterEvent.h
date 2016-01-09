/*
 * CharacterEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CHARACTEREVENT_H_
#define CHARACTEREVENT_H_

#include <fillwave/actions/events/Event.h>

namespace fillwave {
namespace framework {

/*! \struct CharacterEventData
 * \brief Event data structure to store the character.
 */

struct CharacterEventData {
	unsigned int character;
	const eEventType type = eEventType::eCharacter;
};

/*! \struct CharacterEvent
 * \brief Event introduced when the key is pressed.
 */

class CharacterEvent: public Event<CharacterEventData> {
public:
	CharacterEvent(CharacterEventData& data)
			: Event<CharacterEventData>(data) {

	}
	virtual ~CharacterEvent() = default;
};

} /* framework */
} /* fillwave */

#endif /* CHARACTEREVENT_H_ */
