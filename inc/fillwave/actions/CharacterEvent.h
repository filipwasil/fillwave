/*
 * CharacterEvent.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Filip Wasil
 */

#ifndef CHARACTEREVENT_H_
#define CHARACTEREVENT_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/actions/Event.h>

namespace fillwave {
namespace actions {

/*! \struct CharacterEventData
 *
 * \brief Event data structure to store the character.
 *
 */

struct CharacterEventData {
	unsigned int character;
	const eEventType type = eEventType::character;
};

/*! \struct CharacterEvent
 *
 * \brief Event introduced when the key is pressed.
 *
 */

class CharacterEvent: public Event<CharacterEventData> {
public:
	CharacterEvent(CharacterEventData& data);
	virtual ~CharacterEvent();
};

} /* actions */
} /* fillwave */

#endif /* CHARACTEREVENT_H_ */
