/*
 * SequenceCallback.cpp
 *
 *  Created on: 14 May 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2012-2015 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/actions/SequenceCallback.h>
#include <fillwave/actions/ItemCallback.h>

namespace fillwave {
namespace actions {

SequenceCallback::SequenceCallback()
:ItemCallback(eEventType::time),
 mCallbackIterator(this->begin()),
 mReloaditerator(true){
}

SequenceCallback::~SequenceCallback() {
   for ( auto it : *this) {
      delete it;
   }
}

void SequenceCallback::perform(EventType* event){
   if (mReloaditerator) {
      mCallbackIterator = this->begin();
      mReloaditerator = false;
   }

   (*mCallbackIterator)->perform(event);
   if ((*mCallbackIterator)->isFinished()) {
      mCallbackIterator++;
   }
   if (mCallbackIterator == end()) {
      finish();
      mCallbackIterator = this->begin();
      for ( auto it : *this) {
         it->reset();
      }
   }
}

} /* actions */
} /* fillwave */
