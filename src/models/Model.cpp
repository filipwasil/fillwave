/*
 * Model.cpp
 *
 *  Created on: Jun 12, 2014
 *
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

#include <fillwave/actions/callbacks/TimedBoneUpdateCallback.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/models/Model.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/Fillwave.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

#include <fillwave/models/animations/Animator.h>
#include <fillwave/models/animations/Conversion.h>

#endif

#include <fillwave/Log.h>

FLOGINIT("Model", FERROR | FFATAL)

namespace flw {
namespace flf {

Model::Model(Engine *engine,
    flc::Program *program,
    Shape<flc::VertexBasic> &shape,
    flc::Texture2D *diffuseMap,
    flc::Texture2D *normalMap,
    flc::Texture2D *specularMap,
    const Material &material)
    : IFocusable(engine)
    , Programmable(program)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

  initShadowing(engine);

  ProgramLoader loader(engine);

  std::vector<flc::VertexBasic> vertices = shape.getVertices();
  std::vector<GLuint> indices = shape.getIndices();

  flc::VertexArray *vao = new flc::VertexArray();
  attach(std::make_unique<Mesh>(engine,
                                material,
                                diffuseMap,
                                normalMap,
                                specularMap,
                                program,
                                mProgramShadow,
                                mProgramShadowColor,
                                loader.getOcclusionOptimizedQuery(),
                                loader.getAmbientOcclusionGeometry(),
                                loader.getAmbientOcclusionColor(),
                                engine->getLightSystem(),
                                engine->storeBuffer<flc::VertexBufferBasic>(vao, vertices),
                                engine->storeBuffer<flc::IndexBuffer>(vao, indices),
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
                                mAnimator.get(),
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
                                GL_TRIANGLES,
                                vao));
}

Model::Model(Engine *engine, flc::Program *program, const std::string &shapePath)
    : IFocusable(engine)
    , Programmable(program)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  const aiScene *scene = engine->getModelFromFile(shapePath);

  if (scene) {
    initAnimations(scene);
    initShadowing(engine);
    initUniformsCache();
    loadNodes(scene->mRootNode, scene, engine, this);
  } else {
    fLogF("Model: %s could not be read", shapePath.c_str());
  }
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

Model::Model(Engine *engine,
    flc::Program *program,
    const std::string &shapePath,
    const std::string &diffuseMapPath,
    const std::string &normalMapPath,
    const std::string &specularMapPath)
    : IFocusable(engine)
    , Programmable(program)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  const aiScene *scene = engine->getModelFromFile(shapePath);

  if (scene) {
    initAnimations(scene);
    initShadowing(engine); //xxx must be after initAnimations
    initUniformsCache();
    loadNodes(scene->mRootNode, scene, engine, this, diffuseMapPath, normalMapPath, specularMapPath);
  } else {
    fLogF("Model: %s could not be read", shapePath.c_str());
  }
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

Model::Model(Engine *engine,
    flc::Program *program,
    const std::string &shapePath,
    flc::Texture2D *diffuseMap,
    flc::Texture2D *normalMap,
    flc::Texture2D *specularMap,
    const Material &material)
    : IFocusable(engine)
    , Programmable(program)
    , mActiveAnimation(FILLWAVE_DO_NOT_ANIMATE)
    , mLights(engine->getLightSystem()) {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  const aiScene *scene = engine->getModelFromFile(shapePath);

  if (scene) {
    initAnimations(scene);
    initShadowing(engine);
    initUniformsCache();
    loadNodes(scene->mRootNode, scene, engine, this, diffuseMap, normalMap, specularMap, material);
  } else {
    fLogF("Model: %s could not be read", shapePath.c_str());
  }
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

}

void Model::reload() {

}

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

inline void Model::initAnimations(const aiScene *scene) {
  if (scene->HasAnimations()) {
    mAnimator = std::make_unique<Animator>(scene);
    fLogD("attached TimedBoneUpdateCallback to model");
    this->attachHierarchyCallback(std::make_unique<TimedBoneUpdateCallback>(this));
  }
}

inline void Model::loadNodes(aiNode *node,
    const aiScene *scene,
    Engine *engine,
    Entity *entity,
    const std::string &diffuseMapPath,
    const std::string &normalMapPath,
    const std::string &specularMapPath) {

  /* Set this node transformations */

  loadNodeTransformations(node, entity);

  for (GLuint i = 0; i < node->mNumMeshes; i++) {
    const aiMesh *aMesh = scene->mMeshes[node->mMeshes[i]];
    const aiMaterial *aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

    entity->attach(loadMesh(aMesh,
                            Material(aMaterial),
                            engine->storeTexture(diffuseMapPath.c_str()),
                            engine->storeTexture(normalMapPath.c_str()),
                            engine->storeTexture(specularMapPath.c_str()),
                            engine));
  }

  /* Evaluate children */
  for (GLuint i = 0; i < node->mNumChildren; i++) {
    puEntity newEntity = std::make_unique<flf::Hinge>();
    loadNodes(node->mChildren[i], scene, engine, newEntity.get(), diffuseMapPath, normalMapPath, specularMapPath);
    entity->attach(std::move(newEntity));
  }
}

inline void Model::loadNodes(aiNode *node, const aiScene *scene, Engine *engine, Entity *entity) {

  /* Set this node transformations */

  loadNodeTransformations(node, entity);

  for (GLuint i = 0; i < node->mNumMeshes; i++) {
    const aiMesh *aMesh = scene->mMeshes[node->mMeshes[i]];
    const aiMaterial *aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

    aiString diffuseMapPathAssimp, normalMapPathAssimp, specularMapPathAssimp;
    std::string diffuseMapPath, normalMapPath, specularMapPath;

    diffuseMapPath = (
                         aMaterial->GetTexture(aiTextureType_DIFFUSE,
                                               0,
                                               &diffuseMapPathAssimp,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               nullptr,
                                               nullptr) == AI_SUCCESS
                     ) ? diffuseMapPathAssimp.data : "255_255_255.color";

    normalMapPath = (
                        aMaterial->GetTexture(aiTextureType_NORMALS,
                                              0,
                                              &normalMapPathAssimp,
                                              nullptr,
                                              nullptr,
                                              nullptr,
                                              nullptr,
                                              nullptr) == AI_SUCCESS
                    ) ? normalMapPathAssimp.data : "128_128_255.color";

    specularMapPath = (
                          aMaterial->GetTexture(aiTextureType_SPECULAR,
                                                0,
                                                &specularMapPathAssimp,
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                nullptr,
                                                nullptr) == AI_SUCCESS
                      ) ? specularMapPathAssimp.data : "";

    entity->attach(loadMesh(aMesh,
                            Material(aMaterial),
                            engine->storeTexture(diffuseMapPath.c_str()),
                            engine->storeTexture(normalMapPath.c_str()),
                            engine->storeTexture(specularMapPath.c_str()),
                            engine));
  }

  /* Evaluate children */
  for (GLuint i = 0; i < node->mNumChildren; i++) {
    puEntity newEntity = std::make_unique<flf::Hinge>();
    loadNodes(node->mChildren[i], scene, engine, newEntity.get());
    entity->attach(std::move(newEntity));
  }
}

inline void Model::loadNodes(aiNode *node,
    const aiScene *scene,
    Engine *engine,
    Entity *entity,
    flc::Texture2D *diffuseMap,
    flc::Texture2D *normalMap,
    flc::Texture2D *specularMap,
    const Material &material) {

  /* Set this node transformations */

  loadNodeTransformations(node, entity);

  for (GLuint i = 0; i < node->mNumMeshes; i++) {
    const aiMesh *aMesh = scene->mMeshes[i];
    entity->attach(loadMesh(aMesh, material, diffuseMap, normalMap, specularMap, engine));
  }

  /* Evaluate children */
  for (GLuint i = 0; i < node->mNumChildren; i++) {
    puEntity newEntity = std::make_unique<flf::Hinge>();
    loadNodes(node->mChildren[i], scene, engine, newEntity.get(), diffuseMap, normalMap, specularMap, material);
    entity->attach(std::move(newEntity));
  }
}

inline void Model::loadNodeTransformations(aiNode *node, Entity *entity) {
  aiVector3t<float> scale;
  aiQuaterniont<float> rotation;
  aiVector3t<float> position;
  node->mTransformation.Decompose(scale, rotation, position);
  entity->scaleTo(assimpToGlmVec3(scale));
  entity->rotateTo(assimpToGlmQuat(rotation));
  entity->moveTo(assimpToGlmVec3(position));
}

puMesh Model::loadMesh(const aiMesh *shape,
    const Material &material,
    flc::Texture2D *diffuseMap,
    flc::Texture2D *normalMap,
    flc::Texture2D *specularMap,
    Engine *engine) {

  if (!shape) {
    return nullptr;
  }

  ProgramLoader loader(engine);
  auto vao = new flc::VertexArray();
  auto vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao, shape, mAnimator.get());
  auto ibo = engine->storeBuffer<flc::IndexBuffer>(vao, shape);
  return std::make_unique<Mesh>(engine,
                                material,
                                diffuseMap,
                                normalMap,
                                specularMap,
                                mProgram,
                                mProgramShadow,
                                mProgramShadowColor,
                                loader.getOcclusionOptimizedQuery(),
                                loader.getAmbientOcclusionGeometry(),
                                loader.getAmbientOcclusionColor(),
                                engine->getLightSystem(),
                                vbo,
                                ibo,
                                mAnimator.get(),
                                GL_TRIANGLES,
                                vao);
#ifdef FILLWAVE_COMPILATION_OPTIMIZE_RAM_USAGE
  vbo->emptyCPU();
#endif
}

void Model::performAnimation(GLfloat timeElapsed_s) {
  if (mAnimator) {
    mAnimator->updateTransformations(mActiveAnimation, timeElapsed_s);
  }
}

void Model::setActiveAnimation(GLint animationID) {
  if (mAnimator && mAnimator->getAnimations() > animationID) {
    mActiveAnimation = animationID;
    return;
  }
  fLogE("There is no animation for slot: %d", animationID);
  fLogD("Maximum number of animations: %d", mAnimator->getAnimations());
}

GLint Model::getActiveAnimations() {
  if (mAnimator) {
    return mAnimator->getAnimations();
  }
  return 0;
}

bool Model::isAnimated() const {
  return nullptr != mAnimator.get();
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

puMesh Model::loadMesh(tinyobj::shape_t& shape,
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
    /* xxx for PBRP shadows must be updated elsewhere */
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

inline void Model::initShadowing(Engine *engine) {
  ProgramLoader loader(engine);
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  if (mAnimator) {
    mProgramShadow = loader.getShadowWithAnimation();
    mProgramShadowColor = loader.getShadowColorCodedWithAnimation();
    return;
  }
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
  mProgramShadow = loader.getShadow();
  mProgramShadowColor = loader.getShadowColorCoded();
}

void Model::handleFocusEvent(EventType &event) {
  Callback::handleEvent<Callback *>(mCallbacks, event);
}

void Model::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
