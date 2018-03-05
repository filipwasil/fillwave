#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sll copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "fillwave/loaders/TextureConfigs.h"
#include <iostream>
#include <memory>

namespace flw {
namespace flf {

enum class EFlip {
  none
  , horizontal
  , vertical
  , horizontalVertical
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

enum class ECompression {
  none
  , generic_r
  , generic_rg
  , generic_rgb
  , generic_rgba
  , generic_srgb
  , generic_srgba
  , latc_luminance
  , latc_luminance_signed
  , latc_luminance_alpha
  , latc_luminance_alpha_signed
  , rgtc1_r
  , rgtc1_r_signed
  , rgtc1_rg
  , rgtc1_rg_signed
  , s3tc_dxt1_rgb
  , s3tc_dxt1_rgba
  , s3tc_dxt3_rgba
  , s3tc_dxt5_rgba
};

/*! \class Textureloader
 * \brief Loads texture files.
 */

class TextureLoader {
public:
  TextureLoader();

  flc::TextureConfig* load(const std::string &filePath,
      EFlip flip = EFlip::none,
      GLenum format = GL_RGBA,
      std::string rootPath = "",
      ECompression compression = ECompression::none,
      GLenum cubeTarget = 0);

  flc::TextureConfig* loadEmpty(GLint screenWidth, GLint screenHeight, GLenum format = GL_RGBA);
  flc::TextureConfig* loadVirtualFileCheckboard(GLuint width, GLuint height, GLubyte red, GLubyte green, GLubyte blue, GLenum format = GL_RGBA);
  flc::TextureConfig* loadVirtualFileColor(GLuint width, GLuint height, GLubyte red, GLubyte green, GLubyte blue, GLenum format = GL_RGBA);

private:
  GLint getBytesPerPixel(GLenum format);

  GLenum getCompression(ECompression compression);
};

} /* flw */
} /* flf */
