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

TextureLoader::TextureLoader() = default;

flc::TextureConfig* TextureLoader::load(const std::string &filePath,
    EFlip flip,
    GLenum format,
    std::string rootPath,
    ECompression compression,
    GLenum cubeTarget) {

  fLogD("Texture ", filePath.c_str(), " loading ...");
  const size_t posCheckboard = filePath.find(".checkboard");
  const size_t posColor = filePath.find(".color");
  const size_t posDDS = filePath.find(".dds");
  uint8_t r = 0, g = 0, b = 0;
  if (filePath == rootPath) {
    fLogD("Empty texture ", filePath, " generation and loading ...");
    auto cfg = loadVirtualFileColor(512, 512, 0, 0, 0);
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

    auto cfg = loadVirtualFileColor(512, 512, r, g, b);
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

    auto cfg = loadVirtualFileCheckboard(512, 512, r, g, b);
    cfg->mHeader.mCubeTarget = cubeTarget;
    return cfg;
  }
  if (posDDS != std::string::npos) {
    fLogE("Compressed Texture ", filePath, " not supported yet");
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

  if (compression == ECompression::none) {
    cfg->mContent.mCompression = GL_FALSE;
    cfg->mHeader.mInternalFormat = format;
  } else {
    cfg->mContent.mCompression = GL_TRUE;
    cfg->mHeader.mInternalFormat = getCompression(compression);
    cfg->mContent.mCompressionSize = 0;
    fLogF("Texture compression feature not ready");
  }

  cfg->mContent.mBorder = 0;

  cfg->mData = content;

  cfg->mAllocation = flc::EMemoryAllocation::cstyle;

  fLogD("Flipping Texture", filePath, " ...");
  switch (flip) {
    case EFlip::vertical:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h / 2; ++row) {
        for (int column = 0; column < w; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = (h - row - 1) * w * n + column * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
            cfg->mData[exchangeIndex2] ^= cfg->mData[exchangeIndex1];
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::horizontalVertical:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w / 2; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = row * w * n + (w - column - 1) * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
            cfg->mData[exchangeIndex2] ^= cfg->mData[exchangeIndex1];
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::horizontal:
#pragma omp parallel for schedule(guided) num_threads(2)
      for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w / 2; ++column) {
          const int pixelOffset1 = row * w * n + column * n;
          const int pixelOffset2 = row * w * n + (w - column - 1) * n;
          for (int byteInPixel = 0; byteInPixel < n; ++byteInPixel) {
            const int exchangeIndex1 = pixelOffset1 + byteInPixel;
            const int exchangeIndex2 = pixelOffset2 + byteInPixel;
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
            cfg->mData[exchangeIndex2] ^= cfg->mData[exchangeIndex1];
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
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
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
            cfg->mData[exchangeIndex2] ^= cfg->mData[exchangeIndex1];
            cfg->mData[exchangeIndex1] ^= cfg->mData[exchangeIndex2];
          }
        }
      }
      break;

    case EFlip::none:
      break;
  }
  return cfg;
#endif /* FILLWAVE_TEXTURE_LOADER_GLI */
}

flc::TextureConfig* TextureLoader::loadEmpty(GLint screenWidth, GLint screenHeight, GLenum format) {
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

flc::TextureConfig* TextureLoader::loadVirtualFileCheckboard(GLuint width,
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

flc::TextureConfig *TextureLoader::loadVirtualFileColor(GLuint width,
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
    case ECompression::none:
      return GL_NONE;
    case ECompression::generic_r:
      return GL_COMPRESSED_RED;
    case ECompression::generic_rg:
      return GL_COMPRESSED_RG;
    case ECompression::generic_rgb:
      return GL_COMPRESSED_RGB;
    case ECompression::generic_rgba:
      return GL_COMPRESSED_RGBA;
    case ECompression::generic_srgb:
      return GL_COMPRESSED_SRGB;
    case ECompression::generic_srgba:
      return GL_COMPRESSED_SRGB_ALPHA;
#if defined(__APPLE__)
#else
    case ECompression::latc_luminance:
      return GL_COMPRESSED_LUMINANCE_LATC1_EXT;
    case ECompression::latc_luminance_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT;
    case ECompression::latc_luminance_alpha:
      return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
    case ECompression::latc_luminance_alpha_signed:
      return GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT;
    case ECompression::rgtc1_r:
      return GL_COMPRESSED_RED_RGTC1_EXT;
    case ECompression::rgtc1_r_signed:
      return GL_COMPRESSED_SIGNED_RED_RGTC1_EXT;
    case ECompression::rgtc1_rg:
      return GL_COMPRESSED_RED_GREEN_RGTC2_EXT;
    case ECompression::rgtc1_rg_signed:
      return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT;
    case ECompression::s3tc_dxt1_rgb:
      return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    case ECompression::s3tc_dxt1_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case ECompression::s3tc_dxt3_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case ECompression::s3tc_dxt5_rgba:
      return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
#endif /* __APPLE__ */
  }
#endif /* FILLWAVE_GLES_3_0 */
  return GL_NONE;
}

} /* flf */
} /* flw */
