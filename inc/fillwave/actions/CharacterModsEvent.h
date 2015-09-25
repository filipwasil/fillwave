/*
 * CharacterModsEvent.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Filip Wasil
 */

#ifndef CHARACTERMODSEVENT_H_
#define CHARACTERMODSEVENT_H_

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
   CharacterModsEvent(CharacterModsEventData& data);
   virtual ~CharacterModsEvent();
   };

} /* actions */
} /* fillwave */

#endif /* CHARACTERMODEVENT_H_ */
