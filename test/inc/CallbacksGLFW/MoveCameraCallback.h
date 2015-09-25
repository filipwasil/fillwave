/*
 * MoveCameraCallback.h
 *
 *  Created on: Jun 21, 2014
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

#ifndef MOVECAMERACALLBACK_H_
#define MOVECAMERACALLBACK_H_

#include <fillwave/actions/EngineCallback.h>
#include <fillwave/actions/Event.h>

class GLFWwindow;
namespace fillwave {
class Engine;
namespace actions {

/*! \class MoveCameraCallback
 *
 * \brief Callback to move the current scene's camera.
 *
 */

class MoveCameraCallback: public EngineCallback {
private:
   float mSpeed;
   GLFWwindow* mWindow;
public:
   MoveCameraCallback(eEventType eventType,
                      float speed = 1.0,
                      GLFWwindow* window = nullptr);
   virtual ~MoveCameraCallback();

   /* perform
    * \brief Performs EngineCallback action
    */

   virtual void perform (Engine* engine, EventType* event);
};

} /* actions */
} /* fillwave */

#endif /* MOVECAMERACALLBACK_H_ */
