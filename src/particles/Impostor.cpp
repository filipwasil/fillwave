/*
 * Impostor.cpp
 *
 *  Created on: May 10, 2014
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


#include <fillwave/particles/Impostor.h>
#include <fillwave/Fillwave.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Impostor", FERROR | FFATAL)

namespace fillwave {
namespace particles {

Impostor::Impostor(Engine* engine,
                   GLfloat lifetime,
                   GLfloat size,
                   pTexture texture,
                   GLenum blendingSource,
                   GLenum blendingDestination)
:models::Entity(glm::mat4(1.0)),
 Finishable(lifetime),
 mSize(size),
 mTexture(texture),
 mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)){
   mBlending.mSource = blendingSource;
   mBlending.mDestination = blendingDestination;
}

Impostor::~Impostor() {

}

void Impostor::coreDraw() {
   if (mTexture) {
      mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
   }

   glEnable (GL_BLEND);
   glBlendFunc(mBlending.mSource, mBlending.mDestination);
   glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
   glDisable (GL_BLEND);
   core::Texture2D::unbind2DTextures();
}

void Impostor::draw(space::Camera& camera) {

}

} /* models */
} /* fillwave */
