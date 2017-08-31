/*
 * TextureLoader.cpp
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
 *
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

#include <fillwave/loaders/TextureLoader.h>
#include <fillwave/Texturing.h>
#include <fillwave/common/Strings.h>
#include <fillwave/common/Macros.h>
#include <iterator>

#include <fillwave/Log.h>

FLOGINIT("TextureLoader", FERROR | FFATAL | FDEBUG)

using namespace std;

namespace flw {
namespace flf {

flc::Texture2DFile *TextureLoader::load(const std::string &filePath,
    EFlip flip,
    GLenum format,
    std::string rootPath,
    ECompression compression) {

  fLogD("Texture %s loading ...", filePath.c_str());
  const size_t posCheckboard = filePath.find(".checkboard");
  const size_t posColor = filePath.find(".color");
  const size_t posDDS = filePath.find(".dds");
  uint8_t r = 0, g = 0, b = 0;
  if (filePath == rootPath) {
    fLogD("Empty texture %s generation and loading ...", filePath.c_str());
    auto file = loadVirtualFileColor(512, 512, 0, 0, 0);
    return file;
  }


  if (posColor != std::string::npos) {
    fLogD("Color texture %s generation and loading ...", filePath.c_str());
    std::string sub = filePath.substr(rootPath.size(), posColor);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in %s", filePath.c_str());
      return nullptr;
    }

    r = atoi(tokens[0].c_str());
    g = atoi(tokens[1].c_str());
    b = atoi(tokens[2].c_str());

    auto file = loadVirtualFileColor(512, 512, r, g, b);
    return file;
  }
  if (posCheckboard != std::string::npos) {
    fLogD("Checkboard texture %s generation and loading ...", filePath.c_str());
    std::string sub = filePath.substr(rootPath.size(), posCheckboard);
    std::vector<std::string> tokens = split(sub, '_');
    if (tokens.size() < 3) {
      fLogE("Could not found color parameters in %s", filePath.c_str());
      return nullptr;
    }

    r = atoi(tokens[0].c_str());
    g = atoi(tokens[1].c_str());
    b = atoi(tokens[2].c_str());

    auto file = loadVirtualFileCheckboard(512, 512, r, g, b);
    return file;
  }
  if (posDDS != std::string::npos) {
    fLogE("Compressed Texture %s not supported yet", filePath.c_str());
    return nullptr;
  }
#ifdef FILLWAVE_TEXTURE_LOADER_GLI
  (void)flip;
  (void)format;
  (void)compression;
  gli::texture Texture = gli::load(filePath);
  if(Texture.empty()) {
    return nullptr;
  }
#ifdef FILLWAVE_GLES_3_0
  gli::gl GL(gli::gl::PROFILE_ES30);
#else /* FILLWAVE_GLES_3_0 */
  gli::gl GL(gli::gl::PROFILE_GL33);
#endif /* FILLWAVE_GLES_3_0 */
  gli::gl::format const Format = GL.translate(Texture.format(),
                       Texture.swizzles());
  GLenum Target = GL.translate(Texture.target());

  GLuint TextureName = 0;
  glGenTextures(1, &TextureName);
  glBindTexture(Target, TextureName);
  glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL,
             static_cast<GLint>(Texture.levels() - 1));
  glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
  glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
  glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
  glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

  glm::tvec3<GLsizei> const Extent(Texture.extent());
  GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() *
                    Texture.faces());

  switch(Texture.target()) {
    case gli::TARGET_1D:
      glTexStorage1D(
        Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x);
      break;
    case gli::TARGET_1D_ARRAY:
    case gli::TARGET_2D:
    case gli::TARGET_CUBE:
      glTexStorage2D(
        Target, static_cast<GLint>(Texture.levels()), Format.Internal,
        Extent.x, Texture.target() == gli::TARGET_2D ? Extent.y : FaceTotal);
      break;
    case gli::TARGET_2D_ARRAY:
    case gli::TARGET_3D:
    case gli::TARGET_CUBE_ARRAY:
      glTexStorage3D(
        Target, static_cast<GLint>(Texture.levels()), Format.Internal,
        Extent.x, Extent.y,
        Texture.target() == gli::TARGET_3D ? Extent.z : FaceTotal);
      break;
    default:
      assert(0);
      break;
  }

  for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
    for(std::size_t Face = 0; Face < Texture.faces(); ++Face)
      for(std::size_t Level = 0; Level < Texture.levels(); ++Level) {
        GLsizei const LayerGL = static_cast<GLsizei>(Layer);
        glm::tvec3<GLsizei> Extent(Texture.extent(Level));
        Target = gli::is_target_cube(Texture.target())
              ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face)
              : Target;

        switch(Texture.target()) {
          case gli::TARGET_1D:
            if(gli::is_compressed(Texture.format()))
              glCompressedTexSubImage1D(
                Target, static_cast<GLint>(Level), 0, Extent.x,
                Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                Texture.data(Layer, Face, Level));
            else
              glTexSubImage1D(
                Target, static_cast<GLint>(Level), 0, Extent.x,
                Format.External, Format.Type,
                Texture.data(Layer, Face, Level));
            break;
          case gli::TARGET_1D_ARRAY:
          case gli::TARGET_2D:
          case gli::TARGET_CUBE:
            if(gli::is_compressed(Texture.format()))
              glCompressedTexSubImage2D(
                Target, static_cast<GLint>(Level),
                0, 0,
                Extent.x,
                Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
                Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                Texture.data(Layer, Face, Level));
            else
              glTexSubImage2D(
                Target, static_cast<GLint>(Level),
                0, 0,
                Extent.x,
                Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Extent.y,
                Format.External, Format.Type,
                Texture.data(Layer, Face, Level));
            break;
          case gli::TARGET_2D_ARRAY:
          case gli::TARGET_3D:
          case gli::TARGET_CUBE_ARRAY:
            if(gli::is_compressed(Texture.format()))
              glCompressedTexSubImage3D(
                Target, static_cast<GLint>(Level),
                0, 0, 0,
                Extent.x, Extent.y,
                Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
                Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
                Texture.data(Layer, Face, Level));
            else
              glTexSubImage3D(
                Target, static_cast<GLint>(Level),
                0, 0, 0,
                Extent.x, Extent.y,
                Texture.target() == gli::TARGET_3D ? Extent.z : LayerGL,
                Format.External, Format.Type,
                Texture.data(Layer, Face, Level));
            break;
          default:
            assert(0);
            break;
        }
      }
  return TextureName;
#else /* FILLWAVE_TEXTURE_LOADER_GLI */
  GLint w, h, n;
  auto content = stbi_load(filePath.c_str(), &w, &h, &n, getBytesPerPixel(format));
  if (NULL == content) { //xxx NULL, not nullptr because the stb library uses NULL
    FILE *f;
    auto errorNo = fopen_s(&f, filePath.c_str(), "rb");
    if (errorNo) {
      fLogE("Texture %s not found", filePath.c_str());
    } else {
      fLogE("Texture %s found but not supported ", filePath.c_str());
      fclose(f);
    }
    return nullptr;
  }
  fLogD("Image %s size %dx%d pixel %d bytes per pixel", filePath.c_str(), w, h, n);
  auto file = new flc::Texture2DFile();

  file->mHeader.mFormat = format;
  file->mHeader.mWidth = w;
  file->mHeader.mHeight = h;
  file->mHeader.mType = GL_UNSIGNED_BYTE;

  file->mConfig.mMipmaps = GL_TRUE;
  file->mConfig.mMipmapsLevel = 0;

  if (compression == ECompression::eNone) {
    file->mConfig.mCompression = GL_FALSE;
    file->mHeader.mInternalFormat = format;
  } else {
    file->mConfig.mCompression = GL_TRUE;
    file->mHeader.mInternalFormat = getCompression(compression);
    file->mConfig.mCompressionSize = 0;
    fLogF("Texture compression feature not ready");
  }

  file->mConfig.mBorder = 0;

  file->mData = content;

  file->mAllocation = flc::EMemoryAllocation::eMallock;

  fLogD("Flipping Texture %s ...", filePath.c_str());
  switch (flip) {
    case EFlip::eVertical:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h / 2; ++row) {
        for (int column = 0; column < w; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = (h - row - 1) * w * n + column * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
            file->mData[exchangeIndex2] ^= file->mData[exchangeIndex1];
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::eHorizontal_vertical:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w / 2; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = row * w * n + (w - column - 1) * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
            file->mData[exchangeIndex2] ^= file->mData[exchangeIndex1];
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::eHorizontal:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w / 2; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = row * w * n + (w - column - 1) * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
            file->mData[exchangeIndex2] ^= file->mData[exchangeIndex1];
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
          }
        }
      }
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h / 2; ++row) {
        for (int column = 0; column < w; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = (h - row - 1) * w * n + column * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
            file->mData[exchangeIndex2] ^= file->mData[exchangeIndex1];
            file->mData[exchangeIndex1] ^= file->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::eNone:
      break;
  }
  return file;
#endif /* FILLWAVE_TEXTURE_LOADER_GLI */
}

flc::Texture2DFile *TextureLoader::loadEmpty(GLint screenWidth, GLint screenHeight, GLenum format) {
  auto file = new flc::Texture2DFile();

  file->mHeader.mFormat = format;
  file->mHeader.mInternalFormat = format;
  file->mHeader.mWidth = screenWidth;
  file->mHeader.mHeight = screenHeight;
  file->mHeader.mType = GL_UNSIGNED_BYTE;

  file->mConfig.mMipmaps = GL_TRUE;
  file->mConfig.mMipmapsLevel = 0;
  file->mConfig.mCompression = GL_FALSE;
  file->mConfig.mBorder = 0;

  file->mData = nullptr;

  file->mAllocation = flc::EMemoryAllocation::eNone;

  return file;
}

flc::Texture2DFile *TextureLoader::loadVirtualFileCheckboard(GLuint width,
    GLuint height,
    GLubyte red,
    GLubyte green,
    GLubyte blue,
    GLenum format) {

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

  auto file = new flc::Texture2DFile();
  file->mHeader.mFormat = format;
  file->mHeader.mInternalFormat = format;
  file->mHeader.mWidth = width;
  file->mHeader.mHeight = height;
  file->mHeader.mType = GL_UNSIGNED_BYTE;

  file->mConfig.mMipmaps = GL_TRUE;
  file->mConfig.mMipmapsLevel = 0;
  file->mConfig.mCompression = GL_FALSE;
  file->mConfig.mBorder = 0;

  file->mData = content;

  file->mAllocation = flc::EMemoryAllocation::eNew;

  return file;
}

flc::Texture2DFile *TextureLoader::loadVirtualFileColor(GLuint width,
    GLuint height,
    GLubyte red,
    GLubyte green,
    GLubyte blue,
    GLenum format) {
  const GLint bytesPerPixel = getBytesPerPixel(format);
  const int size = bytesPerPixel * width * height * sizeof(GLubyte);
  GLubyte *content = new GLubyte[size];

  for (int i = 0; i < size; i += bytesPerPixel) {
    content[i] = red;
    content[i + 1] = green;
    content[i + 2] = blue;
    content[i + 3] = 1;
  }

  auto file = new flc::Texture2DFile();
  file->mHeader.mFormat = format;
  file->mHeader.mInternalFormat = format;
  file->mHeader.mWidth = width;
  file->mHeader.mHeight = height;
  file->mHeader.mType = GL_UNSIGNED_BYTE;

  file->mConfig.mMipmaps = GL_FALSE;
  file->mConfig.mMipmapsLevel = 0;
  file->mConfig.mCompression = GL_FALSE;
  file->mConfig.mBorder = 0;

  file->mData = content;

  file->mAllocation = flc::EMemoryAllocation::eNew;

  return file;
}

inline GLint TextureLoader::getBytesPerPixel(GLenum format) {
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

inline GLenum TextureLoader::getCompression(ECompression compression) {
#ifdef FILLWAVE_GLES_3_0
  (void)compression;
#else
  switch (compression) {
    case ECompression::eNone:
      return GL_NONE;
    case ECompression::eGeneric_r:
      return GL_COMPRESSED_RED;
    case ECompression::eGeneric_rg:
      return GL_COMPRESSED_RG;
    case ECompression::eGeneric_rgb:
      return GL_COMPRESSED_RGB;
    case ECompression::eGeneric_rgba:
      return GL_COMPRESSED_RGBA;
    case ECompression::eGeneric_srgb:
      return GL_COMPRESSED_SRGB;
    case ECompression::eGeneric_srgba:
      return GL_COMPRESSED_SRGB_ALPHA;
#if defined(__APPLE__)
#else
    case ECompression::eLatc_luminance:
      return GL_COMPRESSED_LUMINANCE_LATC1_EXT;
    case ECompression::eLatc_luminance_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT;
    case ECompression::eLatc_luminance_alpha:
      return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
    case ECompression::eLatc_luminance_alpha_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT;
    case ECompression::eRgtc1_r:
      return GL_COMPRESSED_RED_RGTC1_EXT;
    case ECompression::eRgtc1_r_signed:
      return GL_COMPRESSED_SIGNED_RED_RGTC1_EXT;
    case ECompression::eRgtc1_rg:
      return GL_COMPRESSED_RED_GREEN_RGTC2_EXT;
    case ECompression::eRgtc1_rg_signed:
      return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT;
    case ECompression::eS3tc_dxt1_rgb:
      return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    case ECompression::eS3tc_dxt1_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case ECompression::eS3tc_dxt3_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case ECompression::eS3tc_dxt5_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
#endif /* __APPLE__ */
    default:
      break;
  }
#endif /* FILLWAVE_GLES_3_0 */
  return GL_NONE;
}

} /* flf */
} /* flw */
