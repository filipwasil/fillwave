/*
 * Debugger.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
 */

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

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

#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace fillwave {
namespace space {
class Camera;
}

enum class eDebuggerState {
   lightsSpot,
   lightsSpotColor,
   lightsSpotDepth,
   lightsPoint,
   lightsPointDepth,
   lightsPointColor,
   pickingMap,
   off,
   toggleState
};

class Engine;

/*! \class Debugger
 *
 * \brief Fillwave debugger.
 *
 * - Debugging depth maps
 * - drawing scene from certain views
 * - creating multi-windowed view
 *
 */

class Debugger : public models::Reloadable {
public:
   Debugger(Engine* engine);
   virtual ~Debugger();

   void setState(eDebuggerState state);
   eDebuggerState getState();

   void renderFromCamera(space::Camera& c, GLint id = 0);
   void renderDepthPerspective(GLint id = 0);
   void renderDepthOrthographic(GLint id = 0);
   void renderPickingMap();
   void renderGeometryBuffer(GLuint width,
   		                     GLuint height,
   		                     GLuint attachments,
   		                     core::FramebufferGeometry* buffer);
   void setMiniwindowSize(GLfloat size);

private:
   eDebuggerState mState;
   pProgram mProgram;
   Engine* mEngine;

   pVertexBufferDebug mVBO;

   GLfloat mMiniwindowSize;
   GLuint mMiniwindowsOccupied;

   GLint mULCTextureUnit,
         mULCNearPlane,
         mULCFarPlane;

   void initBuffers();

   void initPipeline();

   void initVBO();

   void initVAO();

   void initUniformsCache();
};

typedef std::unique_ptr<Debugger> puDebugger;
} /* fillwave */

#endif /* DEBUGGER_H_ */
