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

/* Debug  */
#include <fillwave/Config.h>

/* Logs  */
#include <fillwave/Log.h>

/* Stdlib  */
#include <fstream>

/* Implementation  */
#include  <fillwave/models/animations/Conversion.h>

#include <fillwave/engine/Engine.h>

#include <fillwave/Core.h>
#include <fillwave/Debugger.h>
#include <fillwave/Framework.h>

/* Management */
#include <fillwave/management/CacheProgram.h>
#include <fillwave/management/Cachehader.h>
#include <fillwave/management/CacheSampler.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/management/TextureSystem.h>

#include <fillwave/actions/EventHandler.h>
#include <fillwave/common/Macros.h>

#include <fillwave/common/Strings.h>

#include <fillwave/loaders/FileLoader.h>
#include <fillwave/management/CacheBuffer.h>

FLOGINIT_DEFAULT()

using namespace flw::flc;
using namespace std;

namespace flw {

Engine::Engine(const std::string& runtimeBinaryFilePath)
  : mWindowWidth(1920)
  , mWindowHeight(1200)
  , mWindowAspectRatio(mWindowHeight / mWindowWidth)
  , mFileLoader(getFilePathOnly(runtimeBinaryFilePath.c_str()))
  , mProgramLoader(this)
  , mModelLoader()
  , mShaders()
  , mFrameCounter(0)
  , mTimeFactor(1.0)
  , mStartupTime(0.0f)
  , mIsOQ(GL_TRUE)
  , mBackgroundColor(0.1, 0.1, 0.1) {
  initExtensions();
  initContext();
  initManagement();
  initPipelines();
  initUniforms();
  initPickingBuffer();
  initOcclusionTest();
  initExtras();

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  initStartup(engine);
#endif
//   mFence = puFence(new flc::Fence());
}

void Engine::initExtensions() {
#ifdef GLEW_OK
  GLenum GlewInitResult;
  glewExperimental = GL_TRUE;

  GlewInitResult = glewInit();
  if (GL_NO_ERROR != glGetError()) {
    fLogE("glewInit returned INVALID_ENUM ... It may happen");
  }

  if (GLEW_OK != GlewInitResult) {
    fLogE("GLEW init failed. Error: ", GlewInitResult);
    exit(EXIT_FAILURE);
  } else {
    fLogD("OpenGL Version: ", glGetString(GL_VERSION));
  }
  GLint maxPatchVertices = 0;
  glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVertices);
  fLogD("Max supported patches for tesselation: ", maxPatchVertices);
  // suppress error if tesselation is not supported
  glGetError();

#endif /* GLEW_OK */
}

void Engine::initManagement() {
  mTextures = std::make_unique<flf::TextureSystem>(mFileLoader.getRootPath());
  mLights = std::make_unique<flf::LightSystem>();
}

void Engine::initPipelines() {
  /* OT */
  mProgramOcclusionBox = mProgramLoader.getProgram(flf::EProgram::occlusionOptimizedQuery);

  /* T */
  mProgramTextureLookup = mProgramLoader.getProgram(flf::EProgram::quad);
}

void Engine::initUniforms() {
  mProgramTextureLookup->use();
  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

void Engine::initOcclusionTest() {
  flf::vec<flc::VertexPosition> vec = flf::BoxOcclusion().getVertices();
  mVAOOcclusion = new flc::VertexArray();
  mVBOOcclusion = mBuffers.mVerticesPosition.store(mVAOOcclusion, vec);
  mVBOOcclusion->initAttributes(mProgramOcclusionBox->getHandle());
  mVAOOcclusion->bind();
  mVBOOcclusion->bind();
  mVBOOcclusion->attributesSetForVAO();
  mVBOOcclusion->send();
  flc::VertexArray::unbindVAO();
}

void Engine::initStartup() {

  auto program = mProgramLoader.getProgram(flf::EProgram::quadCustomFragmentShaderStartup);

  program->use();
  program->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  program->uniformPush("uScreenFactor", mWindowAspectRatio);
  flc::Program::disusePrograms();

  mPostProcessingPassStartup = std::make_unique<flc::PostProcessingPass>(program,
                                                                         mTextures->getDynamic("fillwave_quad_startup.frag",
                                                                                               program,
                                                                                               glm::ivec2(mWindowWidth,
                                                                                                          mWindowHeight)),
                                                                         mStartupTimeLimit);

  fLogD("Post processing startup pass added");

  mStartupTexture = mTextures->get("logo.png", flf::ECompression::none);
  if (mStartupTexture) {
    return;
  }

  mStartupTexture = mTextures->get("textures/logo.png", flf::ECompression::none);
  if (mStartupTexture) {
    return;
  }

  mStartupTexture = mTextures->get("64_64_64.color", flf::ECompression::none);
  fLogE("Fillwave startup logo could not be executed");
}

void Engine::initPickingBuffer() {
  mPickingPixelBuffer = std::make_unique<flc::PixelBuffer>(GL_STREAM_READ);
  reloadPickingBuffer();
}

void Engine::initExtras() {
  /* Debugger */
  mDebugger = std::make_unique<flf::Debugger>(this);

#ifdef FILLWAVE_COMPILATION_PC_GLES
#else
  /* Tesselation */
  glPatchParameteri(GL_PATCH_VERTICES, 3);
#endif // FILLWAVE_COMPILATION_PC_GLES

  /* Suppress error if setting patch up fails */
  glGetError();
}

void Engine::reload() {

  initContext();

  for (auto &it : mShaders) {
    it.second->reload();
  }

  for (auto &it : mPrograms) {
    it.second->reload();
  }

  mTextures->reload();

  for (auto &it : mSamplers) {
    it.second->reload();
  }

  for (auto &it : mBuffers.mVertexArrays) {
    it.second->reload();
  }

  mPickingPixelBuffer->reload();
  reloadPickingBuffer();
}

void Engine::reloadPickingBuffer() {
  mPickingRenderableTexture = mTextures->getColor2D(mWindowWidth, mWindowHeight);

  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);
  mPickingPixelBuffer->bind();
  mPickingPixelBuffer->setLoaded(GL_FALSE);
  mPickingPixelBuffer->send();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("glReadPixels");
  mPickingPixelBuffer->unbind();
}

void Engine::initContext(void) {
  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  fLogC("Could not set OpenGL depth testing options");
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  fLogC("Could not set OpenGL culling options");
}

Engine::~Engine() {
  if (mScene) {
    mScene.reset();
  }
  mTextManager.clear();
  mFontManager.clear();
  mPostProcessingPasses.clear();
}

void Engine::configBackgroundColor(glm::vec3 color) {
  mBackgroundColor = color;
}

void Engine::configTime(GLfloat timeFactor) {
  mTimeFactor = timeFactor;
}

flf::LightSpot* Engine::storeLightSpot(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable* observed) {
  return mLights->mLightsSpot.add(
      mTextures->getShadow2D(mWindowWidth, mWindowHeight), pos, rot, col, observed);
}

flf::LightPoint* Engine::storeLightPoint(glm::vec3 pos, glm::vec4 col, flf::Moveable* observed) {
  return mLights->mLightsPoint.add(
      mTextures->getShadow3D(mWindowWidth, mWindowHeight), pos, col, observed);
}

flf::LightDirectional*
Engine::storeLightDirectional(glm::vec3 pos, glm::quat rot, glm::vec4 col, flf::Moveable* observed) {
  return mLights->mLightsDirectional.add(
      mTextures->getShadow2D(mWindowWidth, mWindowHeight), pos, rot, col, observed);
}

Program* Engine::storeProgram(const string& name, const vector<Shader*>& shaders, bool isSkipLinking) {
  return mPrograms.store(name, shaders, isSkipLinking);
}

Texture2D* Engine::storeTexture(const string& texturePath, flf::ECompression compression) {
  return mTextures->get(texturePath, compression);
}

Texture2DRenderable* Engine::storeTextureRenderable() {
  return mTextures->getColor2D(mWindowWidth, mWindowHeight);
}

Texture2DRenderableDynamic* Engine::storeTextureDynamic(const string& fragmentShaderPath) {
  const string path = fragmentShaderPath;
  Program* program = mProgramLoader.getQuadCustomFragmentShader(fragmentShaderPath);
  return mTextures->getDynamic(path, program, glm::ivec2(mWindowWidth, mWindowHeight));;
}

Texture3D* Engine::storeTexture3D(
  const string& posX
  , const string& negX
  , const string& posY
  , const string& negY
  , const string& posZ
  , const string& negZ) {
  return mTextures->get(posX, negX, posY, negY, posZ, negZ);
}

Sampler* Engine::storeSO(GLint textureUnit) {
  return mSamplers.store(textureUnit, textureUnit);
}

VertexArray* Engine::storeVAO(flf::IReloadable* user, VertexArray* vao) {
  return vao ? mBuffers.mVertexArrays.store(vao, user) : mBuffers.mVertexArrays.store(user);
}

/* Detach */
void Engine::detach(flf::Entity* entity) {
  if (mScene) {
    mScene->detach(entity);
  }
  mScene->resetRenderer(getScreenSize().x, getScreenSize().y);
}

ps<flf::Text> Engine::storeText(const string& content,
    const string& fontName,
    glm::vec2 position,
    GLfloat scale,
    glm::vec4 color,
    ETextEffect effect) {
  /* Check for the font texture  */
  if (!mTextures->get(fontName + ".png")) {
    mFontLoader.load(mFileLoader.getRootPath() + fontName);
  }
  auto t = mTextures->get(fontName + ".png", flf::ECompression::none, flf::EFlip::vertical);

  Font* font = nullptr;
  for (auto &it : mFontManager) {
    if (it->mName == fontName) {
      font = it.get();
    }
  }

  if (!font) {
    ifstream myfile(mFileLoader.getRootPath(fontName + ".meta"));
    if (!myfile.is_open()) {
      fLogE("No text added. Could not write to metadata file: %s", (fontName + ".meta").c_str());
      return ps<flf::Text>();
    }
    string line;
    string ASCII, xMin, width, yMin, height, yOffset;
    GLfloat fXMin, fWidth, fYMin, fHeight, fYOffset;
    GLint iASCII;
    Font* newFont = new Font();
    GLint control = 0;
    while (!myfile.eof()) {
      getline(myfile, line);
      myfile >> iASCII >> fXMin >> fWidth >> fYMin >> fHeight >> fYOffset;
      newFont->mWidths[iASCII] = fWidth;
      newFont->mOffsets[iASCII] = 1.0f - fHeight - fYOffset;
      if (control++ > FILLWAVE_MAX_TEXTS) {
        fLogE("Metadata can not be read for file %s.", (fontName + ".meta").c_str());
        myfile.close();
        delete newFont;
        return ps<flf::Text>();
      }
    }
    myfile.close();
    mFontManager.push_back(ps<Font>(newFont));
    font = newFont;
  }

  ps<flf::Text> text = make_shared<flf::Text>(content, t, position, this, scale, font, color, effect);
  mTextManager.push_back(ps<flf::Text>(text));
  return text;
}

void Engine::detach(ps<flf::Text> text) {
  auto _compare_function = [text](ps<flf::Text> t) -> bool {
    return (t == text);
  };
  auto _begin = mTextManager.begin();
  auto _end = mTextManager.end();
  auto it = remove_if(_begin, _end, _compare_function);
  mTextManager.erase(it, _end);
}

void Engine::detach(flf::LightSpot* light) {
  auto new_end = remove_if(mLights->mLightsSpot.begin(),
                           mLights->mLightsSpot.end(),
                           [light](const pu<flf::LightSpot> &l) {
                             return light == l.get();
                           });
  mLights->mLightsSpot.erase(new_end, mLights->mLightsSpot.end());
}

void Engine::detach(flf::LightDirectional* light) {
  auto new_end = remove_if(mLights->mLightsDirectional.begin(),
                           mLights->mLightsDirectional.end(),
                           [light](const pu<flf::LightDirectional> &l) {
                             return light == l.get();
                           });
  mLights->mLightsDirectional.erase(new_end, mLights->mLightsDirectional.end());
}

void Engine::detach(flf::LightPoint* light) {
  auto new_end = remove_if(mLights->mLightsPoint.begin(),
                           mLights->mLightsPoint.end(),
                           [light](const pu<flf::LightPoint> &l) {
                             return light == l.get();
                           });
  mLights->mLightsPoint.erase(new_end, mLights->mLightsPoint.end());
}

void Engine::detachLights() {
  mLights->clear();
}

glm::ivec2 Engine::getScreenSize() const {
  return glm::ivec2(mWindowWidth, mWindowHeight);
}

GLfloat Engine::getScreenAspectRatio() const {
  return mWindowAspectRatio;
}

GLuint Engine::getFramesPassed() {
  GLuint result = mFrameCounter;
  mFrameCounter = 0;
  return result;
}

GLfloat Engine::getStartupAnimationTime() const {
  return mStartupTimeLimit;
}

void Engine::setCurrentScene(pu<flf::Scene> &&scene) {
  if (mScene) {
    mScene->onHide();
  }
  mScene = move(scene);
  mScene->onShow();
  mScene->resetRenderer(getScreenSize().x, getScreenSize().y);
}

pp<flf::Scene> Engine::getCurrentScene() const {
  return pp<flf::Scene>(mScene.get());
}

flf::LightSystem &Engine::getLightSystem() const {
  return* mLights.get();
}

flf::TextureSystem &Engine::getTextureSystem() const {
  return* mTextures.get();
}

void Engine::getPhysicalMeshBuffer(const string& shapePath, flf::PhysicsMeshBuffer& buffer) {
  mModelLoader.getPhysicsBuffer((mFileLoader.getRootPath() + shapePath).c_str(), buffer);
}

void Engine::addPostProcess(const string& fragmentShaderPath, GLfloat lifeTime) {
  Program* program = mProgramLoader.getQuadCustomFragmentShader(fragmentShaderPath);
  PostProcessingPass pass(program,
                          mTextures->getDynamic(fragmentShaderPath,
                                                       program,
                                                       glm::ivec2(mWindowWidth, mWindowHeight)),
                          lifeTime);
  mPostProcessingPasses.push_back(pass);
  fLogD("Post processing pass added: %s", fragmentShaderPath.c_str());
}

void Engine::configFPSCounter(string fontName, glm::vec2 position, GLfloat size) {
  if (fontName.size() > 1) {
    mFPSText = storeText("", fontName, position, size);
    //mTextFPSCallback.set(mFPSText);
    return;
  }
  mFPSText.reset();
  //detachCallback(mTextFPSCallback);
}

void Engine::configFileLogging(string fileName) {
  if (fileName.size() > 1) {
    fLogI("File %s will be cleaned and used for logging.", fileName.c_str());
    return;
  }
  fLogI("File logging disabled.");
}

void Engine::log() {
  fLogI("Fillwave engine");
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  fLogI("Renderer: %s\n", renderer);
  fLogI("OpenGL version supported %s\n", version);
}

void Engine::captureFramebufferToBuffer(GLubyte* buffer, GLint* sizeInBytes, GLuint format, GLint bytesPerPixel) {
  mPickingRenderableTexture->bindForRendering();
  drawClear();
  mScene->draw();
  mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, format, GL_UNSIGNED_BYTE, 0);
  fLogC("reading pixel buffer failed");
#ifdef FILLWAVE_GLES_3_0
  buffer = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  buffer = (GLubyte* ) mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
 * sizeInBytes = mWindowWidth*  mWindowHeight*  bytesPerPixel;
  buffer[*sizeInBytes] = '\0';
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

const ModelLoader::Scene* Engine::getModelFromFile(const string& path) {
  fLogD("Reading model ", path);
  return mModelLoader.mImporter->ReadFile((mFileLoader.getRootPath() + path).c_str(), mModelLoader.mFlags);
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP  */

template <GLuint T>
Shader* Engine::storeShader(const string& shaderPath) {
  string shaderSource = "";
  const string fullPath = mFileLoader.getRootPath() + shaderPath;
  flf::ReadFile(fullPath, shaderSource);
  return mShaders.store(fullPath, T, shaderSource);
}

template <GLuint T>
Shader* Engine::storeShader(const string& shaderPath, const string& shaderSource) {
  return mShaders.store(mFileLoader.getRootPath() + shaderPath, T, shaderSource);
}

void Engine::configDebugger(EDebuggerState state) {
  mDebugger->setState(state);
}

VertexBufferBasic* Engine::storeBufferInternal(VertexArray* vao,
    flf::TerrainConstructor* constructor,
    GLint density,
    GLfloat gap,
    vector<GLuint> &indices) {
  return mBuffers.mVertices.store(vao, constructor, density, gap, indices);
}

VertexBufferBasic* Engine::storeBufferInternal(VertexArray* vao, vector<VertexBasic> &data) {
  return mBuffers.mVertices.store(new VertexBufferBasic(data), vao);
}

IndexBuffer* Engine::storeBufferInternal(VertexArray* vao, const vector<GLuint> &data) {
  return mBuffers.mIndices.store(new IndexBuffer(data), vao);
}

void Engine::removeBufferIndex(VertexArray* vao) {
  mBuffers.mIndices.erase(vao);
}

VertexBufferText* 
Engine::storeBufferInternal(VertexArray* vao, const vector<GLfloat> &data, const vector<GLfloat> &textureCoords) {
  return mBuffers.mVerticesText.store(vao, data, textureCoords);
}

IndexBuffer* Engine::storeBufferInternal(VertexArray* vao, GLuint elements) {
  return mBuffers.mIndices.store(new IndexBuffer(elements, true), vao);
}

VertexBufferParticlesGPU* 
Engine::storeBuffersInternal(VertexArray* vao, size_t idx, vector<VertexParticleGPU> &particles) {
  auto ptr = new vector<VertexBufferParticlesGPU* >();
  auto buffers = mBuffers.mVerticesParticlesGPU.store(ptr, vao);
  if (buffers->size() < idx) {
    return (*buffers)[idx];
  }
  fLogD("There is no buffer for requested index. Creating a new one.");
  buffers->push_back(new VertexBufferParticlesGPU(particles));
  return buffers->back();
}

VertexBufferParticles* Engine::storeBufferInternal(VertexArray* vao,
    vector<GLfloat> &velocities,
    vector<GLfloat> &positions,
    vector<GLfloat> &times) {
  return mBuffers.mVerticesParticles.store(vao, velocities, positions, times);
}

VertexBufferDebug* Engine::storeBufferInternal(VertexArray* vao, GLfloat scale) {
  return mBuffers.mVerticesDebugger.store(vao, scale);
}

VertexBufferFloat* Engine::storeBufferInternal(VertexArray* vao, vector<VertexFloat> &data) {
  return mBuffers.mVerticesFloat.store(vao, data);
}

VertexBufferPosition* Engine::storeBufferInternal(VertexArray* vao, vector<VertexPosition> &data) {
  return mBuffers.mVerticesPosition.store(vao, data);
}

void Engine::removeBufferBasic(VertexArray* vao) {
  mBuffers.mVertices.erase(vao);
}

void Engine::removeBufferText(VertexArray* vao) {
  mBuffers.mVerticesText.erase(vao);
}

IndexBuffer* Engine::storeBufferInternal(VertexArray* vao, const ModelLoader::ShapeType* shape) {
  return mBuffers.mIndices.store(ModelLoader::getIndexBuffer(shape), vao);
}

VertexBufferBasic* Engine::storeBufferInternal(
  VertexArray* vao
  , const ModelLoader::ShapeType* shape
  , const ModelLoader::ShapeDataType* data
  , flf::Animator* animator) {
  return mBuffers.mVertices.store(ModelLoader::getVertexBuffer(shape, data, animator), vao);
}

void Engine::draw(GLfloat time) {
#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  if (mScene) {
    /* count this frame */
    mFrameCounter++;

    /* Clear main framebuffer */
    glClearDepth(1.0f);

    /* Calculate dynamic textures */
    mTextures->evaluateDynamicTextures(time);

    /* Lights evaluation */
    glDepthMask(GL_TRUE);
    evaluateShadowMaps();
    drawScene(time);
    drawFront();
  }
}

void Engine::drawFront() {
  drawHUD();
  evaluateDebugger();
  mScene->drawCursor();
  mScene->updateDependencies();
  mScene->updateRenderer();
}

#ifdef FILLWAVE_GLES_3_0
#else

void Engine::drawLines(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  /* count this frame */
  mFrameCounter++;

  /* clear main framebuffer */
  glClearDepth(1.0f);

  /* Calculate dynamic textures */
  mTextures->evaluateDynamicTextures(time);

  /* Lights evaluation */
  if (mScene) {
    evaluateShadowMaps();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawScene(time);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawFront();
  }
}

void Engine::drawPoints(GLfloat time) {

#ifdef FILLWAVE_COMPILATION_STARTUP_ANIMATION
  /* Draw startup animation */
  if (mStartupTime < mStartupTimeLimit) {
    evaluateStartupAnimation(time);
    mStartupTime += time;
    return;
  }
#endif

  /* count this frame */
  mFrameCounter++;

  /* clear main framebuffer */
  glClearDepth(1.0f);

  /* Calculate dynamic textures */
  mTextures->evaluateDynamicTextures(time);

  /* Lights evaluation */
  if (mScene) {
    evaluateShadowMaps();
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    drawScene(time);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawFront();
  }
}

#endif

void Engine::drawHUD() {
  if (mScene) {
    mScene->drawHUD();
  }
  for (auto &it : mTextManager) {
    it->draw();
  }
}

void Engine::drawTexture(flc::Texture *t, flc::Program *p) {
  p->use();
  t->bind(FILLWAVE_DIFFUSE_UNIT);
  p->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  t->unbind();
  flc::Program::disusePrograms();
}

void Engine::drawTexture(flc::Texture *t) {
  mProgramTextureLookup->use();
  mProgramTextureLookup->uniformPush("uPostProcessingSampler", FILLWAVE_DIFFUSE_UNIT);
  t->bind(FILLWAVE_DIFFUSE_UNIT);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  t->unbind();
}

void Engine::drawClear() {
  glClearColor(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::drawScene(GLfloat time) {

  evaluateTime(time);

  if (mPostProcessingPasses.size()) {
    auto _compare_function = [](flc::PostProcessingPass &pass) -> bool {
      return pass.isFinished();
    };
    auto _begin = mPostProcessingPasses.begin();
    auto _end = mPostProcessingPasses.end();

    flc::Texture2DRenderableDynamic* textureNext;
    flc::Texture2DRenderableDynamic* textureCurrent = (*_begin).getFrame();

    flc::Program* programCurrent;

    drawClear();
    textureCurrent->bindForWriting();
    drawSceneCore();

    for (auto it = _begin; it != _end; it++) {

      auto next = it + 1;

      if (next != _end) {

        textureNext = (*next).getFrame();
        textureCurrent = (*it).getFrame();
        programCurrent = (*it).getProgram();

        textureNext->bindForWriting();

        drawClear();

        textureCurrent->draw(0.0f);

        textureNext->draw(time);

        textureNext->bindForReading();

      } else {

        flc::Framebuffer::bindScreenFramebuffer();

        // render to current bound framebuffer using textureCurrent as a texture to post process
        textureCurrent->draw(time);

        textureCurrent = (*it).getFrame();
        programCurrent = (*it).getProgram();

        // render to current bound framebuffer using textureCurrent as a texture to post process
        drawTexture(textureCurrent, programCurrent);
      }

      (*it).checkTime(time);
    }

    auto it = remove_if(_begin, _end, _compare_function);

    mPostProcessingPasses.erase(it, _end);

  } else {
    drawSceneCore();
  }
}

void Engine::drawSceneCore() {
  if (mIsOQ) {
    drawOcclusionPass();
  }
  drawClear();
  mScene->draw();
}

void Engine::drawOcclusionPass() {
  mVAOOcclusion->bind();

  glDisable(GL_CULL_FACE);
  glDepthMask(GL_FALSE);
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

  mScene->drawOcclusion();

  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  flc::VertexArray::unbindVAO();
}

void Engine::evaluateStartupAnimation(GLfloat time) {

  drawClear();

  flc::Texture2DRenderableDynamic *t = mPostProcessingPassStartup->getFrame();

  t->bindForWriting();

  drawTexture(mStartupTexture);

  flc::Framebuffer::bindScreenFramebuffer();

  t->draw(time);

  drawTexture(t, mPostProcessingPassStartup->getProgram());

  mPostProcessingPassStartup->checkTime(time);
}

void Engine::evaluateShadowMaps() {

  glDepthMask(GL_TRUE);

  mLights->updateLightEntities();

  GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;

  flc::Texture2DRenderable *light2DTexture;
  for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
    light2DTexture = mLights->mLightsSpot[i]->getShadowTexture();
    light2DTexture->bindForWriting();
    light2DTexture->bind(currentTextureUnit++);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    mScene->drawDepth(*(mLights->mLightsSpot[i]->getShadowCamera()));
  }

  for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
    light2DTexture = mLights->mLightsDirectional[i]->getShadowTexture();
    light2DTexture->bindForWriting();
    light2DTexture->bind(currentTextureUnit++);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    mScene->drawDepth(*(mLights->mLightsDirectional[i]->getShadowCamera()));
  }

  for (size_t i = 0; i < mLights->mLightsPoint.size(); i++) {
    flf::LightPoint *lightPoint = mLights->mLightsPoint[i].get();
    flc::Texture3DRenderable *light3DTexture = lightPoint->getShadowTexture();
    glm::vec3 lightPosition(lightPoint->getTranslation());
    light3DTexture->bindForWriting();
    light3DTexture->bind(currentTextureUnit);
    for (GLint j = GL_TEXTURE_CUBE_MAP_POSITIVE_X; j <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; j++) {
      light3DTexture->setAttachmentFace(j, GL_COLOR_ATTACHMENT0);
      glClearColor(0.0, 0.0, 0.0, 1.0);
      glClear(GL_DEPTH_BUFFER_BIT);
      mScene->drawDepthColor(*(lightPoint->getShadowCamera(j)), lightPosition);
    }
    currentTextureUnit++;
  }
  flc::Framebuffer::bindScreenFramebuffer();
}

void Engine::evaluateTime(GLfloat timeExpiredInSeconds) {
  if (mTimeFactor) {
    flf::EventData data;
    data.mTime = {
      timeExpiredInSeconds
    };

    mScene->onEvent(flf::Event(flf::EEventType::time, data));
    mScene->stepInTime(timeExpiredInSeconds);
  }
}

void Engine::evaluateDebugger() {
  GLint mCurentTextureUnit = 0;
  GLint id = 0;
  switch (mDebugger->getState()) {
    case EDebuggerState::lightsSpot:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsSpotDepth:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderDepthPerspective(mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderDepthOrthographic(mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsSpotColor:
      mCurentTextureUnit = 0;
      for (size_t i = 0; i < mLights->mLightsSpot.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsSpot[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      for (size_t i = 0; i < mLights->mLightsDirectional.size(); i++) {
        mDebugger->renderFromCamera(*(mLights->mLightsDirectional[i]->getShadowCamera()), mCurentTextureUnit++);
      }
      break;
    case EDebuggerState::lightsPoint:
      break;
    case EDebuggerState::lightsPointDepth: // only light 0
      break;
    case EDebuggerState::lightsPointColor:
      for (size_t j = 0; j < mLights->mLightsPoint.size(); j++) {
        for (int i = GL_TEXTURE_CUBE_MAP_POSITIVE_X; i <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; i++) {
          flf::CameraPerspective cameraPF = *(mLights->mLightsPoint[j]->getShadowCamera(i));
          mDebugger->renderFromCamera(cameraPF, id++);
        }
      }
      break;
    case EDebuggerState::pickingMap:
      mDebugger->renderPickingMap();
      break;
    case EDebuggerState::off:
    case EDebuggerState::toggleState:
      break;
  }
}

void Engine::onResizeScreen(GLuint width, GLuint height) {
  mWindowWidth = width;
  mWindowHeight = height;
  mWindowAspectRatio = static_cast<GLfloat>(mWindowHeight) / static_cast<GLfloat>
  (mWindowWidth);

  glViewport(0, 0, mWindowWidth, mWindowHeight);

  mTextures->resize(mWindowWidth, mWindowHeight);
  mPickingPixelBuffer->setScreenSize(mWindowWidth, mWindowHeight, 4);

  for (auto &it : mTextManager) { //todo optimization update only VBO
    it->editAspectRatio(this);
  }
}

void Engine::onEvent(const flf::Event& event) const {
  for (const auto& handler : mHandlers) {
    handler.handle(event);
  }
  mScene->onEvent(event);
}

void Engine::attachHandler(std::function<void(const flf::Event&)>&& handler, flf::EEventType type) {
  mHandlers.emplace_back(type, std::move(handler));
}

void Engine::detachHandlers() {
  mHandlers.clear();
}

glm::ivec4 Engine::pickingBufferGetColor(GLubyte *data, GLuint x, GLuint y) {
  y = mWindowHeight - y;
  GLuint id = 0;
  GLuint r = 0;
  GLuint g = 0;
  GLuint b = 0;
  GLuint a = 0;

  if (x < mWindowWidth && y < mWindowHeight) {
    id = (x + y * mWindowWidth) * 4;
    b = data[id];
    g = data[id + 1];
    r = data[id + 2];
    a = data[id + 3];
  }
  return glm::ivec4(r, g, b, a);
}

void Engine::pick(GLuint x, GLuint y) {
  mPickingRenderableTexture->bindForRendering();
  drawClear();
  mScene->drawPicking();
  mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("glReadPixels failed");
#ifdef FILLWAVE_GLES_3_0
  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
#endif

  glm::ivec4 colorRead = pickingBufferGetColor(data, x, y);
  mPickingPixelBuffer->unmap();
  mPickingPixelBuffer->unbind();
  flc::Framebuffer::bindScreenFramebuffer();
  mScene->draw();
  mScene->pick(colorRead);
}

void Engine::captureFramebufferToFile(const std::string &name) {
  mPickingRenderableTexture->bindForRendering();
  drawClear();
  mScene->draw();
  mPickingPixelBuffer->bind();
  glReadPixels(0, 0, mWindowWidth, mWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  fLogC("reading pixel buffer failed");
#ifdef FILLWAVE_GLES_3_0
  GLubyte* data = (GLubyte*)mPickingPixelBuffer->mapRange(GL_MAP_READ_BIT);
#else
  GLubyte *data = (GLubyte *) mPickingPixelBuffer->map(GL_READ_WRITE);
#endif
  data[mWindowWidth * mWindowHeight * 4] = '\0';
  FILE *file;
  auto errorNo = fopen_s(&file, mFileLoader.getRootPath(name).c_str(), "w");
  if (errorNo) {
    fLogE("Error when takin' screenshot");
    exit(1);
  }
  for (GLuint i = 0; i < mWindowWidth * mWindowHeight; i++) {
    fprintf(file, "%c", data[4 * i]);
    fprintf(file, "%c", data[4 * i + 1]);
    fprintf(file, "%c", data[4 * i + 2]);
    fprintf(file, "%c", data[4 * i] + 3);
  }
  fclose(file);
  mPickingPixelBuffer->unmap();
  mPickingPixelBuffer->unbind();
  flc::Framebuffer::bindScreenFramebuffer();
  mScene->draw();
}

template Shader* Engine::storeShader<GL_VERTEX_SHADER>(const string& );

template Shader* Engine::storeShader<GL_FRAGMENT_SHADER>(const string& );

template Shader* Engine::storeShader<GL_VERTEX_SHADER>(const string& , const string& );

template Shader* Engine::storeShader<GL_FRAGMENT_SHADER>(const string& , const string& );

#ifdef FILLWAVE_GLES_3_0
#else

template Shader* Engine::storeShader<GL_TESS_CONTROL_SHADER>(const string& );

template Shader* Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const string& );

template Shader* Engine::storeShader<GL_GEOMETRY_SHADER>(const string& );

template Shader* Engine::storeShader<GL_TESS_CONTROL_SHADER>(const string& , const string& );

template Shader* Engine::storeShader<GL_TESS_EVALUATION_SHADER>(const string& , const string& );

template Shader* Engine::storeShader<GL_GEOMETRY_SHADER>(const string& , const string& );

#endif

}
/* flw  */
