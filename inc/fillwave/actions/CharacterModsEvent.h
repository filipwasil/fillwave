/*
 * CharacterModsEvent.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Filip Wasil
 */

#ifndef CHARACTERMODSEVENT_H_
#define CHARACTERMODSEVENT_H_

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct CharacterModsEventData
 * \brief Event data structure to store the character together with modifier keys.
 */

struct CharacterModsEventData {
	unsigned int character;
	int modsifierKeys;
	const eEventType type = eEventType::characterMods;
};

/*! \struct CharacterModsEvent
 * \brief Event introduced when the key is pressed.
 */

class CharacterModsEvent: public Event<CharacterModsEventData> {
public:
	CharacterModsEvent(CharacterModsEventData& data)
			: Event<CharacterModsEventData>(data) {

	}
	virtual ~CharacterModsEvent() = default;
};

} /* actions */
} /* fillwave */

#endif /* CHARACTERMODEVENT_H_ */
