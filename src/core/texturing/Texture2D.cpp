/*
 * Texture2D.cpp
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Texture2D", FERROR | FFATAL | FDEBUG)

namespace fillwave {
namespace core {

Texture2D::Texture2D(puTexture2DFile file,
                     ParameterList& parameters,
                     GLuint howMany)
:Texture(GL_TEXTURE_2D, howMany),
 mFile(std::move(file)),
 mParameters(parameters) {
   reload();
}

Texture2D::~Texture2D() {

}

void Texture2D::sendData(Texture2DFileData data) {
   if (data) {
      mFile->mData = data;
   }
   glTexImage2D(mTarget,
         mFile->mConfig.mMipmapsLevel,
         mFile->mHeader.mInternalFormat,
         mFile->mHeader.mWidth,
         mFile->mHeader.mHeight,
         mFile->mConfig.mBorder,
         mFile->mHeader.mFormat,
         mFile->mHeader.mType,
   (GLubyte*)mFile->mData);
   FLOG_CHECK("send data");
}

void Texture2D::generateMipMaps() {
   if(mFile->mConfig.mMipmaps) {
      glGenerateMipmap(mTarget);
      FLOG_CHECK("generateMipMaps");
   }
}

void Texture2D::unbind2DTexture(GLint textureUnit) {
   glActiveTexture(textureUnit);
   glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::unbind2DTextures() {
   glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::reload() {
   FLOG_DEBUG("Reload");
   Texture::reload();
   for (GLuint i = 0; i < mHowMany; i++) {
      bind(i);
      setParameters(mParameters);
      sendData();
      generateMipMaps();
//      unbind();
   }
}

void Texture2D::log() {

}

} /* core */
} /* fillwave */
