/*
 * Skybox.h
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <fillwave/models/Entity.h>
#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/base/IReloadable.h>

namespace fillwave {
class Engine;
namespace framework {
class Skybox;

typedef framework::PtrShared<framework::Skybox> pSkybox;
/*! \class Skybox
 * \brief Entity which moves with the camera clipping the view space with an image.
 */

class Skybox: public Entity, public IReloadable {
 public:
	Skybox(Engine* engine, core::Texture3D* texture);

	virtual ~Skybox() = default;

	/* IDrawable */
	void draw(ICamera& camera);
	void drawDR(ICamera& camera);

	/* IRenderable */
	bool getRenderItem(RenderItem& item);

	static pSkybox build(Engine* engine, core::Texture3D* texture);

 protected:
	core::Program* mProgram;
	core::Program* mProgramDR;

 private:
	core::Texture3D* mTexture;
	core::VertexBufferPosition* mVBO;
	core::IndexBuffer* mIBO;
	GLint mULCCameraPosition, mULCModelMatrixPosition, mULCViewProjectionMatrix,
	      mULCTextureUnit;

	void initBuffers();
	void initPipeline();
	void initUniformsCache();
	void initVAO();
	void initVBO();
};

} /* framework */
} /* fillwave */

#endif /* SKYBOX_H_ */
