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

#include <fillwave/loaders/TTextureLoader.h>

#include <fillwave/Texturing.h>

#include <fillwave/common/Strings.h>
#include <fillwave/common/Macros.h>

#include <iterator>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

using namespace std;

namespace flw {
namespace flf {

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsGLI>::load(
  const std::string& filePath
  , flc::EFlip flip
  , GLenum format
  , std::string rootPath
  , ECompression compression
  , GLenum cubeTarget) {

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
}

template <>
flc::TextureConfig* TTextureLoader<TextureLoaderTraitsGLI>::load(
  GLint screenWidth
  , GLint screenHeight
  , GLenum format) {
  return nullptr;
}

template <>
const std::vector<flc::ECompression> TTextureLoader<TextureLoaderTraitsGLI>::getSupportedCompressionFormats() {
  return { };
}

} /* flf */
} /* flw */
