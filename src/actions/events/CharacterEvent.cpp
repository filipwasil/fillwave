/*
 * CharacterEvent.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: filip
 */

#include <fillwave/actions/CharacterEvent.h>

namespace fillwave {
namespace actions {


CharacterEvent::CharacterEvent(CharacterEventData& data)
:Event<CharacterEventData>(data) {

}

CharacterEvent::~CharacterEvent() {

}

} /* actions */
} /* fillwave */
