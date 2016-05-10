/*
 * Texture2DRenderableDynamic.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/Log.h>

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
