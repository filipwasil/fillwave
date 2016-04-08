/*
 * Texture3D.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE3D_H_
#define TEXTURE3D_H_

#include <fillwave/core/texturing/Texture.h>

namespace fillwave {
namespace core {

/*! \class Texture3DFile
 * \brief Stores the single file info.
 */

class Texture3DFile: public Texture2DFile {
  public:
	GLenum mCubeTarget;

	Texture3DFile(Texture2DFile* file, GLenum target) :
		mCubeTarget(target) {
		mHeader = file->mHeader;
		mConfig = file->mConfig;
		mData = file->mData;
	}
};

typedef std::unique_ptr<core::Texture3DFile> puTexture3DFile;

/*! \class Texture3D
 * \brief Single GLSL 3D Texture object.
 * It consists of six 2D images.
 */

class Texture3D: public Texture {
  private:
	void sendData(Texture3DFile* file, Texture2DFileData customData = nullptr);

  public:
	puTexture3DFile mRight; /* Positive X*/
	puTexture3DFile mLeft; /* Negative X*/
	puTexture3DFile mCeil; /* Positive Y*/
	puTexture3DFile mFloor; /* Negative Y*/
	puTexture3DFile mFront; /* Positive Z*/
	puTexture3DFile mBack; /* Negative Z*/

	Texture3D(
	    Texture2DFile* fileRight,
	    Texture2DFile* fileLeft,
	    Texture2DFile* fileCeil,
	    Texture2DFile* fileFloor,
	    Texture2DFile* fileFront,
	    Texture2DFile* fileBack,
	    ParameterList& parameters);

	virtual ~Texture3D() = default;

	void sendData();

	void log();

	static void unbindCubemapTexture(GLint textureUnit);

	static void unbindCubemapTextures();

	void sendData(
	    Texture2DFileData xp,
	    Texture2DFileData xn,
	    Texture2DFileData yp,
	    Texture2DFileData yn,
	    Texture2DFileData zp,
	    Texture2DFileData zn);
};

} /* core */
typedef std::shared_ptr<core::Texture3D> pTexture3D;
} /* fillwave */

#endif /* TEXTURE3D_H_ */
