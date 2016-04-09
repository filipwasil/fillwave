/*
 * Texture2DRenderableDynamic.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>

FLOGINIT("Texture2DRenderableDynamic", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2DRenderableDynamic::Texture2DRenderableDynamic(
   Texture2DFile* file,
   ParameterList& parameters,
   core::Program* program) :
	Texture2DRenderable(
	   GL_COLOR_ATTACHMENT0, file, parameters),
	mProgram(program),
	mTimePassed(0.0f) {
	initUniformsCache();
}

void Texture2DRenderableDynamic::draw(GLfloat timePassed) {
	mTimePassed += timePassed;
	mProgram->use();
	bind(FILLWAVE_DIFFUSE_UNIT);
	core::Uniform::push(mUniformLocationCacheTime, mTimePassed);
	glEnable(GL_BLEND);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
	unbind();
	core::Program::disusePrograms();
}

void Texture2DRenderableDynamic::initUniformsCache() {
	mUniformLocationCacheTime = mProgram->getUniformLocation("uTime");
	mUniformLocationCachePostprocessingSampler = mProgram->getUniformLocation(
	         "uPostProcessingSampler");
}

void Texture2DRenderableDynamic::reload() {
	FLOG_DEBUG("Reload");
	Texture2DRenderable::reload();
	initUniformsCache();
}

} /* core */
} /* fillwave */
