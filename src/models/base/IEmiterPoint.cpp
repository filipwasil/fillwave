/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fillwave/Fillwave.h>
#include <fillwave/models/base/IEmiterPoint.h>
#include <fillwave/Log.h>

FLOGINIT("Emiter", FERROR | FFATAL)

namespace flw {
namespace flf {

IEmiterPoint::IEmiterPoint(Engine *engine,
    GLuint howMany,
    GLfloat size,
    GLfloat lifetime,
    flc::Texture *texture,
    glm::vec4 color,
    GLenum blendingSource,
    GLenum blendingDestination,
    GLboolean depthTesting,
    GLfloat alphaCutOff)
    : IReloadable(engine)
    , Entity()
    , mStartSize(size)
    , mLifetime(lifetime)
    , mTexture(texture)
    , mColor(color)
    , mHowMany(howMany)
    , mDepthTesting(depthTesting)
    , mAlphaCutOff(alphaCutOff) {
  mBlending.mSrc = blendingSource;
  mBlending.mDst = blendingDestination;

#ifdef FILLWAVE_GLES_3_0
#else
  glEnable(GL_PROGRAM_POINT_SIZE);
  //todo glEnable(GL_POINT_SPRITE) always on since OpenGL 3.2 ... but not at all drivers ://////
  glEnable(GL_POINT_SPRITE);
#endif
  if (glGetError() != GL_NO_ERROR) {
    fLogE("Legacy features may cause a GL_INVALID_ENUM on core profile. It may happen.");
  }

  attachHandler([this] (const Event& event) {
    mCallbackTimePassed += event.getData().mTime.timePassed;
    update(mCallbackTimePassed);
  }, EEventType::time );
}

void IEmiterPoint::setBlending(GLenum sourceFactor, GLenum destinationFactor) {
  mBlending.mSrc = sourceFactor;
  mBlending.mDst = destinationFactor;
}

void IEmiterPoint::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
