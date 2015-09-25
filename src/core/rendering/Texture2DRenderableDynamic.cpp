/*
 * Texture2DRenderableDynamic.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: Filip Wasil
 */

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
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>

FLOGINIT("Texture2DRenderableDynamic", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2DRenderableDynamic::Texture2DRenderableDynamic(puTexture2DFile file,
                                                       ParameterList& parameters,
                                                       pProgram program)
:Texture2DRenderable(GL_COLOR_ATTACHMENT0,
 std::move(file),
 parameters),
 mProgram(program),
 mTimePassed(0.0f) {
   initUniformsCache();
}

Texture2DRenderableDynamic::~Texture2DRenderableDynamic() {

}

void Texture2DRenderableDynamic::draw(GLfloat timePassed) {
   mTimePassed+=timePassed;
   mProgram->use();
   bind(FILLWAVE_DIFFUSE_UNIT);
   core::Uniform::push(mUniformLocationCacheTime, mTimePassed);
   glEnable (GL_BLEND);
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   glDisable (GL_BLEND);
   unbind();
   core::Program::disusePrograms();
}

void Texture2DRenderableDynamic::initUniformsCache() {
   mUniformLocationCacheTime = mProgram->getUniformLocation("uTime");
   mUniformLocationCachePostprocessingSampler = mProgram->getUniformLocation("uPostProcessingSampler");
}

void Texture2DRenderableDynamic::reload() {
   FLOG_DEBUG("Reload");
   Texture2DRenderable::reload();
   initUniformsCache();
}

} /* core */
} /* fillwave */
