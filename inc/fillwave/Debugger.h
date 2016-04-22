/*
 * Debugger.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
 *
 * Fillwave C++11 graphics Engine
 *
 * Copyright (C) 2016 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This library is available free of charge for any commercial
 * or non-commercial use. However, You are obligated to put a clearly
 * visible information in Your license agreement that Your Software
 * uses Fillwave library to handle graphics management.
 * If You are interested in extra support, extra features
 * or cooperation I look forward to hearing from You.
 *
 * fillwave@gmail.com
 *
 */


#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace fillwave {
namespace core {
class FramebufferGeometry;
}

enum class eDebuggerState {
   eLightsSpot,
   eLightsSpotColor,
   eLightsSpotDepth,
   eLightsPoint,
   eLightsPointDepth,
   eLightsPointColor,
   ePickingMap,
   eOff,
   eToggleState
};

class Engine;

namespace framework {
class Camera;

/*! \class Debugger
 *
 * \brief Fillwave debugger.
 *
 * - Debugging depth maps
 * - drawing scene from certain views
 * - creating multi-windowed view
 *
 */

class Debugger: public IReloadable {
 public:
	Debugger(Engine* engine);
	virtual ~Debugger() = default;

	void setState(eDebuggerState state);
	eDebuggerState getState();

	void renderFromCamera(ICamera& c, GLint id = 0);
	void renderDepthPerspective(GLint id = 0);
	void renderDepthOrthographic(GLint id = 0);
	void renderPickingMap();
	void renderGeometryBuffer(
	   GLuint width,
	   GLuint height,
	   GLuint attachments,
	   core::FramebufferGeometry* buffer);
	void setMiniwindowSize(GLfloat size);

 private:
	eDebuggerState mState;
	core::Program* mProgram;
	Engine* mEngine;

	core::VertexBufferDebug* mVBO;

	GLfloat mMiniwindowSize;
	GLuint mMiniwindowsOccupied;

	GLint mULCTextureUnit, mULCNearPlane, mULCFarPlane;

	void initBuffers();
	void initPipeline();
	void initVBO();
	void initVAO();
	void initUniformsCache();
};

} /* framework */
typedef std::unique_ptr<framework::Debugger> puDebugger;
} /* fillwave */

#endif /* DEBUGGER_H_ */
