/*
 * TextureLoader.h
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/Math.h>
#include <iostream>

namespace fillwave {
namespace framework {

enum class eFlip {
    eNone, eHorizontal, eVertical, eHorizontal_vertical,
};

// generic formats
//GL_COMPRESSED_RED,
//GL_COMPRESSED_RG,
//GL_COMPRESSED_RGB,
//GL_COMPRESSED_RGBA.
//GL_COMPRESSED_SRGB,
//GL_COMPRESSED_SRGB_ALPHA.

// extented formats
//GL_COMPRESSED_LUMINANCE_LATC1_EXT
//GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT
//GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT
//GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT

//GL_COMPRESSED_RED_RGTC1_EXT
//GL_COMPRESSED_SIGNED_RED_RGTC1_EXT
//GL_COMPRESSED_RED_GREEN_RGTC2_EXT
//GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT

//GL_COMPRESSED_RGB_S3TC_DXT1_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
//GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

enum class eCompression {
    eNone,
    eGeneric_r,
    eGeneric_rg,
    eGeneric_rgb,
    eGeneric_rgba,
    eGeneric_srgb,
    eGeneric_srgba,
    eLatc_luminance,
    eLatc_luminance_signed,
    eLatc_luminance_alpha,
    eLatc_luminance_alpha_signed,
    eRgtc1_r,
    eRgtc1_r_signed,
    eRgtc1_rg,
    eRgtc1_rg_signed,
    eS3tc_dxt1_rgb,
    eS3tc_dxt1_rgba,
    eS3tc_dxt3_rgba,
    eS3tc_dxt5_rgba,
};

/*! \class TextureLoader
 * \brief Loads texture files.
 */

class TextureLoader {
  public:
	TextureLoader() = default;

	virtual ~TextureLoader() = default;
	core::Texture2DFile* load(
	    const std::string& filePath,
	    eFlip flip = eFlip::eNone,
	    GLenum format = GL_RGBA,
	    std::string rootPath = "",
	    eCompression compression = eCompression::eNone);

	core::Texture2DFile* loadEmpty(
	    glm::ivec2 screenSize,
	    GLenum format = GL_RGBA);

	core::Texture2DFile* loadVirtualFileCheckboard(
	    GLuint width,
	    GLuint height,
	    GLubyte red,
	    GLubyte green,
	    GLubyte blue,
	    GLenum format = GL_RGBA);

	core::Texture2DFile* loadVirtualFileColor(
	    GLuint width,
	    GLuint height,
	    GLubyte red,
	    GLubyte green,
	    GLubyte blue,
	    GLenum format = GL_RGBA);

  private:
	GLint getBytesPerPixel(GLenum format);
	GLenum getComporession(eCompression compression);
};

} /* framework */
} /* fillwave */

#endif /* TEXTURELOADER_H_ */
