#pragma once

/*
* Copyright (c) 2017, Fillwave developers
* All rights reserved.
*
* Fillwave C++14 graphics engine.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <fillwave/core/texturing/Texture.h>
#include <iostream>

namespace flw {
namespace flf {

enum class eFlip {
  eNone
  , eHorizontal
  , eVertical
  , eHorizontal_vertical
  , };

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
  eNone
  , eGeneric_r
  , eGeneric_rg
  , eGeneric_rgb
  , eGeneric_rgba
  , eGeneric_srgb
  , eGeneric_srgba
  , eLatc_luminance
  , eLatc_luminance_signed
  , eLatc_luminance_alpha
  , eLatc_luminance_alpha_signed
  , eRgtc1_r
  , eRgtc1_r_signed
  , eRgtc1_rg
  , eRgtc1_rg_signed
  , eS3tc_dxt1_rgb
  , eS3tc_dxt1_rgba
  , eS3tc_dxt3_rgba
  , eS3tc_dxt5_rgba
  , };

/*! \class TextureLoader
 * \brief Loads texture files.
 */

class TextureLoader {
public:
  TextureLoader() = default;

  virtual ~TextureLoader() = default;

  flc::Texture2DFile *load(const std::string &filePath,
      eFlip flip = eFlip::eNone,
      GLenum format = GL_RGBA,
      std::string rootPath = "",
      eCompression compression = eCompression::eNone);

  flc::Texture2DFile *loadEmpty(GLint screenWidth, GLint screenHeight, GLenum format = GL_RGBA);

  flc::Texture2DFile *loadVirtualFileCheckboard(GLuint width,
      GLuint height,
      GLubyte red,
      GLubyte green,
      GLubyte blue,
      GLenum format = GL_RGBA);

  flc::Texture2DFile *
  loadVirtualFileColor(GLuint width, GLuint height, GLubyte red, GLubyte green, GLubyte blue, GLenum format = GL_RGBA);

private:
  GLint getBytesPerPixel(GLenum format);

  GLenum getComporession(eCompression compression);
};

} /* flw */
} /* flf */
