/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
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

#include <fillwave/loaders/textureloader/TextureGenerator.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

flc::TextureConfig* TextureGenerator::loadEmpty(GLint screenWidth, GLint screenHeight, GLenum format) {
  auto cfg = new flc::TextureConfig();

  cfg->mHeader.mFormat = format;
  cfg->mHeader.mInternalFormat = format;
  cfg->mHeader.mWidth = screenWidth;
  cfg->mHeader.mHeight = screenHeight;
  cfg->mHeader.mType = GL_UNSIGNED_BYTE;

  cfg->mContent.mMipmaps = GL_TRUE;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mCompression = GL_FALSE;
  cfg->mContent.mBorder = 0;

  cfg->mData = nullptr;

  cfg->mAllocation = flc::EMemoryAllocation::none;

  return cfg;
}

flc::TextureConfig* TextureGenerator::loadVirtualFileCheckboard(
  GLuint width
  , GLuint height
  , GLubyte red
  , GLubyte green
  , GLubyte blue
  , GLenum format) {

  const GLint bytesPerPixel = getBytesPerPixel(format);
  const GLint size = bytesPerPixel * width * height * sizeof(GLubyte);
  auto content = new GLubyte[size];

  GLint i, r = 0, g = 0, b = 0;
  for (i = 0; i < size; i += bytesPerPixel) {
    if (i % ((width * bytesPerPixel) * 8) == 0) {
      r ^= red;
      g ^= green;
      b ^= blue;
    }
    if (i % (bytesPerPixel * 8) == 0) {
      r ^= red;
      g ^= green;
      b ^= blue;
    }
    content[i] = r;
    content[i + 1] = g;
    content[i + 2] = b;
    content[i + 3] = 1;
  }

  auto cfg = new flc::TextureConfig();
  cfg->mHeader.mFormat = format;
  cfg->mHeader.mInternalFormat = format;
  cfg->mHeader.mWidth = width;
  cfg->mHeader.mHeight = height;
  cfg->mHeader.mType = GL_UNSIGNED_BYTE;

  cfg->mContent.mMipmaps = GL_TRUE;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mCompression = GL_FALSE;
  cfg->mContent.mBorder = 0;

  cfg->mData = content;

  cfg->mAllocation = flc::EMemoryAllocation::standard;

  return cfg;
}

flc::TextureConfig* TextureGenerator::loadVirtualFileColor(
  GLuint width
  , GLuint height
  , GLubyte red
  , GLubyte green
  , GLubyte blue
  , GLenum format) {
  const GLint bytesPerPixel = getBytesPerPixel(format);
  const int size = bytesPerPixel * width * height * sizeof(GLubyte);
  GLubyte *content = new GLubyte[size];

  for (int i = 0; i < size; i += bytesPerPixel) {
    content[i] = red;
    content[i + 1] = green;
    content[i + 2] = blue;
    content[i + 3] = 1;
  }

  auto cfg = new flc::TextureConfig();
  cfg->mHeader.mFormat = format;
  cfg->mHeader.mInternalFormat = format;
  cfg->mHeader.mWidth = width;
  cfg->mHeader.mHeight = height;
  cfg->mHeader.mType = GL_UNSIGNED_BYTE;

  cfg->mContent.mMipmaps = GL_FALSE;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mCompression = GL_FALSE;
  cfg->mContent.mBorder = 0;

  cfg->mData = content;

  cfg->mAllocation = flc::EMemoryAllocation::standard;

  return cfg;
}

GLint TextureGenerator::getBytesPerPixel(GLenum format) {
  GLint bytes;
  switch (format) {
    case GL_RGBA:
      bytes = 4;
      break;
    case GL_RGB:
      bytes = 3;
      break;
    case GL_ALPHA:
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
      bytes = 1;
      break;
    default:
      fLogE("Not recognized texture format loading");
      bytes = 0;
      break;
  }
  return bytes;
}

GLenum TextureGenerator::getCompression(flc::ECompression compression) {
#ifdef FILLWAVE_GLES_3_0
  (void)compression;
#else
  switch (compression) {
    case flc::ECompression::none:
      return GL_NONE;
    case flc::ECompression::generic_r:
      return GL_COMPRESSED_RED;
    case flc::ECompression::generic_rg:
      return GL_COMPRESSED_RG;
    case flc::ECompression::generic_rgb:
      return GL_COMPRESSED_RGB;
    case flc::ECompression::generic_rgba:
      return GL_COMPRESSED_RGBA;
    case flc::ECompression::generic_srgb:
      return GL_COMPRESSED_SRGB;
    case flc::ECompression::generic_srgba:
      return GL_COMPRESSED_SRGB_ALPHA;
#if defined(__APPLE__)
#else
    case flc::ECompression::latc_luminance:
      return GL_COMPRESSED_LUMINANCE_LATC1_EXT;
    case flc::ECompression::latc_luminance_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT;
    case flc::ECompression::latc_luminance_alpha:
      return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
    case flc::ECompression::latc_luminance_alpha_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT;
    case flc::ECompression::rgtc1_r:
      return GL_COMPRESSED_RED_RGTC1_EXT;
    case flc::ECompression::rgtc1_r_signed:
      return GL_COMPRESSED_SIGNED_RED_RGTC1_EXT;
    case flc::ECompression::rgtc1_rg:
      return GL_COMPRESSED_RED_GREEN_RGTC2_EXT;
    case flc::ECompression::rgtc1_rg_signed:
      return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT;
    case flc::ECompression::s3tc_dxt1_rgb:
      return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    case flc::ECompression::s3tc_dxt1_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case flc::ECompression::s3tc_dxt3_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case flc::ECompression::s3tc_dxt5_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
#endif /* __APPLE__ */
  }
#endif /* FILLWAVE_GLES_3_0 */
  return GL_NONE;
}

} /* flf */
} /* flw */
