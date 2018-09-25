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

#include <fillwave/Config.h>

#include <fillwave/management/TextureSystem.h>

#include <fillwave/common/Aliases.h>

#include <fillwave/space/Scene.h>

#include <fillwave/common/Macros.h>

#include <fillwave/actions/Event.h>

#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/hud/Text.h>

#include <fillwave/actions/EventHandler.h>

#include <fillwave/loaders/FileLoader.h>
#include <fillwave/loaders/ModelLoader.h>
#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/management/CacheBuffer.h>
#include <fillwave/management/CacheProgram.h>
#include <fillwave/management/Cachehader.h>
#include <fillwave/management/CacheSampler.h>

#include <fillwave/management/LightSystem.h>


#include <fillwave/core/operations/PostProcessingPass.h>

#include <fillwave/Debugger.h>

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
#include <fillwave/core/extended/buffers/PixelBuffer.h>
#include <fillwave/core/extended/pipeline/Fence.h>
#endif

namespace flw {
namespace flf {
class Focusable;
}
namespace flc {
class IndexBuffer;
struct VertexParticleGPU;
struct VertexPosition;
struct VertexFloat;
class VertexBufferParticles;
class VertexBufferParticlesGPU;
class VertexBufferFloat;
class VertexBufferPosition;
}

/*! \class Engine
 * \brief Fillwave engine core
 */

class Engine {
 public:
  Engine(const std::string& runtimeBinaryFilePath, bool isEveryExtensionSuccessfullyLoaded);

  virtual ~Engine();

  /* Configuration */
  void configDebugger(EDebuggerState state);
  void configFileLogging(std::string fileName = "");
  void configFPSCounter(std::string fontName = "", glm::vec2 position = glm::vec2(-0.95, 0.95), GLfloat size = 100.0);
  void configBackgroundColor(glm::vec3 color);
  void configTime(GLfloat timeFactor);

  /* Draw */
  void draw();
  void drawLines();
  void drawPoints();
  void drawTexture(flc::Texture2D* t, flc::Program* p);
  void drawTexture(flc::Texture2D* t);

  /* Remove */
  void detach(ps<flf::Text> text);
  void detach(flf::LightSpot* light);
  void detach(flf::LightDirectional* light);
  void detach(flf::LightPoint* light);
  void detachLights();
  void detach(flf::Entity*);

  /* Assets */
  void getPhysicalMeshBuffer(const std::string& path, flf::PhysicsMeshBuffer& buffer);
  const std::string getGlobalPath(const std::string& localPath);

  /* Scene */
  void setCurrentScene(pu<flf::Scene> &&scene);
  pp<flf::Scene> getCurrentScene() const;

  /* Time */
  GLuint getAndResetRenderedFramesCount();

  template <GLuint T> flc::Shader* storeShader(const std::string& shaderPath);
  template <GLuint T> flc::Shader* storeShader(const std::string& shaderPath, const std::string& shaderSource);
  flc::Program* storeProgram(const std::string &name, const vec<flc::Shader *> &shaders, bool isSkipLinking = false);

  /* Store textures */
  flc::Texture2D* storeTexture(const std::string &path);

  flc::Texture2DRenderable* storeTextureRenderable();

  flc::Texture2DRenderableDynamic* storeTextureDynamic(const std::string &fragmentShaderPath);

  /* Store lights */
  flf::LightSpot* storeLightSpot(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable *followed = nullptr);
  flf::LightPoint* storeLightPoint(glm::vec3 position, glm::vec4 color, flf::Moveable *followed = nullptr);
  flf::LightDirectional* storeLightDirectional(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable* m = nullptr);

  /* Store text */
  ps<flf::Text> storeText(
    const std::string &text
    , const std::string &font
    , glm::vec2 pos
    , GLfloat scale = 1.0f
    , glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    , ETextEffect effect = ETextEffect::none);

  /* Store vertex array objects */
  flc::VertexArray* storeVAO(flf::IReloadable *user, flc::VertexArray *vao = nullptr);

  /* Store one buffer for one VAO */
  template <class T, typename ...S>
  T* storeBuffer(flc::VertexArray *vao, S ... p) {
    return storeBufferInternal(vao, p...);
  }

  /* Enables to store many buffers in one VAO */
  template <class T, typename ...S>
  T* storeBuffers(flc::VertexArray *vao, size_t idx, S ... p) {
    return storeBuffersInternal(vao, idx, p...);
  }

  /* Buffering */
  void removeBuffer(flc::VertexArray* vao);
  void removeBufferIndex(flc::VertexArray* vao);
  void removeBufferIndexParticles(flc::VertexArray* vao);
  void removeBufferBasic(flc::VertexArray* vao);
  void removeBufferText(flc::VertexArray* vao);

  /* Screenshot */
  void captureFramebufferToFile(const std::string &name);
  void captureFramebufferToBuffer(GLubyte *buf, GLint *sizeInBytes, GLuint format = GL_RGBA, GLint bytesPerPixel = 4);

  /* Systems */
  flf::LightSystem& getLightSystem() const;
  flf::TextureSystem& getTextureSystem() const;

  /* Screen */
  glm::ivec2 getScreenSize() const;
  GLfloat getScreenAspectRatio() const;

  /* Log */
  void log();

  /* Post processing */
  void addPostProcess(const std::string &fragmentShaderPath, GLfloat lifeTime = flf::FILLWAVE_ENDLESS);
  void reload();

  /* Screen */
  GLuint mWindowWidth;
  GLuint mWindowHeight;
  GLfloat mWindowAspectRatio;

  /* Loaders */
  flf::FontLoader mFontLoader;
  flf::FileLoader mFileLoader;
  flf::ProgramLoader mProgramLoader;
  ModelLoader mModelLoader;

  /* Picking */
  flc::Texture2DRenderable* mPickingRenderableTexture;
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  pu<flc::PixelBuffer> mPickingPixelBuffer;
  pu<flc::Fence> mFence;

  flf::CacheSampler mSamplers;
#endif

  /* Resources */
  flf::CacheShader mShaders;
  flf::CacheProgram mPrograms;
  vec<ps<flf::Text>> mTextManager;
  vec<ps<Font>> mFontManager;
  flf::CacheBuffer mBuffers;
  pu<flf::LightSystem> mLights;
  pu<flf::TextureSystem> mTextures;
  vec<flc::PostProcessingPass> mPostProcessingPasses;
  flc::Program* mProgramTextureLookup;

  /* OQ */
  flc::Program* mProgramOcclusionBox;
  flc::VertexBufferPosition* mVBOOcclusion;
  flc::VertexArray* mVAOOcclusion;

  /* Input handlers */
  vec<flf::EventHandler> mHandlers;

  /* Extras */
  pu<flf::Debugger> mDebugger;
  GLuint mFrameCounter;
  GLfloat mTimeFactor;
  ps<flf::Text> mFPSText;

  GLboolean mIsOQ;

  pu<flf::Scene> mScene;

  glm::vec3 mBackgroundColor;

 public:
  void onEvent(const flf::Event& event);
  void onResizeScreen(GLuint width, GLuint height);
  void onPick(GLuint xScreenSpace, GLuint yScreenSpace);
  void attachHandler(std::function<void(const flf::Event&)>&& h, flf::EEventType type);
  void detachHandlers();

 private:
  void init();
  void initContext();

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
 public:
   flc::Texture3D* storeTexture3D(
    const std::string &posX
    , const std::string &negX
    , const std::string &posY
    , const std::string &negY
    , const std::string &posZ
    , const std::string &negZ);

  flc::Sampler* storeSO(GLint textureUnit);

 private:
  void initPickingBuffer();
#endif

  void initPipelines();
  void initUniforms();
  void initManagement();
  void initExtras();
  void initOcclusionTest();

  void populateLights();
  void populateDebugger();
  void populateDynamicTextures(GLfloat timeExpiredInSeconds);

  void drawFront();
  void drawOcclusionPass();

  /* IRenderer */
  void drawClear();
  void drawHUD();
  void drawSceneStartup();
  void drawScene();
  void updatePostprocessing(GLfloat time);
  void drawSceneCore();

  flc::VertexBufferBasic*
    storeBufferInternal(
      flc::VertexArray* vao
      , flf::TerrainConstructor* constructor
      , GLint density
      , GLfloat gap
      , vec<GLuint> &indices);

  flc::VertexBufferBasic*
    storeBufferInternal(
      flc::VertexArray *vao
      , vec<flc::VertexBasic> &data);

  flc::VertexBufferText*
    storeBufferInternal(
      flc::VertexArray *vao
      , const vec<GLfloat> &data
      , const vec<GLfloat> &coords);

  flc::VertexBufferParticlesGPU*
    storeBuffersInternal(
      flc::VertexArray *vao
      , size_t idx
      , vec<flc::VertexParticleGPU> &particles);

  flc::VertexBufferParticles*
    storeBufferInternal(
      flc::VertexArray *vao
      , vec<GLfloat> &vel
      , vec<GLfloat> &pos
      , vec<GLfloat> &tim);

  flc::VertexBufferBasic* storeBufferInternal(
    flc::VertexArray* vao
    , const ModelLoader::ShapeType* shape
    , ModelLoader::Animator* animator);

  flc::VertexBufferDebug* storeBufferInternal(flc::VertexArray *vao, GLfloat scale);
  flc::VertexBufferFloat* storeBufferInternal(flc::VertexArray *vao, vec<flc::VertexFloat> &data);
  flc::VertexBufferPosition* storeBufferInternal(flc::VertexArray *vao, vec<flc::VertexPosition> &data);
  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, const ModelLoader::ShapeType* shape);
  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, const vec<GLuint> &data);
  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, GLuint elements);

 private:
  /* Pick */
  glm::ivec4 pickingBufferGetColor(GLubyte* data, GLuint x, GLuint y);
  void reloadPickingBuffer();

};

} /* flw */
