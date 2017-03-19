#pragma once

/*
 * CharacterModsEvent.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Filip Wasil
 */

#include <fillwave/actions/events/TEvent.h>

namespace fillwave {
namespace framework {

/*! \struct CharacterModsEventData
 * \brief Event data structure to store the character together with modifier keys.
 */

struct CharacterModsEventData {
  unsigned int character;
  int modsifierKeys;
  const eEventType type = eEventType::eCharacterMods;
};

/*! \struct CharacterModsEvent
 * \brief Event introduced when the key is pressed.
 */

class CharacterModsEvent : public TEvent<CharacterModsEventData> {
public:
  CharacterModsEvent(CharacterModsEventData &data)
      : TEvent<CharacterModsEventData>(data) {

  }

  virtual ~CharacterModsEvent() = default;
};

} /* framework */
} /* fillwave */
