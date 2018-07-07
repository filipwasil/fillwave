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

#include <fillwave/loaders/textureloader/TTextureLoader.h>
#include <fillwave/loaders/textureloader/squish/TextureLoaderTraitsSquish.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

//int GetStorageRequirements( int width, int height, int flags );
//void CompressImage( squish::u8 const* rgba, int width, int height, int pitch, void* blocks, int flags, float* metric = 0 );
//void CompressImage( squish::u8 const* rgba, int width, int height, void* blocks, int flags, float* metric = 0 );
//void DecompressImage( squish::u8* rgba, int width, int height, int pitch, void const* blocks, int flags );
//void DecompressImage( squish::u8* rgba, int width, int height, void const* blocks, int flags );


template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSquish>::load(
  const std::string& filePath
  , flc::EFlip /*flip*/
  , GLenum /*format*/
  , std::string /*rootPath*/
  , flc::ECompression compression
  , GLenum /*cubeTarget*/) {
  switch (compression) {
    case flc::ECompression::s3tc_dxt1_rgb:
      // kDxt1
      break;
    case flc::ECompression::s3tc_dxt1_rgba:
      // kDxt1
      break;
    case flc::ECompression::s3tc_dxt3_rgba:
      // kDxt3
      break;
    case flc::ECompression::s3tc_dxt5_rgba:
      // kDxt5
      break;
    default:
      // kColourClusterFit = ( 1 << 5 ) //! Use a slow but high quality colour compressor (the default).
      // kColourRangeFit = ( 1 << 6 ) //! Use a fast but low quality colour compressor.
      // kWeightColourByAlpha = ( 1 << 7 ) //! Weight the colour by alpha during cluster fit (disabled by default).
      // kColourIterativeClusterFit = ( 1 << 8 ) //! Use a very slow but very high quality colour compressor.
      // kSourceBGRA = ( 1 << 9 ) //! Source is BGRA rather than RGBA
      break;

  }
  fLogE("Compressed Texture ", filePath, " not supported by this loader");
  return nullptr;
}

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSquish>::load(
  GLint /*screenWidth*/
  , GLint /*screenHeight*/
  , GLenum /*format*/) {
  fLogE("Texture not supported by this loader");
  return nullptr;
}

template <>
const std::vector<flc::ECompression> TTextureLoader<TextureLoaderTraitsSquish>::getSupportedCompressionFormats() {
  return {
    flc::ECompression::s3tc_dxt1_rgba
    , flc::ECompression::s3tc_dxt3_rgba
    , flc::ECompression::s3tc_dxt5_rgba
    , flc::ECompression::s3tc_dxt1_rgb};
}

} /* flf */
} /* flw */
