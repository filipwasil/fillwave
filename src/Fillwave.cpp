/*
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Fillwave developers
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

/* Debug */
#include <fillwave/Config.h>

/* Logs */
#include <fillwave/Log.h>

/* flw */

#include <fillwave/Fillwave.h>

/* Stdlib */
#include <fstream>

/* Implementation */
#include  <impl/FillwaveImpl.h>

using namespace flw::flc;
using namespace std;

namespace flw {

#ifdef __ANDROID__

Engine::Engine(string rootPath) {
  mImpl = make_unique<EngineImpl>(this, rootPath);
  /* This init has to be outside of the initializer list,
   * because it needs mImpl to be created fully before Initialization.
   * mImpl uses Engine functions */
  mImpl->init();
}

Engine::Engine(ANativeActivity* activity) {
  mImpl = make_unique<EngineImpl>(this, activity);
  /* This init has to be outside of the initializer list,
   * because it needs mImpl to be created fully before Initialization.
   * mImpl uses Engine functions */
  mImpl->init();
}
#else

Engine::Engine(GLint argc, GLchar *const argv[]) {
  mImpl = make_unique<EngineImpl>(this, argc, argv);
  /* This init has to be outside of the initializer list,
   * because it needs mImpl to be created fully before Initialization.
   * mImpl uses Engine functions */
  mImpl->init();
}

#endif

Engine::~Engine() = default;

void Engine::configureBackgroundColor(glm::vec3 color) {
  mImpl->mBackgroundColor = color;
}

void Engine::configureTime(GLfloat timeFactor) {
  mImpl->mTimeFactor = timeFactor;
}

void Engine::draw(GLfloat time) {
  mImpl->draw(time);
}

#ifdef FILLWAVE_GLES_3_0
#else

void Engine::drawLines(GLfloat time) {
  mImpl->drawLines(time);
}

void Engine::drawPoints(GLfloat time) {
  mImpl->drawPoints(time);
}

#endif

void Engine::drawTexture(Texture *t, Program *p) {
  mImpl->drawTexture(t, p);
}

void Engine::drawTexture(Texture *t) {
  mImpl->drawTexture(t);
}

LightSpot *Engine::storeLightSpot(glm::vec3 position, glm::quat rotation, glm::vec4 color, Moveable *followed) {
  return mImpl->mLights->mLightsSpot.add(mImpl->mTextures->getShadow2D(mImpl->mWindowWidth, mImpl->mWindowHeight),
                                         position,
                                         rotation,
                                         color,
                                         followed);
}

LightPoint *Engine::storeLightPoint(glm::vec3 position, glm::vec4 color, Moveable *followed) {
  return mImpl->mLights->mLightsPoint.add(mImpl->mTextures->getShadow3D(mImpl->mWindowWidth, mImpl->mWindowHeight),
                                          position,
                                          color,
                                          followed);
}

LightDirectional *
Engine::storeLightDirectional(glm::vec3 position, glm::quat rotation, glm::vec4 color, Moveable *followed) {
  return mImpl->mLights->mLightsDirectional.add(mImpl->mTextures->getShadow2D(mImpl->mWindowWidth,
                                                                              mImpl->mWindowHeight),
                                                position,
                                                rotation,
                                                color,
                                                followed);
}

Program *Engine::storeProgram(const string &name, const vector<Shader *> &shaders, bool isSkipLinking) {
  return mImpl->mPrograms.store(name, shaders, isSkipLinking);
}

Texture2D *Engine::storeTexture(const string &texturePath, flf::eCompression compression) {
  return mImpl->mTextures->get(texturePath, compression);
}

Texture2DRenderable *Engine::storeTextureRenderable() {
  return mImpl->mTextures->getColor2D(mImpl->mWindowWidth, mImpl->mWindowHeight);
}

Texture2DRenderableDynamic *Engine::storeTextureDynamic(const string &fragmentShaderPath) {
  const string path = fragmentShaderPath;
  Program *program = mImpl->mProgramLoader.getQuadCustomFragmentShader(fragmentShaderPath);
  return mImpl->mTextures->getDynamic(path, program, glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight));;
}

Texture3D *Engine::storeTexture3D(const string &posX,
    const string &negX,
    const string &posY,
    const string &negY,
    const string &posZ,
    const string &negZ) {
  return mImpl->mTextures->get(posX, negX, posY, negY, posZ, negZ);
}

Sampler *Engine::storeSO(GLint textureUnit) {
  return mImpl->mSamplers.store(textureUnit, textureUnit);
}

VertexArray *Engine::storeVAO(flf::IReloadable *user, VertexArray *vao) {
  return vao ? mImpl->mBuffers.mVertexArrays.store(vao, user) : mImpl->mBuffers.mVertexArrays.store(user);
}

/* Inputs - insert */
void Engine::insertInput(flf::EventType &event) {
#ifdef FILLWAVE_COMPILATION_OPTIMIZE_ONE_FOCUS
  if (mImpl->mFocus.first) {
    mImpl->mFocus.first->handleFocusEvent(event);
  }
#else
  for (auto &focusable : mImpl->mFocus) {
    focusable.first->handleFocusEvent(event);
  }
#endif
  mImpl->runCallbacks(event);
}

/* Engine callbacks - clear */
void Engine::clearCallback(flf::Callback *callback) {
  mImpl->clearCallback(callback);
}

void Engine::clearCallbacks(eEventType eventType) {
  mImpl->clearCallbacks(eventType);
}

void Engine::clearCallbacks() {
  mImpl->clearCallbacks();
}

/* Callbacks registeration */
void Engine::registerCallback(puCallback &&callback, flf::IFocusable *focusable) {
  if (focusable) {
#ifdef FILLWAVE_COMPILATION_OPTIMIZE_ONE_FOCUS
    if (mImpl->mFocus.first) {
      dropFocus(mImpl->mFocus.first);
    }
    mImpl->mFocus.first = focusable;
    mImpl->mFocus.second.push_back(callback.get());
#else
    if (mImpl->mFocus.find(focusable) == mImpl->mFocus.end()) {
      mImpl->mFocus[focusable] = vector<Callback *>(1, callback.get());
    } else {
      mImpl->mFocus[focusable].push_back(callback.get());
    }
#endif
  }
  mImpl->registerCallback(move(callback));
}

void Engine::dropFocus(flf::IFocusable *focusable) {
#ifdef FILLWAVE_COMPILATION_OPTIMIZE_ONE_FOCUS
  if (focusable == mImpl->mFocus.first) {
    for (auto& it : mImpl->mFocus.second) {
      mImpl->unregisterCallback(it);
    }
    mImpl->mFocus.first = nullptr;
    mImpl->mFocus.second.clear();
  }
#else
  fLogE("mImpl->mFocus.size() %lu", mImpl->mFocus.size());
  if (!mImpl->mFocus.empty() && mImpl->mFocus.find(focusable) != mImpl->mFocus.end()) {
    for (auto &it : mImpl->mFocus[focusable]) {
      mImpl->unregisterCallback(it);
    }
  }
#endif
}

void Engine::unregisterCallback(flf::Callback *callback) {
  mImpl->unregisterCallback(callback);
}

pText Engine::storeText(const string &content,
    const string &fontName,
    glm::vec2 position,
    GLfloat scale,
    glm::vec4 color,
    eTextEffect effect) {
  /* Check for the font texture */
  if (!mImpl->mTextures->get(fontName + ".png")) {
    mImpl->mFontLoader.load(mImpl->mFileLoader.getRootPath() + fontName);
  }
  Texture2D *t = mImpl->mTextures->get(fontName + ".png", flf::eCompression::eNone, flf::eFlip::eVertical);

  Font *font = nullptr;
  for (auto &it : mImpl->mFontManager) {
    if (it->mName == fontName) {
      font = it.get();
    }
  }

  if (!font) {
    ifstream myfile(mImpl->mFileLoader.getRootPath(fontName + ".meta"));
    if (!myfile.is_open()) {
      fLogE("No text added. Could not write to metadata file: %s", (fontName + ".meta").c_str());
      return pText();
    }
    string line;
    string ASCII, xMin, width, yMin, height, yOffset;
    GLfloat fXMin, fWidth, fYMin, fHeight, fYOffset;
    GLint iASCII;
    Font *newFont = new Font();
    GLint control = 0;
    while (!myfile.eof()) {
      getline(myfile, line);
      myfile >> iASCII >> fXMin >> fWidth >> fYMin >> fHeight >> fYOffset;
      newFont->mWidths[iASCII] = fWidth;
      newFont->mOffsets[iASCII] = 1.0f - fHeight - fYOffset;
      if (control++ > 512) { //xxx limit
        fLogE("Metadata can not be read for file %s.", (fontName + ".meta").c_str());
        myfile.close();
        delete newFont;
        return pText();
      }
    }
    myfile.close();
    mImpl->mFontManager.push_back(pFont(newFont));
    font = newFont;
  }

  pText text = make_shared<flf::Text>(content, t, position, this, scale, font, color, effect);
  mImpl->mTextManager.push_back(pText(text));
  return text;
}

void Engine::clearText(pText text) {
  auto _compare_function = [text](pText t) -> bool {
    return (t == text);
  };
  auto _begin = mImpl->mTextManager.begin();
  auto _end = mImpl->mTextManager.end();
  auto it = remove_if(_begin, _end, _compare_function);
  mImpl->mTextManager.erase(it, _end);
}

void Engine::clearLight(LightSpot *light) {
  auto new_end = remove_if(mImpl->mLights->mLightsSpot.begin(),
                           mImpl->mLights->mLightsSpot.end(),
                           [light](const puLightSpot &l) {
                             return light == l.get();
                           });
  mImpl->mLights->mLightsSpot.erase(new_end, mImpl->mLights->mLightsSpot.end());
}

void Engine::clearLight(LightDirectional *light) {
  auto new_end = remove_if(mImpl->mLights->mLightsDirectional.begin(),
                           mImpl->mLights->mLightsDirectional.end(),
                           [light](const puLightDirectional &l) {
                             return light == l.get();
                           });
  mImpl->mLights->mLightsDirectional.erase(new_end, mImpl->mLights->mLightsDirectional.end());
}

void Engine::clearLight(LightPoint *light) {
  auto new_end = remove_if(mImpl->mLights->mLightsPoint.begin(),
                           mImpl->mLights->mLightsPoint.end(),
                           [light](const puLightPoint &l) {
                             return light == l.get();
                           });
  mImpl->mLights->mLightsPoint.erase(new_end, mImpl->mLights->mLightsPoint.end());
}

void Engine::clearLights() {
  mImpl->mLights->clear();
}

glm::ivec2 Engine::getScreenSize() const {
  return glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight);
}

GLfloat Engine::getScreenAspectRatio() const {
  return mImpl->mWindowAspectRatio;
}

void Engine::insertResizeScreen(GLuint width, GLuint height) {
  mImpl->insertResizeScreen(width, height);

  for (auto &it : mImpl->mTextManager) { //todo optimization update only VBO
    it->editAspectRatio(this);
  }
}

GLuint Engine::getFramesPassed() {
  GLuint result = mImpl->mFrameCounter;
  mImpl->mFrameCounter = 0;
  return result;
}

GLfloat Engine::getStartupAnimationTime() const {
  return mImpl->mStartupTimeLimit;
}

void Engine::setCurrentScene(puScene &&scene) {
  if (mImpl->mScene) {
    mImpl->mScene->onHide();
  }
  mImpl->mScene = move(scene);
  mImpl->mScene->onShow();
  mImpl->mScene->resetRenderer(getScreenSize().x, getScreenSize().y);
}

TGetter<Scene> Engine::getCurrentScene() const {
  return TGetter<Scene>(mImpl->mScene.get());
}

flf::LightSystem &Engine::getLightSystem() const {
  return *mImpl->mLights.get();
}

flf::TextureSystem &Engine::getTextureSystem() const {
  return *mImpl->mTextures.get();
}

puPhysicsMeshBuffer Engine::getPhysicalMeshBuffer(const string &shapePath) {
  PhysicsMeshBuffer *buffer = new PhysicsMeshBuffer();

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  const aiScene *scene = mImpl->mImporter.ReadFile((mImpl->mFileLoader.getRootPath() + shapePath).c_str(),
                                                   aiProcess_Triangulate | aiProcess_SortByPType |
                                                   aiProcess_CalcTangentSpace);
  if (scene) {
    for (GLuint i = 0; i < scene->mNumMeshes; ++i) {
      const aiMesh *shape = scene->mMeshes[i];
      buffer->mNumFaces = shape->mNumFaces;
      buffer->mVertices.reserve(shape->mNumVertices);
      buffer->mIndices.reserve(shape->mNumFaces * 3);
      for (GLuint j = 0; j < shape->mNumFaces; j++) {
        buffer->mIndices.push_back(shape->mFaces[j].mIndices[0]);
        buffer->mIndices.push_back(shape->mFaces[j].mIndices[1]);
        buffer->mIndices.push_back(shape->mFaces[j].mIndices[2]);
      }
      for (GLuint z = 0; z < shape->mNumVertices; z++) {
        glm::vec3 vertex(shape->mVertices[z].x, shape->mVertices[z].y, shape->mVertices[z].z);
        buffer->mVertices.push_back(vertex);
      }
      break;      //todo for now fillwave supports only one mesh here;
    }
  }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  return puPhysicsMeshBuffer(buffer);
}

void Engine::addPostProcess(const string &fragmentShaderPath, GLfloat lifeTime) {
  Program *program = mImpl->mProgramLoader.getQuadCustomFragmentShader(fragmentShaderPath);
  PostProcessingPass pass(program,
                          mImpl->mTextures->getDynamic(fragmentShaderPath,
                                                       program,
                                                       glm::ivec2(mImpl->mWindowWidth, mImpl->mWindowHeight)),
                          lifeTime);
  mImpl->mPostProcessingPasses.push_back(pass);
  fLogD("Post processing pass added: %s", fragmentShaderPath.c_str());
}

void Engine::configureFPSCounter(string fontName, glm::vec2 position, GLfloat size) {
  if (fontName.size() > 1) {
    mImpl->mFPSText = storeText("", fontName, position, size);

    /* Provide callback to refresh the FPS value */
    mImpl->mTextFPSCallback = new flf::FPSCallback(this, mImpl->mFPSText);
    registerCallback(unique_ptr<Callback>(mImpl->mTextFPSCallback));
    return;
  }
  mImpl->mFPSText.reset();
  unregisterCallback(mImpl->mTextFPSCallback);
}

void Engine::configureFileLogging(string fileName) {
  if (fileName.size() > 1) {
    fLogI("File %s will be cleaned and used for logging.", fileName.c_str());
    return;
  }
  fLogI("File logging disabled.");
}

void Engine::reload() {
  mImpl->reload();
}

void Engine::log() {
  fLogI("Fillwave engine");
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  fLogI("Renderer: %s\n", renderer);
  fLogI("OpenGL version supported %s\n", version);
}

void Engine::pick(GLuint x, GLuint y) {
  mImpl->pick(x, y);
}

void Engine::captureFramebufferToFile(const string &name) {
  mImpl->captureFramebufferToFile(name);
}

void Engine::captureFramebufferToBuffer(GLubyte *buffer, GLint *sizeInBytes, GLuint format, GLint bytesPerPixel) {
  mImpl->mPickingRenderableTexture->bindForRendering();
  mImpl->drawClear();
  mImpl->mScene->draw();
  mImpl->mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mImpl->mWindowWidth, mImpl->mWindowHeight, format, GL_UNSIGNED_BYTE, 0);
  fLogC("reading pixel buffer failed");
#ifdef FILLWAVE_GLES_3_0
  buffer = (GLubyte*)mImpl->mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  buffer = (GLubyte *) mImpl->mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
  *sizeInBytes = mImpl->mWindowWidth * mImpl->mWindowHeight * bytesPerPixel;
  buffer[*sizeInBytes] = '\0';
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

const aiScene *Engine::getModelFromFile(string path) {
  fLogD("Reading model %s", path.c_str());
  return mImpl->mImporter.ReadFile((mImpl->mFileLoader.getRootPath() + path).c_str(),
                                   aiProcess_Triangulate | aiProcess_SortByPType | aiProcess_CalcTangentSpace);
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

template <GLuint T>
Shader *Engine::storeShader(const string &shaderPath) {
  string shaderSource = "";
  const string fullPath = mImpl->mFileLoader.getRootPath() + shaderPath;
  ReadFile(fullPath, shaderSource);
  return mImpl->mShaders.store(fullPath, T, shaderSource);
}

template <GLuint T>
Shader *Engine::storeShader(const string &shaderPath, const string &shaderSource) {
  const string fullPath = mImpl->mFileLoader.getRootPath() + shaderPath;
  return mImpl->mShaders.store(fullPath, T, shaderSource);
}

template Shader *Engine::storeShader<GL_VERTEX_SHADER>(const string &);

template Shader *Engine::storeShader<GL_FRAGMENT_SHADER>(const string &);

template Shader *Engine::storeShader<GL_VERTEX_SHADER>(const string &, const string &);

template Shader *Engine::storeShader<GL_FRAGMENT_SHADER>(const string &, const string &);

#ifdef FILLWAVE_GLES_3_0
#else

template Shader *Engine::storeShader<GL_TESS_CONTROL_SHADER>(const string &);

template Shader *Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const string &);

template Shader *Engine::storeShader<GL_GEOMETRY_SHADER>(const string &);

template Shader *Engine::storeShader<GL_TESS_CONTROL_SHADER>(const string &, const string &);

template Shader *Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const string &, const string &);

template Shader *Engine::storeShader<GL_GEOMETRY_SHADER>(const string &, const string &);

#endif

void Engine::configureDebugger(eDebuggerState state) {
  mImpl->mDebugger->setState(state);
}

VertexBufferBasic *Engine::storeBufferInternal(VertexArray *vao,
    flf::TerrainConstructor *constructor,
    GLint density,
    GLfloat gap,
    vector<GLuint> &indices) {
  return mImpl->mBuffers.mVertices.store(vao, constructor, density, gap, indices);
}

VertexBufferBasic *Engine::storeBufferInternal(VertexArray *vao, vector<VertexBasic> &data) {
  return mImpl->mBuffers.mVertices.store(new VertexBufferBasic(data), vao);
}

IndexBuffer *Engine::storeBufferInternal(VertexArray *vao, const vector<GLuint> &data) {
  return mImpl->mBuffers.mIndices.store(new IndexBuffer(data), vao);
}

void Engine::removeBufferIndex(VertexArray *vao) {
  mImpl->mBuffers.mIndices.erase(vao);
}

VertexBufferText *
Engine::storeBufferInternal(VertexArray *vao, const vector<GLfloat> &data, const vector<GLfloat> &textureCoords) {
  return mImpl->mBuffers.mVerticesText.store(vao, data, textureCoords);
}

IndexBuffer *Engine::storeBufferInternal(VertexArray *vao, GLuint elements) {
  return mImpl->mBuffers.mIndices.store(new IndexBuffer(elements, true), vao);
}

VertexBufferParticlesGPU *
Engine::storeBuffersInternal(VertexArray *vao, size_t idx, vector<VertexParticleGPU> &particles) {
  auto ptr = new vector<VertexBufferParticlesGPU *>();
  auto buffers = mImpl->mBuffers.mVerticesParticlesGPU.store(ptr, vao);
  if (buffers->size() < idx) {
    return (*buffers)[idx];
  }
  fLogD("There is no buffer for requested index. Creating a new one.");
  buffers->push_back(new VertexBufferParticlesGPU(particles));
  return buffers->back();
}

VertexBufferParticles *Engine::storeBufferInternal(VertexArray *vao,
    vector<GLfloat> &velocities,
    vector<GLfloat> &positions,
    vector<GLfloat> &times) {
  return mImpl->mBuffers.mVerticesParticles.store(vao, velocities, positions, times);
}

VertexBufferDebug *Engine::storeBufferInternal(VertexArray *vao, GLfloat scale) {
  return mImpl->mBuffers.mVerticesDebugger.store(vao, scale);
}

VertexBufferFloat *Engine::storeBufferInternal(VertexArray *vao, vector<VertexFloat> &data) {
  return mImpl->mBuffers.mVerticesFloat.store(vao, data);
}

VertexBufferPosition *Engine::storeBufferInternal(VertexArray *vao, vector<VertexPosition> &data) {
  return mImpl->mBuffers.mVerticesPosition.store(vao, data);
}

void Engine::removeBufferBasic(VertexArray *vao) {
  mImpl->mBuffers.mVertices.erase(vao);
}

void Engine::removeBufferText(VertexArray *vao) {
  mImpl->mBuffers.mVerticesText.erase(vao);
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

IndexBuffer *Engine::storeBufferInternal(VertexArray *vao, const aiMesh *shape) {
  return mImpl->mBuffers.mIndices.store(new IndexBuffer(shape), vao);
}

VertexBufferBasic *Engine::storeBufferInternal(VertexArray *vao, const aiMesh *shape, flf::Animator *animator) {
  return mImpl->mBuffers.mVertices.store(new VertexBufferBasic(shape, animator), vao);
}

#else
flc::VertexBufferBasic* Engine::storeBufferInternal(flc::VertexArray* vao,
    tinyobj::shape_t& shape,
    tinyobj::attrib_t& attributes) {
  VertexBufferBasic* newData = new VertexBufferBasic(shape, attributes);
  return mImpl->mBuffers.mVertices.store(newData, vao);
}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

}
/* flw */
