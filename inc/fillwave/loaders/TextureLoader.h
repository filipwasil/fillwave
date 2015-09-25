/*
 * TextureLoader.h
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

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

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/Math.h>
#include <iostream>

namespace fillwave {
namespace loader {

enum class eFlip{
   FILLWAVE_TEXTURE_FLIP_NONE,
   FILLWAVE_TEXTURE_FLIP_HORIZONTAL,
   FILLWAVE_TEXTURE_FLIP_VERTICAL,
   FILLWAVE_TEXTURE_FLIP_HORIZONTAL_VERTICAL,
};

/*! \class TextureLoader
 * \brief Loads texture files.
 */

class TextureLoader {
public:
	TextureLoader();

	virtual ~TextureLoader();
	core::Texture2DFile* load(const std::string& filePath,
	                          eFlip flip = eFlip::FILLWAVE_TEXTURE_FLIP_NONE,
	                          GLenum format = GL_RGBA,
	                          std::string rootPath = "");

	core::Texture2DFile* loadEmpty(glm::ivec2 screenSize,
	                               GLenum format = GL_RGBA);

	core::Texture2DFile* loadVirtualFileCheckboard(GLuint width,
	                                               GLuint height,
	                                               GLubyte red,
	                                               GLubyte green,
	                                               GLubyte blue,
	                                               GLenum format = GL_RGBA);

	core::Texture2DFile* loadVirtualFileColor(GLuint width,
	                                          GLuint height,
	                                          GLubyte red,
	                                          GLubyte green,
	                                          GLubyte blue,
	                                          GLenum format = GL_RGBA);

	GLint getBytesPerPixel(GLenum format);
};

} /* loader */
typedef std::unique_ptr<loader::TextureLoader> puTextureLoader;
} /* fillwave */

#endif /* TEXTURELOADER_H_ */
