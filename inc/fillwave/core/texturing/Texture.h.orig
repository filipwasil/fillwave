/*
 * Texture.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <fillwave/core/GLObject.h>

#include <fillwave/core/texturing/Parameter.h>

#include <memory>

#if __APPLE__ or _WIN32
#include <stdlib.h>
#endif

namespace fillwave {
namespace core {

typedef GLubyte* Texture2DFileData;

/*! \class Texture2DFileConfig
 * \brief Stores the single file configuration info.
 */

class Texture2DFileConfig {
public:
	Texture2DFileConfig(GLint level = 0, GLint border = 0, GLboolean mipmaps =
	GL_FALSE, GLboolean compression = GL_FALSE);
	GLint mMipmapsLevel;
	GLboolean mMipmaps;
	GLboolean mCompression;
	GLint mBorder;
	GLsizei mCompressionSize;
};

/*! \class Texture2DFileHeader
 * \brief Stores the single file header info.
 */

class Texture2DFileHeader {
public:
	Texture2DFileHeader(
			GLint internalFormat = GL_RGBA,
			GLint format = GL_RGBA,
			GLint type = GL_UNSIGNED_BYTE,
			GLsizei width = 0,
			GLsizei height = 0);
	GLint mInternalFormat;
	GLsizei mHeight;
	GLsizei mWidth;
	GLenum mType;
	GLenum mFormat;
};

/*! \enum eMemoryAllocation
 * \brief Stores the type of memory free method
 */

enum class eMemoryAllocation {
	eMallock, eNew, eNone
};

/*! \class Texture2DFile
 * \brief Stores the single file info.
 */

class Texture2DFile {
public:
	Texture2DFileHeader mHeader;
	Texture2DFileConfig mConfig;
	Texture2DFileData mData;
	eMemoryAllocation mAllocation = eMemoryAllocation::eNone;
	virtual ~Texture2DFile() {
		switch (mAllocation) {
			case eMemoryAllocation::eMallock:
				free(mData);
				break;
			case eMemoryAllocation::eNew:
				delete mData;
				mData = nullptr;
				break;
			case eMemoryAllocation::eNone:
				break;
		}
	}
};

/*! \class Texture
 * \brief Textures base class
 */

//class
class Texture: public GLObject {
public:
	Texture(GLenum textureTarget = GL_TEXTURE_2D, GLsizei howMany = 1);

	virtual ~Texture();

	virtual void bind(GLuint id = 0);
	virtual void bind(GLint textureUnit, GLuint id = 0);
	virtual void unbind();

	void generateMipMaps();
	void setParameter(GLenum parameter, GLenum value);
	void setParameters(ParameterList paramers);

	virtual GLint getTarget();
	virtual void reload();

	virtual void log() = 0;
protected:
	GLenum mTarget;
};

void bindTexture(GLuint target, GLuint handle);
void bindTexture(GLint textureUnit, GLuint target, GLuint handle);
void unbindTexture(GLuint target);

} /* core */
typedef std::shared_ptr<core::Texture> pTexture;
typedef std::unique_ptr<core::Texture2DFile> puTexture2DFile;
} /* fillwave */

#endif /* TEXTURE_H_ */
