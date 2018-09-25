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

#include <flw/flf/management/TextureSystem.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

TextureSystem::TextureSystem(const std::string &rootPath)
  : mRootPath(rootPath) {
  checkExtensions();
}

inline void TextureSystem::checkExtensions() {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  int numberOfExtensions = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &numberOfExtensions);

  for (int i = 0; i < numberOfExtensions; i++) {
    const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
    auto find_extension = [ccc](const char *name) -> bool {
      if (0 != (strcmp((const char *) ccc, name))) {
        return false;
      }
      fLogI(name, " compression supported");
      return true;
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

flc::Texture2D* TextureSystem::get(const std::string &texturePath) {
  const std::string filePath = mRootPath + texturePath;
  if (texturePath.empty()) {
    return nullptr;
  }

  if (nullptr != mTextures2D.get(filePath)) {
    return mTextures2D.get(filePath);
  }

  if (flc::TextureConfig* file = mLoader.load(filePath, GL_RGBA, mRootPath)) {
    fLogD("Texture ", filePath, " added to manager");
    flc::ParameterList parameters;
    return mTextures2D.store(filePath, file, parameters, 1);
  }

  fLogD("Texture ", filePath, " not found");
  return nullptr;
}

flc::Texture2DRenderableDynamic* TextureSystem::getDynamic(const std::string& fragmentShaderPath, flc::Program* program, glm::ivec2 screenSize) {
  std::string filePath = mRootPath + fragmentShaderPath;

  auto file = mLoader.load(screenSize.x, screenSize.y);

  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  return mTextures2DDynamic.store(fragmentShaderPath, file, parameters, program);
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
flc::Texture3D* TextureSystem::get(const std::string &posX,
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

  auto cfgPX =
    mLoader.load(filePathPosX, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
  auto cfgNX =
    mLoader.load(filePathNegX, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
  auto cfgPY =
    mLoader.load(filePathPosY, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
  auto cfgNY =
    mLoader.load(filePathNegY, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
  auto cfgPZ =
    mLoader.load(filePathPosZ, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
  auto cfgNZ =
    mLoader.load(filePathNegZ, GL_RGBA, mRootPath, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

  if (cfgPX && cfgNX && cfgPY && cfgNY && cfgPZ && cfgNZ) {
    fLogD("Texture ", name, " has been added to manager");

    auto t = mTextures3D.store(name, cfgPX, cfgNX, cfgPY, cfgNY, cfgPZ, cfgNZ, parameters);

    return t;
  }
  if (!cfgPX) {
    fLogD("3D Texture positive x ", posX, " not found");
  } else {
    delete cfgPX;
  }
  if (!cfgNX) {
    fLogD("3D Texture negative x ", negX, " not found");
  } else {
    delete cfgNX;
  }
  if (!cfgPY) {
    fLogD("3D Texture positive y ", posY, " not found");
  } else {
    delete cfgPY;
  }
  if (!cfgNY) {
    fLogD("3D Texture negative y ", negY, " not found");
  } else {
    delete cfgNY;
  }
  if (!cfgPZ) {
    fLogD("3D Texture positive z ", posZ, " not found");
  } else {
    delete cfgPZ;
  }
  if (!cfgNZ) {
    fLogD("3D Texture negative z ", negZ, " not found");
  } else {
    delete cfgNZ;
  }
  fLogE("Texture 3D ", name, " not added to manager");
  return nullptr;
}
#endif

flc::Texture2DRenderable* TextureSystem::getShadow2D(GLuint width, GLuint height) {
  auto cfg = new flc::TextureConfig();

  cfg->mHeader.mFormat = GL_DEPTH_COMPONENT;
  cfg->mHeader.mInternalFormat = GL_DEPTH_COMPONENT;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mBorder = 0;
  cfg->mHeader.mWidth = width;
  cfg->mHeader.mHeight = height;
  cfg->mData = nullptr;
  cfg->mContent.mMipmaps = GL_FALSE;
  cfg->mContent.mCompression = GL_FALSE;

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  cfg->mHeader.mType = GL_UNSIGNED_INT;
  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
  };
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30)
  cfg->mHeader.mType = GL_UNSIGNED_INT;
  flc::ParameterList parameters = {
      flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
      , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
      , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
      , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
      , flc::Parameter(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE)
      , flc::Parameter(GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL)
  };
#else
  cfg->mHeader.mType = GL_FLOAT;
  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
  };
#endif

  return mTextures2DRenderable.store(mTextures2DRenderable.size(), GL_DEPTH_ATTACHMENT, cfg, parameters);
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
flc::Texture3DRenderable* TextureSystem::getShadow3D(GLuint /*width*/, GLuint /*height*/) {

  flc::TextureConfig* file[6];
  for (GLint i = 0; i < 6; ++i) {
    file[i] = new flc::TextureConfig();
    file[i]->mHeader.mFormat = GL_RED;
    file[i]->mHeader.mInternalFormat = GL_R32F;
    file[i]->mContent.mMipmapsLevel = 0;
    file[i]->mContent.mBorder = 0;
    file[i]->mHeader.mWidth = 512;
    file[i]->mHeader.mHeight = 512;
    file[i]->mHeader.mType = GL_FLOAT;
    file[i]->mData = nullptr;
    file[i]->mContent.mMipmaps = GL_FALSE;
    file[i]->mContent.mCompression = GL_FALSE;
  }

  auto file2D = new flc::TextureConfig();
  file2D->mHeader.mFormat = GL_DEPTH_COMPONENT;
  file2D->mHeader.mInternalFormat = GL_DEPTH_COMPONENT32;
  file2D->mContent.mMipmapsLevel = 0;
  file2D->mContent.mBorder = 0;
  file2D->mHeader.mWidth = 512;
  file2D->mHeader.mHeight = 512;
  file2D->mHeader.mType = GL_FLOAT;
  file2D->mData = nullptr;
  file2D->mContent.mMipmaps = GL_FALSE;
  file2D->mContent.mCompression = GL_FALSE;

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
#endif

flc::Texture2DRenderable* TextureSystem::getColor2D(GLuint width, GLuint height) {

  auto cfg = new flc::TextureConfig();
  cfg->mHeader.mFormat = GL_RGBA;
  cfg->mHeader.mInternalFormat = GL_RGBA;
  cfg->mContent.mMipmapsLevel = 0;
  cfg->mContent.mBorder = 0;
  cfg->mHeader.mWidth = width;
  cfg->mHeader.mHeight = height;
#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
  cfg->mHeader.mType = GL_UNSIGNED_BYTE;
#else
  cfg->mHeader.mType = GL_FLOAT;
#endif
  cfg->mData = nullptr;
  cfg->mContent.mMipmaps = GL_FALSE;
  cfg->mContent.mCompression = GL_FALSE;

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  return mTextures2DRenderable.store(mTextures2DRenderable.size(), GL_COLOR_ATTACHMENT0, cfg, parameters2D);
}

flc::Texture2D* TextureSystem::getDeferredColor(GLuint width, GLuint height, GLuint size) {

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
  };

  flc::TextureConfig::Header colorTextureHeader;
#if defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)
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

  auto cfg = new flc::TextureConfig();
  cfg->mHeader = colorTextureHeader;
  cfg->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), cfg, parameters2D, size);
}

flc::Texture2D* TextureSystem::getDeferredColorScreen(GLuint width, GLuint height, GLuint size) {

  flc::ParameterList parameters2D = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
  };

  flc::TextureConfig::Header colorTextureHeader;
#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
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

  auto cfg = new flc::TextureConfig();
  cfg->mContent = flc::TextureConfig::Content();
  cfg->mHeader = colorTextureHeader;
  cfg->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), cfg, parameters2D, size);
}

flc::Texture2D* TextureSystem::getDeferredDepth(GLuint width, GLuint height) {

  flc::ParameterList parameters;

  flc::TextureConfig::Header depthTextureHeader;
  depthTextureHeader.mFormat = GL_DEPTH_COMPONENT;
  depthTextureHeader.mInternalFormat = GL_DEPTH_COMPONENT;
  depthTextureHeader.mWidth = width;
  depthTextureHeader.mHeight = height;
#if defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  depthTextureHeader.mType = GL_UNSIGNED_INT;
#else
  depthTextureHeader.mType = GL_FLOAT;
#endif

  auto cfg = new flc::TextureConfig();
  cfg->mContent = flc::TextureConfig::Content();
  cfg->mHeader = depthTextureHeader;
  cfg->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), cfg, parameters, 1);
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
flc::Texture2D* TextureSystem::getDeferredStencilDepth(GLuint width, GLuint height) {

  flc::ParameterList parameters;

  flc::TextureConfig::Header stencilTextureHeader;
  stencilTextureHeader.mFormat = GL_DEPTH_STENCIL;
  stencilTextureHeader.mInternalFormat = GL_DEPTH32F_STENCIL8;
  stencilTextureHeader.mWidth = width;
  stencilTextureHeader.mHeight = height;
  stencilTextureHeader.mType = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;

  auto* cfg = new flc::TextureConfig();
  cfg->mHeader = stencilTextureHeader;
  cfg->mData = nullptr;

  return mTextures2DDeferred.store(mTextures2DDeferred.size(), cfg, parameters, 1);
}
#endif

void TextureSystem::resize(GLuint width, GLuint height) {
  for (auto &it : mTextures2DDynamic) {
    it.second->mTexture2DRenderable.resize(width, height);
  }

  for (auto &it : mTextures2DRenderable) {
    it.second->resize(width, height);
  }
}

void TextureSystem::drawDynamicTextures() {
  for (auto &it : mTextures2DDynamic) {
    it.second->mTexture2DRenderable.bindForWriting();
    it.second->draw();
  }
  flc::Framebuffer::bindScreenFramebuffer();
}

void TextureSystem::populateDynamicTextures(GLfloat timeExpiredInSeconds) {
  for (auto &it : mTextures2DDynamic) {
    it.second->addTimeStep(timeExpiredInSeconds);
  }
}

void TextureSystem::reload() {
  for (auto &it : mTextures2D) {
    it.second->reload();
  }

  for (auto &it : mTextures2DDynamic) {
    it.second->reload();
  }

  for (auto &it : mTextures2DRenderable) {
    it.second->reload();
  }

  for (auto &it : mTextures2DDeferred) {
    it.second->reload();
  }

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else

  for (auto &it : mTextures3D) {
    it.second->reload();
  }

  for (auto &it : mTextures3DRenderable) {
    it.second->mTexture3D.mTexture.reload();
  }

  for (auto &it : mTextures1D) {
    it.second->mTexture.reload();
  }

#endif /* FILLWAVE_BACKEND_OPENGL_ES_20 */

}

} /* flf */
} /* flw */
