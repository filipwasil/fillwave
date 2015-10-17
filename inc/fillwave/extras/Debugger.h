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

class Debugger: public models::Reloadable {
public:
	Debugger(Engine* engine);
	virtual ~Debugger() = default;

	void setState(eDebuggerState state);
	eDebuggerState getState();

	void renderFromCamera(space::Camera& c, GLint id = 0);
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
	pProgram mProgram;
	Engine* mEngine;

	pVertexBufferDebug mVBO;

	GLfloat mMiniwindowSize;
	GLuint mMiniwindowsOccupied;

	GLint mULCTextureUnit, mULCNearPlane, mULCFarPlane;

	void initBuffers();

	void initPipeline();

	void initVBO();

	void initVAO();

	void initUniformsCache();
};

typedef std::unique_ptr<Debugger> puDebugger;
} /* fillwave */

#endif /* DEBUGGER_H_ */
