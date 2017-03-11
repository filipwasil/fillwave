#pragma once

/*
 * CharacterEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/actions/events/TEvent.h>

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

class CharacterEvent: public TEvent<CharacterEventData> {
 public:
	CharacterEvent(CharacterEventData& data) :
		TEvent(data) {

	}
	virtual ~CharacterEvent() = default;
};

} /* framework */
} /* fillwave */