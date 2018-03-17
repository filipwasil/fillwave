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
#include <fillwave/management/LightSystem.h>
#include <fillwave/Fillwave.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

#include <fillwave/models/animations/Conversion.h>

#endif

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

Model::Model(Engine* engine,
    flc::Program* program,
    Shape<flc::VertexBasic> &shape,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    const Material& material)
    : Programmable(program)
    , mEngine(engine)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

  initShadowing(engine);

  ProgramLoader loader(engine);

  std::vector<flc::VertexBasic> vertices = shape.getVertices();
  std::vector<GLuint> indices = shape.getIndices();

  flc::VertexArray* vao = new flc::VertexArray();
  attach(std::make_unique<Mesh>(engine,
                                material,
                                diffuseMap,
                                normalMap,
                                specularMap,
                                program,
                                mProgramShadow,
                                mProgramShadowColor,
                                loader.getProgram(EProgram::occlusionOptimizedQuery),
                                loader.getProgram(EProgram::ambientOcclusionGeometry),
                                loader.getProgram(EProgram::ambientOcclusionColor),
                                engine->getLightSystem(),
                                engine->storeBuffer<flc::VertexBufferBasic>(vao, vertices),
                                engine->storeBuffer<flc::IndexBuffer>(vao, indices),
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
                                mAnimator.get(),
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
                                GL_TRIANGLES,
                                vao));
}

Model::Model(Engine* engine, flc::Program* program, const std::string& shapePath)
    : Programmable(program)
    , mEngine(engine)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  reloadModel(shapePath);
#else
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
                 engine->storeTexture(materials[materialId].diffuse_texname),
                 engine->storeTexture(materials[materialId].bump_texname),
                 engine->storeTexture(materials[materialId].specular_texname),
                 engine));
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

Model::Model(Engine* engine,
    flc::Program* program,
    const std::string& shapePath,
    const std::string& diffuseMapPath,
    const std::string& normalMapPath,
    const std::string& specularMapPath)
    : Programmable(program)
    , mEngine(engine)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  reloadModel(shapePath
    , mEngine->storeTexture(diffuseMapPath.c_str())
    , mEngine->storeTexture(normalMapPath.c_str())
    , mEngine->storeTexture(specularMapPath.c_str()));
#else
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

    attach(loadMesh(shapes[i], attrib,
               shapes[i].mesh.material_ids[0] != -1 ? Material(
                 materials[shapes[i].mesh.material_ids[0]]) : Material(),
               engine->storeTexture(diffuseMapPath.c_str()),
               engine->storeTexture(normalMapPath.c_str()),
               engine->storeTexture(specularMapPath.c_str()),
               engine));
  }
#endif
}

Model::Model(Engine* engine,
    flc::Program* program,
    const std::string& shapePath,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    const Material& material)
    : Programmable(program)
    , mEngine(engine)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  reloadModel(shapePath
    , diffuseMap
    , normalMap
    , specularMap
    , material);
#else
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

    attach(loadMesh(shapes[i], attrib,
               shapes[i].mesh.material_ids[0] != -1 ? Material(
                 materials[shapes[i].mesh.material_ids[0]]) : Material(),
               diffuseMap,
               normalMap,
               specularMap,
               engine));
  }
#endif
}

Model::~Model() {
  // nothing
}

void Model::reloadModel(const std::string& path) {
  unloadNodes();
  const auto* scene = mEngine->getModelFromFile(path);
  if (!scene) {
    fLogF("Model: %s could not be read", path.c_str());
  }
  initAnimations(scene);
  initShadowing(mEngine);
  initUniformsCache();
  loadNodes(scene->mRootNode, scene, this);
}

void Model::reloadModel(
  const std::string& path
  , flc::Texture2D* diff
  , flc::Texture2D* norm
  , flc::Texture2D* specular
  , const Material& material) {
  unloadNodes();
  const aiScene* scene = mEngine->getModelFromFile(path);
  if (!scene) {
    fLogF("Model: %s could not be read", path.c_str());
    return;
  }
  initAnimations(scene);
  initShadowing(mEngine);
  initUniformsCache();
  loadNodes(scene->mRootNode, scene, this, diff, norm, specular, material);
}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

inline void Model::initAnimations(const aiScene* scene) {
  if (scene->HasAnimations()) {
    mAnimator = std::make_unique<Animator>(scene);
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

inline void Model::loadNodes(aiNode *node, const aiScene* scene, Entity* entity) {

  /* Set this node transformations */
  loadNodeTransformations(node, entity);

  for (GLuint i = 0; i < node->mNumMeshes; i++) {
    const aiMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
    const aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

    aiString diffuseMapPathAssimp, normalMapPathAssimp, specularMapPathAssimp;

    if (nullptr == aMesh) {
      continue;
    }

    entity->attach(
      loadMesh(*aMesh
        , Material(aMaterial)
        , mEngine->storeTexture(getMeshTextureName(aiTextureType_DIFFUSE, diffuseMapPathAssimp, aMaterial))
        , mEngine->storeTexture(getMeshTextureName(aiTextureType_NORMALS, normalMapPathAssimp, aMaterial))
        , mEngine->storeTexture(getMeshTextureName(aiTextureType_SPECULAR, specularMapPathAssimp, aMaterial))
        , mEngine));
  }

  /* Evaluate children */
  for (GLuint i = 0; i < node->mNumChildren; i++) {
    pu<Entity> newEntity = std::make_unique<flf::Hinge>();
    loadNodes(node->mChildren[i], scene, newEntity.get());
    entity->attach(std::move(newEntity));
  }
}

inline void Model::loadNodes(aiNode *node,
    const aiScene* scene,
    Entity* entity,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    const Material& material) {

  /* Set this node transformations */
  loadNodeTransformations(node, entity);

  for (GLuint i = 0; i < node->mNumMeshes; ++i) {
    const aiMesh& aMesh = *scene->mMeshes[node->mMeshes[i]];
    entity->attach(loadMesh(aMesh, material, diffuseMap, normalMap, specularMap, mEngine));
  }

  /* Evaluate children */
  for (GLuint i = 0; i < node->mNumChildren; ++i) {
    pu<Entity> newEntity = std::make_unique<flf::Hinge>();
    loadNodes(node->mChildren[i], scene, newEntity.get(), diffuseMap, normalMap, specularMap, material);
    entity->attach(std::move(newEntity));
  }
}


inline const char* Model::getMeshTextureName(aiTextureType type, aiString& path, const aiMaterial* mat) {
  return mat->GetTexture(type, 0, &path, nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS
         ? path.data
         : "128_128_128.color";
}

inline void Model::loadNodeTransformations(aiNode *node, Entity* entity) {
  aiVector3t<float> scale;
  aiQuaterniont<float> rotation;
  aiVector3t<float> position;
  node->mTransformation.Decompose(scale, rotation, position);
  entity->scaleTo(assimpToGlmVec3(scale));
  entity->rotateTo(assimpToGlmQuat(rotation));
  entity->moveTo(assimpToGlmVec3(position));
}

pu<Mesh> Model::loadMesh(const aiMesh& shape,
    const Material& material,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    Engine* engine) {

  ProgramLoader loader(engine);
  auto vao = new flc::VertexArray();
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, shape, mAnimator.get());
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, shape);
  auto mesh = std::make_unique<Mesh>(engine,
                                material,
                                diffuseMap,
                                normalMap,
                                specularMap,
                                mProgram,
                                mProgramShadow,
                                mProgramShadowColor,
                                loader.getProgram(EProgram::occlusionOptimizedQuery),
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

pp<Mesh> Model::getMesh(size_t id) {
  if (id < mMeshes.size()) {
    return pp<Mesh> (mMeshes.at(id));
  }
  fLogF("Requested mesh does not exist. Id requested: ", static_cast<int>(id));
  return pp<Mesh>(nullptr);
}

void Model::performAnimation(GLfloat timeElapsedInSeconds) {
  if (mAnimator && mAnimator->getAnimations() > mActiveAnimation) {
    mAnimator->updateTransformations(mActiveAnimation, timeElapsedInSeconds);
  }
}

void Model::setActiveAnimation(GLint animationID) {
  if (!mAnimator) {
    fLogE("This model is not animated. Active animation not set.");
    return;
  }

  if (mAnimator->getAnimations() <= animationID) {
    fLogD("Animation ", mActiveAnimation, " has stopped due to setting a non-valid animation id:", animationID);
    mActiveAnimation = FILLWAVE_DO_NOT_ANIMATE;
    return;
  }

  fLogD("New active animation set: ", mActiveAnimation);
  mActiveAnimation = animationID;
}

GLint Model::getActiveAnimations() {
  if (mAnimator) {
    return mAnimator->getAnimations();
  }
  return 0;
}

bool Model::isAnimated() const {
  return mAnimator ? true : false;
}

inline void Model::evaluateAnimations() {
  if (mAnimator) {
    mAnimator->updateBonesBuffer();
    mProgram->use();
    mAnimator->updateBonesUniform(mUniformLocationCacheBones);
    mProgramShadow->use();
    mAnimator->updateBonesUniform(mUniformLocationCacheBonesShadow);
    mProgramShadowColor->use();
    mAnimator->updateBonesUniform(mUniformLocationCacheBonesShadowColor);
  }
}


inline void Model::initUniformsCache() {
  if (mAnimator) {
    mUniformLocationCacheBones = mProgram->getUniformLocation("uBones[0]");
    mUniformLocationCacheBonesShadow = mProgramShadow->getUniformLocation("uBones[0]");
    mUniformLocationCacheBonesShadowColor = mProgramShadowColor->getUniformLocation("uBones[0]");
  }
}

#else /* FILLWAVE_MODEL_LOADER_ASSIMP */

puMesh Model::loadMesh(const tinyobj::shape_t& shape,
                tinyobj::attrib_t& attrib,
                const Material& material,
                flc::Texture2D* diffuseMap,
                flc::Texture2D* normalMap,
                flc::Texture2D* specularMap,
                Engine* engine) {
  ProgramLoader loader(engine);
  flc::VertexArray* vao = new flc::VertexArray();

  return std::make_unique < Mesh
       > (engine, material, diffuseMap, normalMap, specularMap, mProgram,
         mProgramShadow, mProgramShadowColor, loader.getOcclusionOptimizedQuery(),
         loader.getAmbientOcclusionGeometry(), loader.getAmbientOcclusionColor(),
         engine->getLightSystem(), engine->storeBuffer<flc::VertexBufferBasic> (vao,
             shape, attrib),
         engine->storeBuffer<flc::IndexBuffer>(vao,
             static_cast<GLuint>(shape.mesh.indices.size())), GL_TRIANGLES,
         vao);
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

void Model::draw(ICamera &camera) {
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  evaluateAnimations();
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  drawWithEffects(camera);
}

void Model::drawPBRP(ICamera &camera) {
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  if (mAnimator) {
    //todo for PBRP shadows must be updated elsewhere
    mAnimator->updateBonesBuffer();
    mAnimator->updateBonesUniform(mUniformLocationCacheBones);
  }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  mLights.pushLightUniforms(mProgram);
  mLights.bindShadowmaps();

  drawWithEffectsPBRP(camera);
}

void Model::drawDR(ICamera &camera) {
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  evaluateAnimations();
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
  drawWithEffectsDR(camera);
}

void Model::log() const {

}

inline void Model::initShadowing(Engine* engine) {
  ProgramLoader loader(engine);
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  if (mAnimator) {
    mProgramShadow = loader.getProgram(EProgram::shadowWithAnimation);
    mProgramShadowColor = loader.getProgram(EProgram::shadowColorCodedWithAnimation);
    return;
  }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
  mProgramShadow = loader.getProgram(EProgram::shadow);
  mProgramShadowColor = loader.getProgram(EProgram::shadowColorCoded);
}

void Model::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
