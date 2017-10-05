/*
 * Texture3D.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/Log.h>

FLOGINIT("Texture3D", FERROR | FFATAL)

namespace flw {
namespace flc {

Texture3D::Texture3D(Texture2DFile *fileRight,
    Texture2DFile *fileLeft,
    Texture2DFile *fileCeil,
    Texture2DFile *fileFloor,
    Texture2DFile *fileFront,
    Texture2DFile *fileBack,
    ParameterList &parameters)
    : Texture(GL_TEXTURE_CUBE_MAP)
    , mRight(std::make_unique<Texture3DFile>(fileRight, GL_TEXTURE_CUBE_MAP_POSITIVE_X))
    , mLeft(std::make_unique<Texture3DFile>(fileLeft, GL_TEXTURE_CUBE_MAP_NEGATIVE_X))
    , mCeil(std::make_unique<Texture3DFile>(fileCeil, GL_TEXTURE_CUBE_MAP_POSITIVE_Y))
    , mFloor(std::make_unique<Texture3DFile>(fileFloor, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y))
    , mFront(std::make_unique<Texture3DFile>(fileFront, GL_TEXTURE_CUBE_MAP_POSITIVE_Z))
    , mBack(std::make_unique<Texture3DFile>(fileBack, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)) {
  bind();
  setParameters(parameters);
  sendData();
  unbind();
}

inline void Texture3D::sendData(flc::Texture3DFile* file, GLubyte* customData) {

  if (customData) {
    file->mData = customData;
  }

  fLogD("file->mCubeTarget 0x%x", file->mCubeTarget);
  fLogD("file->mConfig.mMipmapsLevel %d", file->mConfig.mMipmapsLevel);
  fLogD("file->mHeader.mInternalFormat 0x%x", file->mHeader.mInternalFormat);
  fLogD("file->mHeader.mWidth %d", file->mHeader.mWidth);
  fLogD("file->mHeader.mHeight %d", file->mHeader.mHeight);
  fLogD("file->mConfig.mBorder %d", file->mConfig.mBorder);
  fLogD("file->mHeader.mFormat 0x%x", file->mHeader.mFormat);
  fLogD("file->mHeader.mType 0x%x", file->mHeader.mType);
  glTexImage2D(file->mCubeTarget,
               file->mConfig.mMipmapsLevel,
               file->mHeader.mInternalFormat,
               file->mHeader.mWidth,
               file->mHeader.mHeight,
               file->mConfig.mBorder,
               file->mHeader.mFormat,
               file->mHeader.mType,
               (GLubyte *) file->mData);
  fLogC("send data");
}

void Texture3D::sendData() {
  sendData(mRight.get());
  sendData(mLeft.get());
  sendData(mCeil.get());
  sendData(mFloor.get());
  sendData(mFront.get());
  sendData(mBack.get());
}

void Texture3D::unbindCubemapTextures() {
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::unbindCubemapTexture(GLint textureUnit) {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::log() {
  // nothing
}

void Texture3D::sendData(GLubyte* xp,
    GLubyte* xn,
    GLubyte* yp,
    GLubyte* yn,
    GLubyte* zp,
    GLubyte* zn) {

  sendData(mRight.get(), xp);
  sendData(mLeft.get(), xn);
  sendData(mCeil.get(), yp);
  sendData(mFloor.get(), yn);
  sendData(mFront.get(), zp);
  sendData(mBack.get(), zn);

  fLogC("send data");
}

} /* flc */
} /* flw */
