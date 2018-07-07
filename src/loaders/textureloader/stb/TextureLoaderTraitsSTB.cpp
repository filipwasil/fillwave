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

#include <fillwave/Log.h>

#include <iterator>

#include <nv_helpers_gl/nv_dds.h>

FLOGINIT_DEFAULT()

using namespace std;

namespace flw {
namespace flf {

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSTB>::load(
  const std::string &filePath
  , GLenum format
  , std::string rootPath
  // This loader detects the compression format automatically
  , flc::ECompression /*compression*/
  , GLenum cubeTarget) {

  fLogD("Texture ", filePath.c_str(), " loading ...");
  const size_t posCheckboard = filePath.find(".checkboard");
  const size_t posColor = filePath.find(".color");
  const size_t posDDS = filePath.find(".dds");
  uint8_t r = 0, g = 0, b = 0;

  auto textureGenerator = TextureLoaderTraitsSTB().mGenerator;

  if (filePath == rootPath) {
    fLogD("Empty texture ", filePath, " generation and loading ...");
    auto cfg = textureGenerator.loadVirtualFileColor(512, 512, 0, 0, 0);
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }

  if (posColor != std::string::npos) {
    fLogD("Color texture ", filePath, " generation and loading ...");
    std::string sub = filePath.substr(rootPath.size(), posColor);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in ", filePath);
      return nullptr;
    }

    r = atoi(tokens[0].c_str());
    g = atoi(tokens[1].c_str());
    b = atoi(tokens[2].c_str());

    auto cfg = textureGenerator.loadVirtualFileColor(512, 512, r, g, b);
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }
  if (posCheckboard != std::string::npos) {
    fLogD("Checkboard texture ", filePath, " generation and loading ...");
    std::string sub = filePath.substr(rootPath.size(), posCheckboard);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in ", filePath);
      return nullptr;
    }

    r = atoi(tokens[0].c_str());
    g = atoi(tokens[1].c_str());
    b = atoi(tokens[2].c_str());

    auto cfg = textureGenerator.loadVirtualFileCheckboard(512, 512, r, g, b);
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }
  if (posDDS != std::string::npos) {
    nv_dds::CDDSImage image;
    image.load(filePath.c_str());
    if (!image.is_compressed()) {
      fLogF("Texture ", filePath, " is compressed with not supported format");
      return nullptr;
    }
    auto cfg = new flc::TextureConfig();
    cfg->mContent.mCompression = GL_TRUE;
    cfg->mHeader.mInternalFormat = image.get_format();
    cfg->mContent.mCompressionSize = 0;

//    glCompressedTexImage2D(
//      GL_TEXTURE_2D
//      , 0
//      , image.get_format()
//      , image.get_width()
//      , image.get_height()
//      , 0
//      , image.get_size()
//      , image);

    const auto mipmapsCount = image.get_num_mipmaps();
    for (decltype(image.get_num_mipmaps()) i = 0; i < mipmapsCount; ++i) {
      nv_dds::CSurface mipmap = image.get_mipmap(i);
      cfg->mMipmaps.push_back({
                                   mipmap.get_size(),
                                   mipmap.get_height(),
                                   mipmap.get_width(),
                                   image.get_format(),
                                   mipmap
                                 }
      );
    }
  }

  GLint w, h, n;
  auto content = stbi_load(filePath.c_str(), &w, &h, &n, textureGenerator.getBytesPerPixel(format));
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

  cfg->mContent.mMipmaps = GL_TRUE;
  cfg->mContent.mMipmapsLevel = 0;

  cfg->mHeader.mCubeTarget = cubeTarget;

  cfg->mContent.mCompression = GL_FALSE;
  cfg->mHeader.mInternalFormat = format;

  cfg->mContent.mBorder = 0;

  cfg->mData = make_pu_with_no_ownership<GLubyte>(content);

  cfg->mAllocation = flc::EMemoryAllocation::cstyle;

  return cfg;
}

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsSTB>::load(GLint screenWidth, GLint screenHeight, GLenum /*format*/) {
  return TextureLoaderTraitsSTB().mGenerator.loadEmpty(screenWidth, screenHeight);
}

template <>
const std::vector<flc::ECompression> TTextureLoader<TextureLoaderTraitsSTB>::getSupportedCompressionFormats() {
  return { };
}

template
class TTextureLoader<TextureLoaderTraitsSTB>;

} /* flf */
} /* flw */
