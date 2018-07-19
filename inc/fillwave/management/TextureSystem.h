#pragma once

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

#include <fillwave/core/texturing/Texture1D.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/core/rendering/Texture3DRenderableDynamic.h>
#include <fillwave/loaders/modelloader/ModelLoaderTraits.h>
#include <fillwave/loaders/TextureLoader.h>
#include <fillwave/management/base/TCache.h>

namespace flw {
namespace flf {

/*! \class TextureSystem
 * \brief Manager to handle TextureObject1D, TextureObject2D and TextureObject3D objects.
 */

class TextureSystem final {
public:
  TextureSystem(const std::string &rootPath);

  void checkExtensions();

  flc::Texture2D* get(
    const std::string& texturePath);

  flc::Texture3D* get(
    const std::string& posX
    , const std::string& negX
    , const std::string& posY
    , const std::string& negY
    , const std::string& posZ
    , const std::string& negZ);

  flc::Texture2DRenderable* getShadow2D(GLuint width, GLuint height);
  flc::Texture3DRenderable* getShadow3D(GLuint width, GLuint height);
  flc::Texture2DRenderable* getColor2D(GLuint width, GLuint height);
  flc::Texture2D* getDeferredColor(GLuint width, GLuint height, GLuint size = 1);
  flc::Texture2D* getDeferredColorScreen(GLuint width, GLuint height, GLuint size = 1);
  flc::Texture2D* getDeferredDepth(GLuint width, GLuint height);
  flc::Texture2D* getDeferredStencilDepth(GLuint width, GLuint height);
  flc::Texture2DRenderableDynamic*
    getDynamic(const std::string& fragmentShaderPath, flc::Program* program, glm::ivec2 screenSize);

  void reload();

  void populateDynamicTextures(GLfloat timeExpiredInSeconds);

  void drawDynamicTextures();

  void resizeTextures(GLuint width, GLuint height);

  void resize(GLuint width, GLuint height);

private:

#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
#else /* FILLWAVE_BACKEND_OPENGL_ES_30 */
  TCache<MAX_CACHE_SIZE, flc::Texture1D, size_t, flc::ParameterList &> mTextures1D;
#endif /* FILLWAVE_BACKEND_OPENGL_ES_30 */
  TCache<
    MAX_CACHE_SIZE
    , flc::Texture2D
    , std::string
    , flc::TextureConfig*
    , flc::ParameterList&
    , GLuint> mTextures2D;

  TCache<
    MAX_CACHE_SIZE
    , flc::Texture2D
    , size_t
    , flc::TextureConfig*
    , flc::ParameterList&
    , GLuint> mTextures2DDeferred;

  TCache<MAX_CACHE_SIZE
    , flc::Texture2DRenderableDynamic
    , std::string
    , flc::TextureConfig*
    , flc::ParameterList &
    , flc::Program*> mTextures2DDynamic;
  TCache<
    MAX_CACHE_SIZE
    , flc::Texture2DRenderable
    , size_t
    , GLenum
    , flc::TextureConfig*
    , flc::ParameterList&> mTextures2DRenderable;

  TCache<
    MAX_CACHE_SIZE
    , flc::Texture3D
    , std::string, flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::ParameterList&> mTextures3D;

  TCache<
    MAX_CACHE_SIZE
    , flc::Texture3DRenderableDynamic
    , std::string
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::ParameterList&
    , flc::Texture2DRenderable*
    , flc::Program *> mTextures3DDynamic;

  TCache<
    MAX_CACHE_SIZE
    , flc::Texture3DRenderable
    , size_t
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::TextureConfig*
    , flc::Texture2DRenderable*
    , flc::ParameterList&> mTextures3DRenderable;

  std::vector<GLenum> mSupportedCompresssionTypes;
  const std::string mRootPath;
  TextureLoader mLoader;

  template <class T>
  inline void reload(T &textures) {
    for (auto &it : textures) {
      it.second->reload();
    }
  }

  template <class T>
  inline void resize(T &textures, GLuint width, GLuint height) {
    for (auto &it : textures) {
      it.second->resize(width, height);
    }
  }
};

} /* flf */
} /* flw */
