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
#include <fillwave/core/buffers/IndexBufferBasic.h>
#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/base/Reloadable.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class Skybox
 * \brief Entity which moves with the camera clipping the view space with an image.
 */

class Skybox: public Entity, public Reloadable {
public:
	Skybox(Engine* engine, pTexture3D texture);

	virtual ~Skybox() = default;

	void draw(ICamera& camera);
	void drawDR(ICamera& camera);

protected:
	pProgram mProgram;
	pProgram mProgramDR;

private:
	pTexture3D mTexture;
	pVertexBufferPosition mVBO;
	pIndexBufferBasic mIBO;
	GLint mULCCameraPosition, mULCModelMatrixPosition, mULCViewProjectionMatrix,
			mULCTextureUnit;

	void initBuffers();
	void initPipeline();
	void initUniformsCache();
	void initVAO();
	void initVBO();
};

} /* framework */
typedef std::shared_ptr<framework::Skybox> pSkybox;

static pSkybox buildSkybox(Engine* engine, pTexture3D texture) {
	return std::make_shared<framework::Skybox>(engine, texture);
}
} /* fillwave */

#endif /* SKYBOX_H_ */
