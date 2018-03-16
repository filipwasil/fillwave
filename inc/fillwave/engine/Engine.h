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

#include <fillwave/space/Scene.h>

#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/hud/Text.h>

#include <fillwave/common/pointers/PointerProtected.h>

/* Debugger */
#include "fillwave/Debugger.h"
#include "fillwave/common/Aliases.h"
#include "fillwave/actions/Event.h"

/* Common */
#include "fillwave/common/PhysicsMeshBuffer.h"

#ifdef __ANDROID__
struct ANativeActivity;
#endif

#include <fillwave/loaders/FileLoader.h>
#include <fillwave/management/CacheBuffer.h>
#include "fillwave/management/CacheProgram.h"
#include "fillwave/management/Cachehader.h"
#include "fillwave/management/CacheSampler.h"
#include "fillwave/management/LightSystem.h"
#include "fillwave/management/TextureSystem.h"

#include "fillwave/actions/EventHandler.h"
#include "fillwave/common/Macros.h"

#include "fillwave/Core.h"
#include "fillwave/Debugger.h"
#include "fillwave/Framework.h"

/* Management */


#ifdef __ANDROID__
struct ANativeActivity;
#else /* __ANDROID__ */
#include "fillwave/common/Strings.h"
#endif /* __ANDROID__ */

#include <fillwave/loaders/FileLoader.h>
#include <fillwave/management/CacheBuffer.h>
#include <fillwave/loaders/ModelLoader.h>

namespace flw {
namespace flf {
class Focusable;
}
namespace flc {
/* All buffers should be there */
class IndexBuffer;
struct VertexParticleGPU;
struct VertexPosition;
struct VertexFloat;
class VertexBufferParticles;
class VertexBufferParticlesGPU;
class VertexBufferFloat;
class VertexBufferPosition;
}

/*! \class EngineBase
 * \brief Fillwave engine core
 */

class Engine {
 public:
  Engine(GLint argc, GLchar *const argv[]);

  virtual ~Engine();

  /* Configuration */
  void configDebugger(EDebuggerState state);
  void configFileLogging(std::string fileName = "");
  void configFPSCounter(std::string fontName = "", glm::vec2 position = glm::vec2(-0.95, 0.95), GLfloat size = 100.0);
  void configBackgroundColor(glm::vec3 color);
  void configTime(GLfloat timeFactor);

  /* Draw */
  void draw(GLfloat time);
  void drawLines(GLfloat time);
  void drawPoints(GLfloat time);
  void drawTexture(flc::Texture *t, flc::Program *p);
  void drawTexture(flc::Texture *t);

  /* Remove */
  void detach(ps<flf::Text> text);
  void detach(flf::LightSpot *light);
  void detach(flf::LightDirectional *light);
  void detach(flf::LightPoint *light);
  void detachLights();
  void detach(flf::Entity*);

  /* Assets */
  pu<flf::PhysicsMeshBuffer> getPhysicalMeshBuffer(const std::string &shapePath);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  const aiScene* getModelFromFile(const std::string& path);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  /* Scene */
  void setCurrentScene(pu<flf::Scene> &&scene);
  pp<flf::Scene> getCurrentScene() const;

  /* Time */
  GLuint getFramesPassed();
  GLfloat getStartupAnimationTime() const;

  /**
   * Store shaders.
   *
   * T can be:
   *
   * GL_VERTEX_SHADER
   * GL_TESS_CONTROL_SHADER
   * GL_TESS_EVALUATION_SHADER
   * GL_GEOMETRY_SHADER
   * GL_FRAGMENT_SHADER
   */
  template <GLuint T> flc::Shader* storeShader(const std::string &shaderPath);
  template <GLuint T> flc::Shader* storeShader(const std::string &shaderPath, const std::string &shaderSource);
  flc::Program* storeProgram(const std::string &name, const std::vector<flc::Shader *> &shaders, bool isSkipLinking = false);

  /* Store textures */
  flc::Texture2D* storeTexture(const std::string &path, flf::ECompression com = flf::ECompression::none);

  flc::Texture2DRenderable* storeTextureRenderable();

  flc::Texture2DRenderableDynamic* storeTextureDynamic(const std::string &fragmentShaderPath);

  flc::Texture3D* storeTexture3D(
    const std::string &posX
    , const std::string &negX
    , const std::string &posY
    , const std::string &negY
    , const std::string &posZ
    , const std::string &negZ);

  /* Store lights */
  flf::LightSpot* storeLightSpot(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable *followed = nullptr);
  flf::LightPoint* storeLightPoint(glm::vec3 position, glm::vec4 color, flf::Moveable *followed = nullptr);
  flf::LightDirectional* storeLightDirectional(glm::vec3 position,
    glm::quat rotation,
    glm::vec4 color,
    flf::Moveable* followed = nullptr);

  /* Store text */
  ps<flf::Text> storeText(const std::string &content,
    const std::string &fontName,
    glm::vec2 position,
    GLfloat scale = 1.0f,
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    ETextEffect effect = ETextEffect::none);

  /* Store sampler */
  flc::Sampler* storeSO(GLint textureUnit);

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
  void removeBuffer(flc::VertexArray* vao); //todo any idea of generic class ? template it ?
  void removeBufferIndex(flc::VertexArray* vao);
  void removeBufferIndexParticles(flc::VertexArray* vao);
  void removeBufferBasic(flc::VertexArray* vao);
  void removeBufferText(flc::VertexArray* vao);

  /* Pick */
  void pick(GLuint x, GLuint y);

  /* Screen */
  glm::ivec2 getScreenSize() const;
  GLfloat getScreenAspectRatio() const;

  /* Log */
  void log();

  /* Screenshot */
  void captureFramebufferToFile(const std::string &name);
  void captureFramebufferToBuffer(GLubyte *buf, GLint *sizeInBytes, GLuint format = GL_RGBA, GLint bytesPerPixel = 4);

  /* Post processing */
  void addPostProcess(const std::string &fragmentShaderPath, GLfloat lifeTime = flf::FILLWAVE_ENDLESS);

  void reload();

  /* Systems */
  flf::LightSystem& getLightSystem() const;
  flf::TextureSystem& getTextureSystem() const;

 private:

  flc::VertexBufferBasic* storeBufferInternal(flc::VertexArray *vao,
    flf::TerrainConstructor *constructor,
    GLint density,
    GLfloat gap,
    std::vector<GLuint> &indices);

  flc::VertexBufferBasic* storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexBasic> &data);

  flc::VertexBufferText* storeBufferInternal(flc::VertexArray *vao,
    const std::vector<GLfloat> &data,
    const std::vector<GLfloat> &textureCoords);

  flc::VertexBufferParticlesGPU*
  storeBuffersInternal(flc::VertexArray *vao, size_t idx, std::vector<flc::VertexParticleGPU> &particles);

  flc::VertexBufferParticles *storeBufferInternal(flc::VertexArray *vao,
    std::vector<GLfloat> &velocities,
    std::vector<GLfloat> &positions,
    std::vector<GLfloat> &times);

  flc::VertexBufferDebug* storeBufferInternal(flc::VertexArray *vao, GLfloat scale);
  flc::VertexBufferFloat* storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexFloat> &data);
  flc::VertexBufferPosition* storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexPosition> &data);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  flc::VertexBufferBasic*
  storeBufferInternal(flc::VertexArray *vao, const aiMesh *shape, flf::Animator *animator);

  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, const aiMesh *shape);

#else
  flc::VertexBufferBasic* storeBufferInternal(flc::VertexArray* vao,
      tinyobj::shape_t& shape, tinyobj::attrib_t& attributes);
#endif

  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, const std::vector<GLuint> &data);
  flc::IndexBuffer* storeBufferInternal(flc::VertexArray *vao, GLuint elements);


  /* Screen */
  GLuint mWindowWidth = 1920;
  GLuint mWindowHeight = 1200;
  GLfloat mWindowAspectRatio = 1200.0f / 1920.0f;

  /* Loaders */
  flf::FontLoader mFontLoader;
  flf::FileLoader mFileLoader;
  flf::ProgramLoader mProgramLoader;

  /* Picking */
  flc::Texture2DRenderable* mPickingRenderableTexture;
  pu<flc::PixelBuffer> mPickingPixelBuffer;

  /* Resources */
  flf::CacheShader mShaders;
  flf::CacheProgram mPrograms;
  flf::CacheSampler mSamplers;
  std::vector<ps<flf::Text>> mTextManager;
  std::vector<ps<Font>> mFontManager;
  flf::CacheBuffer mBuffers;
  pu<flf::LightSystem> mLights;
  pu<flf::TextureSystem> mTextures;
  std::vector<flc::PostProcessingPass> mPostProcessingPasses;
  flc::Program* mProgramTextureLookup;

  /* Fences and barriers */
  puFence mFence;

  /* OQ */
  flc::Program *mProgramOcclusionBox;
  flc::VertexBufferPosition *mVBOOcclusion;
  flc::VertexArray *mVAOOcclusion;

  /* Input handlers */
  flf::vec<flf::EventHandler> mHandlers;

  /* Extras */
  pu<flf::Debugger> mDebugger;
  GLuint mFrameCounter;
  GLfloat mTimeFactor;
  ps<flf::Text> mFPSText;
  //flf::FPSCallback mTextFPSCallback;

  /* Startup */
  GLfloat mStartupTime;
  flc::Texture* mStartupTexture;
  const GLfloat mStartupTimeLimit = 8.0f;
  pu<flc::PostProcessingPass> mPostProcessingPassStartup;

  /* Options */
  GLboolean mIsOQ;

  /* Scene */
  pu<flf::Scene> mScene;
  glm::vec3 mBackgroundColor;

  ModelLoader mModelLoader;

 public:
  /* Events */
  void onEvent(const flf::Event& event) const;
  void onResizeScreen(GLuint width, GLuint height);
  void attachHandler(std::function<void(const flf::Event&)>&& h, flf::EEventType type);
  void detachHandlers();

 private:

  /* Initiatization */
  void init();
  void initExtensions();
  void initContext();
  void initPickingBuffer();
  void initPipelines();
  void initUniforms();
  void initManagement();
  void initExtras();
  void initOcclusionTest();
  void initStartup();

  /* Evaluation */
  void evaluateShadowMaps();
  void evaluateDebugger();
  void evaluateDynamicTextures(GLfloat timeExpiredInSeconds);
  void evaluateTime(GLfloat timeExpiredInSeconds);
  void evaluateStartupAnimation(GLfloat time);

  void drawFront();
  void drawOcclusionPass();

  /* IRenderer */
  void drawClear();
  void drawHUD();
  void drawSceneStartup();
  void drawScene(GLfloat time);
  void drawSceneCore();

  /* Picking */
  glm::ivec4 pickingBufferGetColor(GLubyte* data, GLuint x, GLuint y);

  void reloadPickingBuffer();

};

} /* flw */