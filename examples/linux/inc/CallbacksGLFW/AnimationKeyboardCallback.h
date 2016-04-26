/*
 * AnimationKeyboardCallback.h
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

#ifndef ANIMATIONKEYBOARDCALLBACK_H_
#define ANIMATIONKEYBOARDCALLBACK_H_

#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Framework.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class AnimationKeyboardCallback
 *
 * \brief EngineCallback to change current animation.
 *
 * This callback, when attached to a model, can change
 * the current active animation.
 *
 */

class AnimationKeyboardCallback: public Callback{
public:
   AnimationKeyboardCallback(Entity* entity, eEventType eventType);
   virtual ~AnimationKeyboardCallback();
   void perform (EventType& event);
private:
   Entity* mEntity;
   };
} /* framework */
} /* fillwave */

#endif /* ANIMATIONKEYBOARDCALLBACK_H_ */
