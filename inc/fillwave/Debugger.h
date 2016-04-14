/*
 * Debugger.h
 *
 *  Created on: Jul 26, 2014
 *      Author: Filip Wasil
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
