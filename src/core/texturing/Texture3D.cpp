/*
 * Texture3D.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/common/Macros.h>
#include <fillwave/Log.h>

FLOGINIT("Texture3D", FERROR | FFATAL)

namespace fillwave {
namespace core {

Texture3D::Texture3D(
		Texture2DFile* fileRight,
		Texture2DFile* fileLeft,
		Texture2DFile* fileCeil,
		Texture2DFile* fileFloor,
		Texture2DFile* fileFront,
		Texture2DFile* fileBack,
		ParameterList& parameters)
		:
				Texture(GL_TEXTURE_CUBE_MAP),
				mRight(framework::make_unique<Texture3DFile>(fileRight,
				GL_TEXTURE_CUBE_MAP_POSITIVE_X)),
				mLeft(framework::make_unique<Texture3DFile>(fileLeft,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X)),
				mCeil(framework::make_unique<Texture3DFile>(fileCeil,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y)),
				mFloor(framework::make_unique<Texture3DFile>(fileFloor,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)),
				mFront(framework::make_unique<Texture3DFile>(fileFront,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z)),
				mBack(framework::make_unique<Texture3DFile>(fileBack,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)) {
	bind();
	setParameters(parameters);
	sendData();
	unbind();
}

inline void Texture3D::sendData(
		Texture3DFile* file,
		Texture2DFileData customData) {

	if (customData) {
		file->mData = customData;
	}

	FLOG_DEBUG("file->mCubeTarget 0x%x", file->mCubeTarget);
	FLOG_DEBUG("file->mConfig.mMipmapsLevel %d", file->mConfig.mMipmapsLevel);
	FLOG_DEBUG("file->mHeader.mInternalFormat 0x%x",
			file->mHeader.mInternalFormat);
	FLOG_DEBUG("file->mHeader.mWidth %d", file->mHeader.mWidth);
	FLOG_DEBUG("file->mHeader.mHeight %d", file->mHeader.mHeight);
	FLOG_DEBUG("file->mConfig.mBorder %d", file->mConfig.mBorder);
	FLOG_DEBUG("file->mHeader.mFormat 0x%x", file->mHeader.mFormat);
	FLOG_DEBUG("file->mHeader.mType 0x%x", file->mHeader.mType);
	glTexImage2D(file->mCubeTarget, file->mConfig.mMipmapsLevel,
			file->mHeader.mInternalFormat, file->mHeader.mWidth,
			file->mHeader.mHeight, file->mConfig.mBorder, file->mHeader.mFormat,
			file->mHeader.mType, (GLubyte*) file->mData);
	FLOG_CHECK("send data");
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

}

void Texture3D::sendData(
		Texture2DFileData xp,
		Texture2DFileData xn,
		Texture2DFileData yp,
		Texture2DFileData yn,
		Texture2DFileData zp,
		Texture2DFileData zn) {

	sendData(mRight.get(), xp);
	sendData(mLeft.get(), xn);
	sendData(mCeil.get(), yp);
	sendData(mFloor.get(), yn);
	sendData(mFront.get(), zp);
	sendData(mBack.get(), zn);

	FLOG_CHECK("send data");
}

} /* core */
} /* fillwave */
