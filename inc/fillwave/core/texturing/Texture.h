/*
 * Texture.h
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

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
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/GLObject.h>

#include <fillwave/core/texturing/Parameter.h>

#include <memory>

#if __APPLE__
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
   Texture2DFileConfig(GLint level = 0,
                       GLint border = 0,
                       GLboolean mipmaps = GL_FALSE,
                       GLboolean compression = GL_FALSE,
                       GLenum compressionType = GL_NONE);
   GLint mMipmapsLevel;
   GLboolean mMipmaps;
   GLint mBorder;
   GLboolean mCompression;
   GLenum mCompressionType;
};

/*! \class Texture2DFileHeader
 * \brief Stores the single file header info.
 */

class Texture2DFileHeader {
public:
   Texture2DFileHeader(GLint internalFormat = GL_RGBA,
                       GLint format = GL_RGBA,
                       GLint type = GL_UNSIGNED_BYTE,
                       GLsizei width = 0,
                       GLsizei height = 0);
   GLenum mFormat;
   GLint mInternalFormat;
   GLsizei mWidth;
   GLsizei mHeight;
   GLenum mType;
};

/*! \enum eMemoryAllocation
 * \brief Stores the type of memory free method
 */

enum class eMemoryAllocation {
   C,
   CPP,
   None
};

/*! \class Texture2DFile
 * \brief Stores the single file info.
 */

class Texture2DFile {
public:
   Texture2DFileHeader mHeader;
   Texture2DFileConfig mConfig;
   Texture2DFileData mData;
   eMemoryAllocation mAllocation = eMemoryAllocation::None;
   virtual ~Texture2DFile() {
      switch (mAllocation) {
      case eMemoryAllocation::C:
         free(mData);
         break;
      case eMemoryAllocation::CPP:
         delete mData;
         mData = nullptr;
         break;
      case eMemoryAllocation::None:
         break;
      }
   }
};

/*! \class Texture
 * \brief Textures base class
 */

//class
class Texture : public GLObject {
public:
   Texture(GLenum textureTarget = GL_TEXTURE_2D, GLsizei howMany = 1);

   virtual ~Texture();

   virtual void bind(GLuint id = 0);

   virtual void bind(GLint textureUnit, GLuint id = 0);

   virtual void unbind();

   void generateMipMaps();

   void setParameter(GLenum parameter,GLenum value);

   void setParameters(ParameterList paramers);

   GLuint getMapType();

   void setMapType(GLuint mapType);

   virtual GLint getTarget();

   virtual void log() = 0;

   virtual void reload();

protected:
   GLenum mTarget;

private:
   GLuint mMapType;
};

} /* core */
typedef std::shared_ptr<core::Texture> pTexture;
typedef std::unique_ptr<core::Texture2DFile> puTexture2DFile;
} /* fillwave */

#endif /* TEXTURE_H_ */
