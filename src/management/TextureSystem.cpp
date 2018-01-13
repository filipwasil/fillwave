/*
 * Copyright (c) 2018, Fillwave developers
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

#include <fillwave/Log.h>
#include <fillwave/management/TextureSystem.h>

FLOGINIT_MASK(FERROR | FFATAL | FINFO | FDEBUG)

namespace flw {
namespace flf {

TextureSystem::TextureSystem(const std::string &rootPath)
    : mRootPath(rootPath) {
  checkExtensions();
}

inline void TextureSystem::checkExtensions() {
#ifdef FILLWAVE_GLES_3_0
#else
  int NumberOfExtensions;
  glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

  for (int i = 0; i < NumberOfExtensions; i++) {
    const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
    auto find_extension = [ccc](const char *name) -> bool {
      if (0 == (strcmp((const char *) ccc, name))) {
        fLogI(name, " compression supported");
        return true;
      } else {
        return false;
      }
    };

#if defined(__APPLE__) || defined (__ANDROID__)
#else
    if (find_extension("GL_EXT_texture_compression_latc")) {
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_LUMINANCE_LATC1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT);
    } else if (find_extension("GL_EXT_texture_compression_rgtc")) {
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RED_RGTC1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_SIGNED_RED_RGTC1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RED_GREEN_RGTC2_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT);
    } else if (find_extension("GL_EXT_texture_compression_s3tc")) {
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RGB_S3TC_DXT1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
      mSupportedCompresssionTypes.push_back(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
    }
#endif
  }

#endif
}

flc::Texture2D* TextureSystem::get(const std::string &texturePath, ECompression compression, EFlip flip) {
  const std::string filePath = mRootPath + texturePath;
  if (texturePath.empty()) {
    return nullptr;
  }

  if (mTextures2D.find(filePath) != mTextures2D.end()) {
    return mTextures2D[filePath].get();
  }

  if (flc::Texture2DFile* file = mLoader.load(filePath, flip, GL_RGBA, mRootPath, compression)) {
    fLogD("Texture ", filePath, " added to manager");
    flc::ParameterList parameters;
    return mTextures2D.store(filePath, file, parameters, 1);
  }

  fLogD("Texture ", filePath, " not found");
  return nullptr;
}

flc::Texture2DRenderableDynamic *
TextureSystem::getDynamic(const std::string &fragmentShaderPath, flc::Program *program, glm::ivec2 screenSize) {
  std::string filePath = mRootPath + fragmentShaderPath;

  auto file = mLoader.loadEmpty(screenSize.x, screenSize.y);

  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  return mTextures2DDynamic.store(fragmentShaderPath, file, parameters, program);
}

flc::Texture3D *TextureSystem::get(const std::string &posX,
    const std::string &negX,
    const std::string &posY,
    const std::string &negY,
    const std::string &posZ,
    const std::string &negZ) {

  std::string filePathPosX = mRootPath + posX;
  std::string filePathNegX = mRootPath + negX;
  std::string filePathPosY = mRootPath + posY;
  std::string filePathNegY = mRootPath + negY;
  std::string filePathPosZ = mRootPath + posZ;
  std::string filePathNegZ = mRootPath + negZ;

  const std::string name = filePathPosX + filePathNegX + filePathPosY + filePathNegY + filePathPosZ + filePathNegZ;

  fLogD("Texture to be added: ", name);

  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  fLogD("Texture ", name, " will be added to manager");

  auto filePosX = mLoader.load(filePathPosX, EFlip::eNone, GL_RGBA, mRootPath);
  auto fileNegX = mLoader.load(filePathNegX, EFlip::eNone, GL_RGBA, mRootPath);
  auto filePosY = mLoader.load(filePathPosY, EFlip::eNone, GL_RGBA, mRootPath);
  auto fileNegY = mLoader.load(filePathNegY, EFlip::eNone, GL_RGBA, mRootPath);
  auto filePosZ = mLoader.load(filePathPosZ, EFlip::eNone, GL_RGBA, mRootPath);
  auto fileNegZ = mLoader.load(filePathNegZ, EFlip::eNone, GL_RGBA, mRootPath);

  if (filePosX && fileNegX && filePosY && fileNegY && filePosZ && fileNegZ) {
    fLogD("Texture ", name, " has been added to manager");

    auto t = mTextures3D.store(name, filePosX, fileNegX, filePosY, fileNegY, filePosZ, fileNegZ, parameters);

    return t;
  }
  if (!filePosX) {
    fLogD("3D Texture positive x ", posX, " not found");
  } else {
    delete filePosX;
  }
  if (!fileNegX) {
    fLogD("3D Texture negative x ", negX, " not found");
  } else {
    delete fileNegX;
  }
  if (!filePosY) {
    fLogD("3D Texture positive y ", posY, " not found");
  } else {
    delete filePosY;
  }
  if (!fileNegY) {
    fLogD("3D Texture negative y ", negY, " not found");
  } else {
    delete fileNegY;
  }
  if (!filePosZ) {
    fLogD("3D Texture positive z ", posZ, " not found");
  } else {
    delete filePosZ;
  }
  if (!fileNegZ) {
    fLogD("3D Texture negative z ", negZ, " not found");
  } else {
    delete fileNegZ;
  }
  fLogE("Texture 3D ", name, " not added to manager");
  return nullptr;
}

flc::Texture2DRenderable *TextureSystem::getShadow2D(GLuint width, GLuint height) {
  auto file = new flc::Texture2DFile();

  file->mHeader.mFormat = GL_DEPTH_COMPONENT;
  file->mHeader.mInternalFormat = GL_DEPTH_COMPONENT;
  file->mConfig.mMipmapsLevel = 0;
  file->mConfig.mBorder = 0;
  file->mHeader.mWidth = width;
  file->mHeader.mHeight = height;
  file->mData = nullptr;
  file->mConfig.mMipmaps = GL_FALSE;
  file->mConfig.mCompression = GL_FALSE;

#ifdef FILLWAVE_GLES_3_0
  file->mHeader.mType = GL_UNSIGNED_INT;
  flc::ParameterList parameters = {
      flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
      , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
      , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
      , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
      , flc::Parameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE)
      , flc::Parameter(GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL)
  };
#else
  file->mHeader.mType = GL_FLOAT;
  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
  };
#endif

  return mTextures2DRenderable.store(mTextures2DRenderable.size(), GL_DEPTH_ATTACHMENT, file, parameters);
}

flc::Texture3DRenderable* TextureSystem::getShadow3D(GLuint /*width*/, GLuint /*height*/) {

  flc::Texture2DFile* file[6];
  for (GLint i = 0; i < 6; ++i) {
    file[i] = new flc::Texture2DFile();
    file[i]->mHeader.mFormat = GL_RED;
    file[i]->mHeader.mInternalFormat = GL_R32F;
    file[i]->mConfig.mMipmapsLevel = 0;
    file[i]->mConfig.mBorder = 0;
    file[i]->mHeader.mWidth = 512;
    file[i]->mHeader.mHeight = 512;
    file[i]->mHeader.mType = GL_FLOAT;
    file[i]->mData = nullptr;
    file[i]->mConfig.mMipmaps = GL_FALSE;
    file[i]->mConfig.mCompression = GL_FALSE;
  }

  auto file2D = new flc::Texture2DFile();
  file2D->mHeader.mFormat = GL_DEPTH_COMPONENT;
  file2D->mHeader.mInternalFormat = GL_DEPTH_COMPONENT32;
  file2D->mConfig.mMipmapsLevel = 0;
  file2D->mConfig.mBorder = 0;
  file2D->mHeader.mWidth = 512;
  file2D->mHeader.mHeight = 512;
  file2D->mHeader.mType = GL_FLOAT;
  file2D->mData = nullptr;
  file2D->mConfig.mMipmaps = GL_FALSE;
  file2D->mConfig.mCompression = GL_FALSE;

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
  };

  flc::ParameterList parameters3D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE)
  };

  auto t = mTextures2DRenderable.store(mTextures2DRenderable.size(), GL_DEPTH_ATTACHMENT, file2D, parameters2D);
  return mTextures3DRenderable.store(mTextures3DRenderable.size(), file[0], file[1], file[2], file[3], file[4], file[5], t, parameters3D);
}

flc::Texture2DRenderable *TextureSystem::getColor2D(GLuint width, GLuint height) {

  flc::Texture2DFile* file = new flc::Texture2DFile();
  file->mHeader.mFormat = GL_RGBA;
  file->mHeader.mInternalFormat = GL_RGBA;
  file->mConfig.mMipmapsLevel = 0;
  file->mConfig.mBorder = 0;
  file->mHeader.mWidth = width;
  file->mHeader.mHeight = height;
#ifdef FILLWAVE_GLES_3_0
  file->mHeader.mType = GL_UNSIGNED_BYTE;
#else
  file->mHeader.mType = GL_FLOAT;
#endif
  file->mData = nullptr;
  file->mConfig.mMipmaps = GL_FALSE;
  file->mConfig.mCompression = GL_FALSE;

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  return mTextures2DRenderable.store(mTextures2DRenderable.size(), GL_COLOR_ATTACHMENT0, file, parameters2D);
}

flc::Texture2D *TextureSystem::getDeferredColor(GLuint width, GLuint height, GLuint size) {

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
  };

  flc::Texture2DFileHeader colorTextureHeader;
#ifdef FILLWAVE_GLES_3_0
  colorTextureHeader.mFormat = GL_RGBA;
  colorTextureHeader.mInternalFormat = GL_RGBA;
  colorTextureHeader.mType = GL_UNSIGNED_BYTE;
#else
  colorTextureHeader.mFormat = GL_RGB;
  colorTextureHeader.mInternalFormat = GL_RGB32F;
  colorTextureHeader.mType = GL_FLOAT;
#endif
  colorTextureHeader.mWidth = width;
  colorTextureHeader.mHeight = height;

  auto file = new flc::Texture2DFile();
  file->mConfig = flc::Texture2DFileConfig();
  file->mHeader = colorTextureHeader;
  file->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), file, parameters2D, size);
}

flc::Texture2D* TextureSystem::getDeferredColorScreen(GLuint width, GLuint height, GLuint size) {

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
  };

  flc::Texture2DFileHeader colorTextureHeader;
#ifdef FILLWAVE_GLES_3_0
  colorTextureHeader.mFormat = GL_RGB;
  colorTextureHeader.mInternalFormat = GL_RGBA;
  colorTextureHeader.mType = GL_UNSIGNED_BYTE;
#else
  colorTextureHeader.mFormat = GL_RGB;
  colorTextureHeader.mInternalFormat = GL_RGBA;
  colorTextureHeader.mType = GL_FLOAT;
#endif
  colorTextureHeader.mWidth = width;
  colorTextureHeader.mHeight = height;

  auto file = new flc::Texture2DFile();
  file->mConfig = flc::Texture2DFileConfig();
  file->mHeader = colorTextureHeader;
  file->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), file, parameters2D, size);
}

flc::Texture2D *TextureSystem::getDeferredDepth(GLuint width, GLuint height) {

  flc::ParameterList parameters;

  flc::Texture2DFileHeader depthTextureHeader;
  depthTextureHeader.mFormat = GL_DEPTH_COMPONENT;
  depthTextureHeader.mInternalFormat = GL_DEPTH_COMPONENT;
  depthTextureHeader.mWidth = width;
  depthTextureHeader.mHeight = height;
#ifdef FILLWAVE_GLES_3_0
  depthTextureHeader.mType = GL_UNSIGNED_INT;
#else
  depthTextureHeader.mType = GL_FLOAT;
#endif

  auto file = new flc::Texture2DFile();
  file->mConfig = flc::Texture2DFileConfig();
  file->mHeader = depthTextureHeader;
  file->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), file, parameters, 1);
}

flc::Texture2D *TextureSystem::getDeferredStencilDepth(GLuint width, GLuint height) {

  flc::ParameterList parameters;

  flc::Texture2DFileHeader stencilTextureHeader;
  stencilTextureHeader.mFormat = GL_DEPTH_STENCIL;
  stencilTextureHeader.mInternalFormat = GL_DEPTH32F_STENCIL8;
  stencilTextureHeader.mWidth = width;
  stencilTextureHeader.mHeight = height;
  stencilTextureHeader.mType = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;

  auto file = new flc::Texture2DFile();
  file->mConfig = flc::Texture2DFileConfig();
  file->mHeader = stencilTextureHeader;
  file->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), file, parameters, 1);
}

void TextureSystem::resize(GLuint width, GLuint height) {
  resize(mTextures2DDynamic, width, height);
  resize(mTextures2DRenderable, width, height);
}

void TextureSystem::evaluateDynamicTextures(GLfloat timeExpiredInSeconds) {
  for (auto &it : mTextures2DDynamic) {
    it.second->bindForWriting();
    it.second->draw(timeExpiredInSeconds);
  }
  flc::Framebuffer::bindScreenFramebuffer();
}

void TextureSystem::reload() {
#ifdef FILLWAVE_GLES_3_0
#else /* FILLWAVE_GLES_3_0 */
  reload(mTextures1D);
#endif /* FILLWAVE_GLES_3_0 */
  reload(mTextures2D);
  reload(mTextures2DDynamic);
  reload(mTextures2DRenderable);
  reload(mTextures3D);
  reload(mTextures3DRenderable);
  reload(mTextures3DDynamic);
  reload(mTextures2DDeferred);
}

} /* flf */
} /* flw */
