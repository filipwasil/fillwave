/*
 * AnimationKeyboardCallback.cpp
 *
 *  Created on: Sep 20, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
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
 * filip.wasil@gmail.com
 *
 */

#include "../../../linux/inc/CallbacksGLFW/AnimationKeyboardCallback.h"


namespace fillwave {
namespace framework {

AnimationKeyboardCallback::AnimationKeyboardCallback(
		Entity* entity,
		eEventType EventType)
		: Callback(EventType),
		  mEntity(entity) {
}

AnimationKeyboardCallback::~AnimationKeyboardCallback() {
}

void AnimationKeyboardCallback::perform(EventType& event) {
   KeyboardEventData e = KeyboardEvent::getData(event);
   if (mEntity) {
      Model* model = static_cast<Model*>(mEntity);
      switch (e.key) {
         case GLFW_KEY_Q:
            model->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);
            break;
         case GLFW_KEY_0:
            model->setActiveAnimation(0);
            break;
         case GLFW_KEY_1:
            model->setActiveAnimation(1);
            break;
         case GLFW_KEY_2:
            model->setActiveAnimation(2);
            break;
         case GLFW_KEY_3:
            model->setActiveAnimation(3);
            break;
         case GLFW_KEY_4:
            model->setActiveAnimation(4);
            break;
         case GLFW_KEY_5:
            model->setActiveAnimation(5);
            break;
         case GLFW_KEY_6:
            model->setActiveAnimation(6);
            break;
         case GLFW_KEY_7:
            model->setActiveAnimation(7);
            break;
         case GLFW_KEY_8:
            model->setActiveAnimation(8);
            break;
         case GLFW_KEY_9:
            model->setActiveAnimation(9);
            break;
         default:
            break;
      }
   }
}

} /* framework */
} /* fillwave */
