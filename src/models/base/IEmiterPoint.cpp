/*
 * IEmiterPoint.cpp
 *
 *  Created on: 16 Jun 2014
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


#include <fillwave/Fillwave.h>
#include <fillwave/models/base/IEmiterPoint.h>
#include <fillwave/Log.h>

FLOGINIT("Emiter", FERROR | FFATAL)

namespace fillwave {
namespace framework {

IEmiterPoint::IEmiterPoint(Engine *engine,
    GLuint howMany,
    GLfloat size,
    GLfloat lifetime,
    core::Texture *texture,
    glm::vec4 color,
    GLenum blendingSource,
    GLenum blendingDestination,
    GLboolean depthTesting,
    GLfloat alphaCutOff)
    : IReloadable (engine), Entity (), mStartSize (size), mLifetime (lifetime), mTexture (texture), mColor (color)
    , mHowMany (howMany), mDepthTesting (depthTesting), mAlphaCutOff (alphaCutOff) {
  mBlending.mSrc = blendingSource;
  mBlending.mDst = blendingDestination;

#ifdef FILLWAVE_GLES_3_0
#else
  glEnable (GL_PROGRAM_POINT_SIZE);
  // glEnable(GL_POINT_SPRITE) always on since OpenGL 3.2 ... but not at all drivers ://////
  glEnable (GL_POINT_SPRITE);
#endif
  if (glGetError () != GL_NO_ERROR) {
    fLogE("Legacy features may cause a GL_INVALID_ENUM on core profile. It may happen.");
  }
}

void IEmiterPoint::setBlending(GLenum sourceFactor, GLenum destinationFactor) {
  mBlending.mSrc = sourceFactor;
  mBlending.mDst = destinationFactor;
}

void IEmiterPoint::updateRenderer(IRenderer &renderer) {
  renderer.update (this);
}

} /* framework */
} /* fillwave */
