/*
 * Skybox.cpp
 *
 *  Created on: Dec 7, 2014
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

#include <fillwave/models/Skybox.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/models/shapes/SphereSkybox.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Skybox", FERROR | FFATAL)

namespace fillwave {
namespace models {

Skybox::Skybox(Engine* engine, pTexture3D texture)
		: Reloadable(engine), mTexture(texture) {

	loader::ProgramLoader loader;

	mProgram = loader.getSkybox(engine);
	mProgramDR = loader.getSkyboxDR(engine);

	models::SphereSkybox sphere(1.0, 10, 10);

	std::vector<GLuint> indices = sphere.getIndices();
	std::vector<core::VertexPosition> vertices = sphere.getVertices();

	FLOG_DEBUG("Initializing skybox buffer");

	mIBO = pIndexBufferBasic(new core::IndexBufferBasic(indices));
	mVBO = pVertexBufferPosition(new core::VertexBufferPosition(vertices));

	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

Skybox::~Skybox() {

}

void Skybox::draw(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();

	mProgram->use();

	core::Uniform::push(mULCCameraPosition, camera.getTranslation());
	core::Uniform::push(mULCModelMatrixPosition, mTransformation);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	mVAO->bind();

	mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

	glFrontFace(GL_CW);
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(GL_TRIANGLES, mIBO->getElements(), GL_UNSIGNED_INT,
				(GLvoid*) 0);
	} else {
		/* Perform array drawing */
		glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
	}
	glFrontFace(GL_CCW);

	core::Texture2D::unbind2DTextures();

	mVAO->unbind();
	core::Program::disusePrograms();
}

void Skybox::drawDR(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();

	mProgramDR->use();

	core::Uniform::push(mULCCameraPosition, camera.getTranslation());
	core::Uniform::push(mULCModelMatrixPosition, mTransformation);
	core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
	core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

	mVAO->bind();

	mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

	glFrontFace(GL_CW);
	if (mIBO) {
		/* Perform index drawing */
		glDrawElements(GL_TRIANGLES, mIBO->getElements(), GL_UNSIGNED_INT,
				(GLvoid*) 0);
	} else {
		/* Perform array drawing */
		glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
	}
	glFrontFace(GL_CCW);

	core::Texture2D::unbind2DTextures();

	mVAO->unbind();
	core::Program::disusePrograms();
}

inline void Skybox::initBuffers() {
	if (mIBO) {
		mIBO->reload();
	}
	if (mVBO) {
		mVBO->reload();
	}
}

inline void Skybox::initPipeline() {

}

inline void Skybox::initUniformsCache() {
	mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
	mULCModelMatrixPosition = mProgram->getUniformLocation("uModelMatrix");
	mULCViewProjectionMatrix = mProgram->getUniformLocation(
			"uViewProjectionMatrix");
	mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

inline void Skybox::initVAO() {
	mSampler->bind();
	mVAO->bind();

	mVBO->bind();
	mVBO->attributesSetForVAO();
	mVBO->setReady();
	mVBO->send();
	if (mIBO) {
		mIBO->bind();
		mIBO->setReady();
		mIBO->send();
	}
	mVAO->unbind();
}

inline void Skybox::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

} /* core */
} /* fillwave */
