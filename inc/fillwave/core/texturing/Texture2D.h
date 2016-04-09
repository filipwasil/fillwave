/*
 * Texture.h
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <fillwave/core/texturing/Texture.h>

namespace fillwave {
namespace core {

/*! \class Texture2D
 * \brief Single GLSL 2D Texture object.
 */

class Texture2D: public Texture {
 public:
	Texture2D(
	   Texture2DFile* file,
	   ParameterList& parameters,
	   GLuint howMany = 1);

	virtual ~Texture2D() = default;

	void generateMipMaps();

	void sendData(Texture2DFileData data = nullptr);

	virtual void reload();

	void log();

	static void unbind2DTexture(GLint textureUnit);

	static void unbind2DTextures();

	puTexture2DFile mFile;

 protected:
	ParameterList mParameters;
};

} /* core */
typedef std::shared_ptr<core::Texture2D> pTexture2D;
} /* fillwave */

#endif /* TEXTURE_2D_H_ */
