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
#include <fillwave/loaders/textureloader/stb/TextureLoaderTraitsSTB.h>

#include <fillwave/Texturing.h>

#include <fillwave/common/Strings.h>
#include <fillwave/common/Macros.h>

#include <fillwave/loaders/textureloader/TextureFactory.h>

#include <fillwave/Log.h>

#include <iterator>

#include <nv_helpers_gl/nv_dds.h>

FLOGINIT_DEFAULT()

using namespace std;

namespace flw {
namespace flf {

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSTB>::load(
  const std::string& filePath
  , GLenum format
  , const std::string& rootPath
  , GLenum cubeTarget) {

  if (filePath == rootPath) {
    fLogD("Empty texture ", filePath, " generation and loading ...");
    auto cfg = TextureFactory::loadVirtualFileColor(512, 512, 0, 0, 0);
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }

  const size_t posColor = filePath.find(".color");
  if (posColor != std::string::npos) {
    fLogD("Color texture ", filePath, " generation and loading ...");
    std::string sub = filePath.substr(rootPath.size(), posColor);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in ", filePath);
      return nullptr;
    }

    auto cfg = TextureFactory::loadVirtualFileColor(
      512
      , 512
      , atoi(tokens[0].c_str())
      , atoi(tokens[1].c_str())
      , atoi(tokens[2].c_str()));
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }

  const size_t posCheckboard = filePath.find(".checkboard");
  if (posCheckboard != std::string::npos) {
    fLogD("Checkboard texture ", filePath, " generation and loading ...");
    std::string sub = filePath.substr(rootPath.size(), posCheckboard);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in ", filePath);
      return nullptr;
    }

    auto cfg = TextureFactory::loadVirtualFileCheckboard(
      512
      , 512
      , atoi(tokens[0].c_str())
      , atoi(tokens[1].c_str())
      , atoi(tokens[2].c_str()));
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }
  if (filePath.find(".DDS") != std::string::npos || filePath.find(".dds") != std::string::npos) {
    fLogD("Comporessed texture ", filePath, " loading ...");
    nv_dds::CDDSImage image;
    image.load(filePath.c_str());
    if (!image.is_compressed()) {
      fLogF("Texture ", filePath, " is compressed with not supported format");
      return nullptr;
    }
    auto* cfg = new flc::TextureConfig();
    cfg->mContent.mCompression = GL_TRUE;
    cfg->mHeader.mInternalFormat = image.get_format();
    cfg->mContent.mCompressionSize = image.get_size();

    cfg->mHeader.mFormat = 0;
    cfg->mHeader.mWidth = image.get_width();
    cfg->mHeader.mHeight = image.get_height();
    cfg->mHeader.mType = 0;
    cfg->mHeader.mCubeTarget = cubeTarget;
    cfg->mHeader.mInternalFormat = image.get_format();

    cfg->mContent.mMipmapsLevel = image.get_num_mipmaps();
    cfg->mContent.mMipmaps = cfg->mContent.mMipmapsLevel != 0 ? GL_TRUE : GL_FALSE;
    cfg->mContent.mCompression = GL_TRUE;
    cfg->mContent.mBorder = 0;

    cfg->mData = make_pu_with_no_ownership<GLubyte>(image);
    cfg->mAllocation = flc::EMemoryAllocation::none;

    for (GLint i = 0; i < cfg->mContent.mMipmapsLevel; ++i) {
      nv_dds::CSurface mipmap = image.get_mipmap(i);
      cfg->mMipmaps.push_back({
        mipmap.get_size()
        , mipmap.get_height()
        , mipmap.get_width()
        , image.get_format()
        , mipmap
      });
    }

    return cfg;
  }

  GLint w = 0;
  GLint h = 0;
  GLint n = 0;
  stbi_set_flip_vertically_on_load(cubeTarget == 0);
  auto content = stbi_load(filePath.c_str(), &w, &h, &n, [format](){
    switch (format) {
      case GL_RGBA:
        return 4;
      case GL_RGB:
        return 3;
      case GL_ALPHA:
      case GL_RED:
      case GL_GREEN:
      case GL_BLUE:
        return 1;
      default:
        fLogE("Not recognized texture format loading");
        return 0;
    }
  } () );
  stbi_set_flip_vertically_on_load(0);
  // NULL, not nullptr because the stb library uses NULL
  if (NULL == content) {
    FILE *f;
    auto errorNo = fopen_s(&f, filePath.c_str(), "rb");
    if (errorNo) {
      fLogE("Texture ", filePath, " not found");
    } else {
      fLogE("Texture ", filePath, " found but not supported ");
      fclose(f);
    }
    return nullptr;
  }
  fLogD("Image ",filePath, " size ", w, "x", h, " pixel ", n, " bytes per pixel");
  auto cfg = new flc::TextureConfig();

  cfg->mHeader.mFormat = format;
  cfg->mHeader.mWidth = w;
  cfg->mHeader.mHeight = h;
  cfg->mHeader.mType = GL_UNSIGNED_BYTE;
  cfg->mHeader.mCubeTarget = cubeTarget;
  cfg->mHeader.mInternalFormat = format;

  cfg->mContent.mMipmaps = GL_TRUE;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mCompression = GL_FALSE;
  cfg->mContent.mBorder = 0;

  cfg->mData = make_pu_with_no_ownership<GLubyte>(content);

  cfg->mAllocation = flc::EMemoryAllocation::cstyle;

  return cfg;
}

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSTB>::load(
  GLint screenWidth
  , GLint screenHeight
  , GLenum format) {
  return TextureFactory::loadEmpty(screenWidth, screenHeight, format);
}

template <>
const vecStack<GLenum> TTextureLoader<TextureLoaderTraitsSTB>::getSupportedCompressionFormats() {
  return {
    GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
    , GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
    , GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
  };
}

template
class TTextureLoader<TextureLoaderTraitsSTB>;

} /* flf */
} /* flw */
