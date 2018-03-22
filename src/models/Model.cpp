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

#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/models/Model.h>
#include <fillwave/models/Hinge.h>

#include <fillwave/management/LightSystem.h>

#include <fillwave/Fillwave.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

Model::Model(Engine* engine,
    flc::Program* program,
    Shape<flc::VertexBasic>& shape,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    const Material& material)
    : Programmable(program)
    , mEngine(engine)
    , mLights(engine->getLightSystem()) {

  initShadowing(engine);

  ProgramLoader loader(engine);

  std::vector<flc::VertexBasic> vertices = shape.getVertices();
  std::vector<GLuint> indices = shape.getIndices();

  flc::VertexArray* vao = new flc::VertexArray();
  attach(std::make_unique<Mesh>(
    engine
    , material
    , diffuseMap
    , normalMap
    , specularMap
    , program
    , mProgramShadow
    , mProgramShadowColor
    , loader.getProgram(EProgram::occlusionOptimizedQuery)
    , loader.getProgram(EProgram::ambientOcclusionGeometry)
    , loader.getProgram(EProgram::ambientOcclusionColor)
    , engine->getLightSystem()
    , engine->storeBuffer<flc::VertexBufferBasic>(vao, vertices)
    , engine->storeBuffer<flc::IndexBuffer>(vao, indices)
    , mAnimator.get()
    , GL_TRIANGLES
    , vao)
  );
}

Model::Model(
  Engine* engine
  , flc::Program* program
  , const std::string& shapePath)
  : Programmable(program)
  , mEngine(engine)
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

void Model::reloadModel(const std::string& path) {
  unloadNodes();
  const auto* scene = mEngine->getScene(path);
  if (!scene) {
    fLogF("Model: ", path, " could not be read");
  }
  initAnimations(scene);
  initShadowing(mEngine);
  initUniformsCache();
  loadNodes(ModelLoader::getRootNode(scene), scene, this);

  ///////////////
#if 0
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  tinyobj::attrib_t attrib;
  std::string err;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, shapePath.c_str())) {
    fLogF("Model: %s could not be read", shapePath.c_str());
  }
  if (!err.empty()) { // `err` may contain warning message.
    fLogW("%s", err.c_str());
  }

  initShadowing(engine);
  for (GLuint i = 0; i < shapes.size(); i++) {
    if (shapes[i].mesh.material_ids.empty()) {
      fLogF("No materials available");
    }

    int materialId = shapes[i].mesh.material_ids[0];
    if (materialId != -1) {
      attach(loadMesh(shapes[i], attrib,
                 Material(materials[materialId]),
// or
//               shapes[i].mesh.material_ids[0] != -1 ? Material(
//               materials[shapes[i].mesh.material_ids[0]]) : Material(),
                 engine->storeTexture(materials[materialId].diffuse_texname),
                 engine->storeTexture(materials[materialId].bump_texname),
                 engine->storeTexture(materials[materialId].specular_texname),
// or Tex*
//               diffuseMap,
//               normalMap,
//               specularMap,

// or paths
//               engine->storeTexture(diffuseMapPath.c_str()),
//               engine->storeTexture(normalMapPath.c_str()),
//               engine->storeTexture(specularMapPath.c_str()),
//                 engine));
      continue;
    }
    attach(loadMesh(shapes[i], attrib,
               Material(),
               nullptr,
               nullptr,
               nullptr,
               engine));
  }
#endif
}

void Model::reloadModel(
  const std::string& path
  , flc::Texture2D* diff
  , flc::Texture2D* norm
  , flc::Texture2D* specular
  , const Material& material) {
  unloadNodes();
  const auto* scene = mEngine->getScene(path);
  if (!scene) {
    fLogF("Model: %s could not be read", path.c_str());
    return;
  }
  initAnimations(scene);
  initShadowing(mEngine);
  initUniformsCache();
  loadNodes(ModelLoader::getRootNode(scene), scene, this, diff, norm, specular, material);
}

inline void Model::initAnimations(const ModelLoader::Scene* scene) {
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

inline void Model::loadNodes(const ModelLoader::Node* node, const ModelLoader::Scene* scene, Entity* entity) {

  /* Set this node transformations */
  ModelLoader::setTransformation(node, entity);
  auto meshes = ModelLoader::getMeshes(node, scene);
  for (auto& meshCreationInfo : meshes) {
    entity->attach(
      loadMesh(
        meshCreationInfo.shape
        , meshCreationInfo.data
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
  const ModelLoader::Node* node
  , const ModelLoader::Scene* scene
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
      , meshCreationInfo.data
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

pp<Mesh> Model::getMesh(size_t id) {
  if (id < mMeshes.size()) {
    return pp<Mesh> (mMeshes.at(id));
  }
  fLogF("Requested mesh does not exist. Id requested: ", static_cast<int>(id));
  return pp<Mesh>(nullptr);
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
  , const ModelLoader::ShapeDataType& data
  , const Material& material
  , flc::Texture2D* diffuseMap
  , flc::Texture2D* normalMap
  , flc::Texture2D* specularMap
  , Engine* engine) {

  ProgramLoader loader(engine);
  auto vao = new flc::VertexArray();
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, shape);
//  engine->storeBuffer<flc::IndexBuffer>(vao, static_cast<GLuint>(shape.mesh.indices.size())), GL_TRIANGLES, vao);
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, shape, data, mAnimator.get());
  auto mesh = std::make_unique<Mesh>(
    engine, material, diffuseMap, normalMap, specularMap, mProgram, mProgramShadow, mProgramShadowColor, loader
      .getProgram(EProgram::occlusionOptimizedQuery),
                                     loader.getProgram(EProgram::ambientOcclusionGeometry),
                                     loader.getProgram(EProgram::ambientOcclusionColor),
                                     engine->getLightSystem(),
                                     vbo,
                                     ibo,
                                     mAnimator.get(),
                                     GL_TRIANGLES,
                                     vao);
#ifdef FILLWAVE_COMPILATION_OPTIMIZE_RAM_USAGE
  vbo->emptyCPU();
#endif
  return mesh;
}

void Model::draw(ICamera &camera) {
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

}

inline void Model::initShadowing(Engine* engine) {
  ProgramLoader loader(engine);
  if (mAnimator) {
    mProgramShadow = loader.getProgram(EProgram::shadowWithAnimation);
    mProgramShadowColor = loader.getProgram(EProgram::shadowColorCodedWithAnimation);
    return;
  }
  mProgramShadow = loader.getProgram(EProgram::shadow);
  mProgramShadowColor = loader.getProgram(EProgram::shadowColorCoded);
}

void Model::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
