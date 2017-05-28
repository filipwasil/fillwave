#pragma once

/*
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

#include <fillwave/space/Scene.h>

#include <fillwave/space/LightPoint.h>
#include <fillwave/space/LightSpot.h>
#include <fillwave/space/LightDirectional.h>
#include <fillwave/hud/Text.h>

#include <fillwave/common/TGetter.h>

/* Debugger */
#include <fillwave/Debugger.h>

/* Common */
#include <fillwave/common/PhysicsMeshBuffer.h>

#ifdef __ANDROID__
struct ANativeActivity;
#endif

namespace flw {
namespace flf {
class Focusable;
}
namespace flc {
/* All buffers should be there */
//flc::VertexBufferBasic
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
 * \brief Fillwave engine.
 */

class Engine final {
public:
#ifdef __ANDROID__
  Engine(std::string rootPath);
  Engine(ANativeActivity* activity);
#else

  Engine(GLint argc, GLchar *const argv[]);

#endif

  virtual ~Engine();

  /* Configuration */
  void configDebugger(eDebuggerState state);
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
  void detach(pText text);
  void detach(flf::LightSpot *light);
  void detach(flf::LightDirectional *light);
  void detach(flf::LightPoint *light);
  void detachLights();
  void detach(flf::Entity*);

  /* Assets */
  puPhysicsMeshBuffer getPhysicalMeshBuffer(const std::string &shapePath);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  const aiScene *getModelFromFile(std::string path); /* xxx remove */
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  /* Scene */
  void setCurrentScene(puScene &&scene);
  TGetter<flf::Scene> getCurrentScene() const;

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
  template <GLuint T> flc::Shader *storeShader(const std::string &shaderPath);
  template <GLuint T> flc::Shader *storeShader(const std::string &shaderPath, const std::string &shaderSource);
  flc::Program * storeProgram(const std::string &name, const std::vector<flc::Shader *> &shaders, bool isSkipLinking = false);

  /* Store textures */
  flc::Texture2D *storeTexture(const std::string &path, flf::eCompression com = flf::eCompression::eNone);

  flc::Texture2DRenderable *storeTextureRenderable();

  flc::Texture2DRenderableDynamic *storeTextureDynamic(const std::string &fragmentShaderPath);

  flc::Texture3D *storeTexture3D(const std::string &posX,
      const std::string &negX,
      const std::string &posY,
      const std::string &negY,
      const std::string &posZ,
      const std::string &negZ);

  /* Store lights */
  flf::LightSpot *storeLightSpot(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable *followed = nullptr);
  flf::LightPoint *storeLightPoint(glm::vec3 position, glm::vec4 color, flf::Moveable *followed = nullptr);
  flf::LightDirectional *storeLightDirectional(glm::vec3 position,
      glm::quat rotation,
      glm::vec4 color,
      flf::Moveable *followed = nullptr);

  /* Store text */
  pText storeText(const std::string &content,
      const std::string &fontName,
      glm::vec2 position,
      GLfloat scale = 1.0f,
      glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
      eTextEffect effect = eTextEffect::eNone);

  /* Store sampler */
  flc::Sampler *storeSO(GLint textureUnit);

  /* Store vertex array objects */
  flc::VertexArray *storeVAO(flf::IReloadable *user, flc::VertexArray *vao = nullptr);

  /* Store one buffer for one VAO */
  template <class T, typename ...S>
  T *storeBuffer(flc::VertexArray *vao, S ... p) {
    return storeBufferInternal(vao, p...);
  }

  /* Enables to store many buffers in one VAO */
  template <class T, typename ...S>
  T *storeBuffers(flc::VertexArray *vao, size_t idx, S ... p) {
    return storeBuffersInternal(vao, idx, p...);
  }

  /* Buffering */
  void removeBuffer(flc::VertexArray *vao); //todo any idea of generic class ? template it ?
  void removeBufferIndex(flc::VertexArray *vao);
  void removeBufferIndexParticles(flc::VertexArray *vao);
  void removeBufferBasic(flc::VertexArray *vao);
  void removeBufferText(flc::VertexArray *vao);

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

  /* Inputs - focus */
  void dropFocus(flf::IFocusable *focusable = nullptr);

  /* Inputs */
  void insertInput(flf::EventType &event);
  void insertResizeScreen(GLuint width, GLuint height);
  void attachCallback(puCallback &&callback, flf::IFocusable *focusable = nullptr);
  void detachCallback(flf::Callback *callback);
  void detachCallbacks(eEventType eventType);
  void detachCallbacks();
  void reload();

  /* Systems */
  flf::LightSystem &getLightSystem() const;
  flf::TextureSystem &getTextureSystem() const;

private:
  struct EngineImpl;
  std::unique_ptr<EngineImpl> mImpl;

  flc::VertexBufferBasic *storeBufferInternal(flc::VertexArray *vao,
      flf::TerrainConstructor *constructor,
      GLint density,
      GLfloat gap,
      std::vector<GLuint> &indices);

  flc::VertexBufferBasic *storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexBasic> &data);

  flc::VertexBufferText *storeBufferInternal(flc::VertexArray *vao,
      const std::vector<GLfloat> &data,
      const std::vector<GLfloat> &textureCoords);

  flc::VertexBufferParticlesGPU *
  storeBuffersInternal(flc::VertexArray *vao, size_t idx, std::vector<flc::VertexParticleGPU> &particles);

  flc::VertexBufferParticles *storeBufferInternal(flc::VertexArray *vao,
      std::vector<GLfloat> &velocities,
      std::vector<GLfloat> &positions,
      std::vector<GLfloat> &times);

  flc::VertexBufferDebug *storeBufferInternal(flc::VertexArray *vao, GLfloat scale);

  flc::VertexBufferFloat *storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexFloat> &data);

  flc::VertexBufferPosition *storeBufferInternal(flc::VertexArray *vao, std::vector<flc::VertexPosition> &data);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  flc::VertexBufferBasic *
  storeBufferInternal(flc::VertexArray *vao, const aiMesh *shape, flf::Animator *animator);

  flc::IndexBuffer *storeBufferInternal(flc::VertexArray *vao, const aiMesh *shape);

#else
  flc::VertexBufferBasic* storeBufferInternal(flc::VertexArray* vao,
      tinyobj::shape_t& shape, tinyobj::attrib_t& attributes);
#endif

  flc::IndexBuffer *storeBufferInternal(flc::VertexArray *vao, const std::vector<GLuint> &data);

  flc::IndexBuffer *storeBufferInternal(flc::VertexArray *vao, GLuint elements);
};

} /* flw */