/*
 * IRenderer.h
 *
 *  Created on: Dec 31, 2015
 *      Author: filip
 */

#ifndef INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_
#define INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_

#include <fillwave/OpenGL.h>
#include <fillwave/models/base/IRenderable.h>
#include <memory>

namespace fillwave {
namespace framework {

class ICamera;
class Entity;
class Skybox;

/*! \class IRenderer
 * \brief Base for all renderers.
 */

class IRenderer {
 public:
	IRenderer() :
		mFlagReload(true), mSkybox(nullptr) {

	}

	virtual ~IRenderer() = default;

	virtual void update(IRenderable* renderable) = 0;
	virtual void draw(ICamera& camera) = 0;
	virtual void reset(GLuint width, GLuint height) = 0;
	virtual void clear() = 0;

	bool mFlagReload;
	Skybox* mSkybox;
	GLfloat mAmbientGlobal[3];
};

} /* namespace framework */
typedef std::unique_ptr<framework::IRenderer> puIRenderer;
} /* namespace fillwave */

#endif /* INC_FILLWAVE_CORE_RENDERERS_RENDERER_H_ */
