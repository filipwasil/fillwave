/*
 * Skybox.h
 *
 *  Created on: Dec 7, 2014
 *      Author: Filip Wasil
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_

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

#include <fillwave/models/Entity.h>
#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/core/buffers/IndexBufferBasic.h>
#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
class Engine;
namespace models {

/*! \class Skybox
 * \brief Entity which moves with the camera clipping the view space with an image.
 */

class Skybox: public Entity, public Reloadable {
public:
	Skybox(Engine* engine, pTexture3D texture);

	virtual ~Skybox();

	void draw(space::Camera& camera);

	void drawDR(space::Camera& camera);

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

} /* models */
typedef std::shared_ptr<models::Skybox> pSkybox;

static pSkybox buildSkybox(Engine* engine, pTexture3D texture) {
	return pSkybox(new models::Skybox(engine, texture));
}
} /* fillwave */

#endif /* SKYBOX_H_ */
