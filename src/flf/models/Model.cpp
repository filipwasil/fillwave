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

#include <flw/flf/models/Model.h>
#include <flw/flf/models/Hinge.h>

#include <flw/flf/management/LightSystem.h>

#include <flw/Fillwave.h>

#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

Model::Model(Engine* engine,
  flc::Program* program,
  const Shape<flc::VertexBasic>& shape,
  flc::Texture2D* diffuseMap,
  flc::Texture2D* normalMap,
  flc::Texture2D* specularMap,
  const Material& material)
  : Programmable(program)
  , mEngine(engine)
  , mProgramLoader(engine)
  , mAnimator(nullptr)
  , mLights(mEngine->getLightSystem()) {

  std::vector<flc::VertexBasic> vertices = shape.getVertices();
  std::vector<GLuint> indices = shape.getIndices();

  initShadowing();
  initUniformsCache();

  auto* vao = new flc::VertexArray();
  attach(std::make_unique<Mesh>(
    mEngine
    , material
    , diffuseMap
    , normalMap
    , specularMap
    , mProgram
    , mProgramShadow
    , mProgramShadowColor
    , mProgramLoader.getProgram(EProgram::occlusionOptimizedQuery)
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
    , nullptr
#else
    , mProgramLoader.getProgram(EProgram::ambientOcclusionGeometry)
#endif
    , mProgramLoader.getProgram(EProgram::ambientOcclusionColor)
    , mEngine->getLightSystem()
    , vao
    , false
    , mEngine->storeBuffer<flc::VertexBufferBasic>(vao, vertices)
    , engine->storeBuffer<flc::IndexBuffer>(vao, indices)
    , mAnimator.get()
    , GL_TRIANGLES)
  );
}

Model::Model(
  Engine* engine
  , flc::Program* program
  , const std::string& shapePath)
  : Programmable(program)
  , mEngine(engine)
  , mProgramLoader(engine)
  , mAnimator(nullptr)
  , mLights(engine->getLightSystem()) {
  reloadModel(shapePath);
}

Model::Model(Engine* engine
             , flc::Program* program
             , const std::string& shapePath
             , const std::string& diffuseMapPath
             , const std::string& normalMapPath
             , const std::string& specularMapPath)
  : Programmable(program)
  , mEngine(engine)
  , mProgramLoader(engine)
  , mAnimator(nullptr)
  , mLights(engine->getLightSystem()) {

  reloadModel(shapePath
    , mEngine->storeTexture(diffuseMapPath.c_str())
    , mEngine->storeTexture(normalMapPath.c_str())
    , mEngine->storeTexture(specularMapPath.c_str()));
}

Model::Model(Engine* engine
             , flc::Program* program
             , const std::string& shapePath
             , flc::Texture2D* diffuseMap
             , flc::Texture2D* normalMap
             , flc::Texture2D* specularMap
             , const Material& material)
  : Programmable(program)
  , mEngine(engine)
  , mProgramLoader(engine)
  , mAnimator(nullptr)
  , mLights(engine->getLightSystem()) {

  reloadModel(shapePath
    , diffuseMap
    , normalMap
    , specularMap
    , material);
}

Model::~Model() {
  // nothing
}

void Model::reloadModel(const std::string& localPath) {
  const auto scene = ModelLoader::SceneType(mEngine->getGlobalPath(localPath));
  initAnimations(scene);
  initShadowing();
  initUniformsCache();
  loadNodes(ModelLoader::getRootNode(scene), scene, this);
}

void Model::reloadModel(
  const std::string& localPath
  , flc::Texture2D* diff
  , flc::Texture2D* norm
  , flc::Texture2D* specular
  , const Material& material) {
  unloadNodes();
  const auto scene = ModelLoader::SceneType(mEngine->getGlobalPath(localPath));
  initAnimations(scene);
  initShadowing();
  initUniformsCache();
  loadNodes(ModelLoader::getRootNode(scene), scene, this, diff, norm, specular, material);
}

inline void Model::initAnimations(const ModelLoader::SceneType& scene) {
  mAnimator = std::unique_ptr<ModelLoader::Animator>(ModelLoader::getAnimator(scene));
  if (mAnimator) {
    fLogD("attached TimedBoneUpdateCallback to model");
    this->attachHandler(
      [this](const Event& event){
        this->performAnimation(event.getData().mTime.timePassed);
      }, EEventType::time);
  }
}

inline void Model::unloadNodes() {
  for (auto mesh : mMeshes) {
    detach(mesh);
  }
  mMeshes.clear();
}

inline void Model::loadNodes(const ModelLoader::NodeType* node, const ModelLoader::SceneType& scene, Entity* entity) {

  /* Set this node transformations */
  ModelLoader::setTransformation(node, entity);
  auto meshes = ModelLoader::getMeshes(node, scene);
  for (auto& meshCreationInfo : meshes) {
    entity->attach(
      loadMesh(
        meshCreationInfo.shape
        , meshCreationInfo.material
        , mEngine->storeTexture(meshCreationInfo.diffuse)
        , mEngine->storeTexture(meshCreationInfo.normal)
        , mEngine->storeTexture(meshCreationInfo.specular)
        , mEngine
      )
    );
  }

  /* Evaluate children */
  auto children = ModelLoader::getChildren(node);

  for (auto* child : children) {
    pu<Entity> newEntity = std::make_unique<flf::Hinge>();
    loadNodes(child, scene, newEntity.get());
    entity->attach(std::move(newEntity));
  }
}

void Model::loadNodes (
  const ModelLoader::NodeType* node
  , const ModelLoader::SceneType& scene
  , Entity* entity
  , flc::Texture2D* diffuseMap
  , flc::Texture2D* normalMap
  , flc::Texture2D* specularMap
  , const Material& material) {

  ModelLoader::setTransformation(node, entity);
  auto meshes = ModelLoader::getMeshes(node, scene);
  for (auto & meshCreationInfo : meshes) {
    entity->attach(loadMesh(
      meshCreationInfo.shape
      , material
      , diffuseMap
      , normalMap
      , specularMap
      , mEngine));
  }

  /* Evaluate children */
  auto children = ModelLoader::getChildren(node);

  for (auto* child : children) {
    pu<Entity> newEntity = std::make_unique<flf::Hinge>();
    loadNodes(child, scene, newEntity.get(), diffuseMap, normalMap, specularMap, material);
    entity->attach(std::move(newEntity));
  }
}

pn<Mesh> Model::getMesh(size_t id) {
  if (id < mMeshes.size()) {
    return make_pu_with_no_ownership<Mesh> (mMeshes.at(id));
  }
  fLogF("Requested mesh does not exist. Id requested: ", static_cast<int>(id));
  return make_pu_with_no_ownership<Mesh>(nullptr);
}

void Model::performAnimation(GLfloat timeElapsedInSeconds) {
  if (nullptr == mAnimator) {
    fLogE("This model is not animated. Active animation not set.");
    return;
  }
  mAnimator->performAnimation(timeElapsedInSeconds);
}

void Model::setActiveAnimation(GLint animationID) {
  if (nullptr == mAnimator) {
    fLogE("This model is not animated. Active animation not set.");
    return;
  }
  mAnimator->setActiveAnimation(animationID);
}

bool Model::isAnimated() const {
  return mAnimator ? true : false;
}

inline void Model::evaluateAnimations() {
  if (mAnimator) {
    mAnimator->updateBonesBufferRAM();
    mProgram->use();
    mAnimator->updateBonesBufferVRAM(mUniformLocationCacheBones);
    mProgramShadow->use();
    mAnimator->updateBonesBufferVRAM(mUniformLocationCacheBonesShadow);
    mProgramShadowColor->use();
    mAnimator->updateBonesBufferVRAM(mUniformLocationCacheBonesShadowColor);
  }
}


inline void Model::initUniformsCache() {
  if (mAnimator) {
    mUniformLocationCacheBones = mProgram->getUniformLocation("uBones[0]");
    mUniformLocationCacheBonesShadow = mProgramShadow->getUniformLocation("uBones[0]");
    mUniformLocationCacheBonesShadowColor = mProgramShadowColor->getUniformLocation("uBones[0]");
  }
}

pu<Mesh> Model::loadMesh(
  const ModelLoader::ShapeType* shape
  , const Material& material
  , flc::Texture2D* diffuseMap
  , flc::Texture2D* normalMap
  , flc::Texture2D* specularMap
  , Engine* engine) {

  auto vao = new flc::VertexArray();
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, shape, mAnimator.get());
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, shape);

  auto mesh = std::make_unique<Mesh>(
    engine
    , material
    , diffuseMap
    , normalMap
    , specularMap
    , mProgram
    , mProgramShadow
    , mProgramShadowColor
    , mProgramLoader.getProgram(EProgram::occlusionOptimizedQuery)
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
    , nullptr
#else
    , mProgramLoader.getProgram(EProgram::ambientOcclusionGeometry)
#endif
    , mProgramLoader.getProgram(EProgram::ambientOcclusionColor)
    , mEngine->getLightSystem()
    , vao
    , false
    , vbo
    , ibo
    , mAnimator.get()
    , GL_TRIANGLES);
  return mesh;
}

void Model::drawFR(ICamera &camera) {
  evaluateAnimations();
  drawWithEffects(camera);
}

void Model::drawPBRP(ICamera &camera) {
  if (mAnimator) {
    //todo for PBRP shadows must be updated elsewhere
    mAnimator->updateBonesBufferRAM();
    mAnimator->updateBonesBufferVRAM(mUniformLocationCacheBones);
  }
  mLights.pushLightUniforms(mProgram);
  mLights.bindShadowmaps();

  drawWithEffectsPBRP(camera);
}

void Model::drawDR(ICamera &camera) {
  evaluateAnimations();
  drawWithEffectsDR(camera);
}

void Model::log() const {
  // nothing
}

inline void Model::initShadowing() {
  mProgramShadow = mProgramLoader.getProgram(mAnimator ? EProgram::shadowWithAnimation : EProgram::shadow);
  mProgramShadowColor =
    mProgramLoader.getProgram(mAnimator ? EProgram::shadowColorCodedWithAnimation : EProgram::shadowColorCoded);
}

void Model::updateRenderer(flc::IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
