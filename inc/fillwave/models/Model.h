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

#include "fillwave/models/base/Programmable.h"
#include "fillwave/models/Mesh.h"
#include "fillwave/models/animations/Animator.h"
#include "fillwave/Assets.h"
#include "fillwave/common/TGetter.h"

namespace flw {
class Engine;
namespace flf {
class TimedBoneUpdateCallback;

/*! \class Model
 * \brief Drawable Mesh set.
 */

class Model : public Programmable {
public:

  Model(Engine* engine,
      flc::Program* program,
      flf::Shape<flc::VertexBasic>& shape,
      flc::Texture2D* diffuseMap,
      flc::Texture2D* normalMap,
      flc::Texture2D* specularMap,
      const Material &material);

  Model(Engine *engine, flc::Program* program, const std::string& shapePath);

  Model(Engine *engine,
      flc::Program* program,
      const std::string& shapePath,
      const std::string& diffuseMapPath,
      const std::string& normalMapPath = "",
      const std::string& specularMapPath = "");

  Model(Engine *engine,
      flc::Program* program,
      const std::string& shapePath,
      flc::Texture2D* diffuseMap,
      flc::Texture2D* normalMap = nullptr,
      flc::Texture2D* specularMap = nullptr,
      const Material &material = Material());

  ~Model() override;

  Model &operator=(Model &&) = default;

  Model(Model &&obj) = default;

  void reloadModel(const std::string& shapePath);

  void reloadModel(
    const std::string& path
    , flc::Texture2D* diff
    , flc::Texture2D* norm
    , flc::Texture2D* specular
    , const Material& material = Material());

  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  void drawDR(ICamera &camera) override;

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  /* Animation */
  void performAnimation(GLfloat timeElapsed_us);

  void setActiveAnimation(GLint animationID);

  GLint getActiveAnimations();

  TGetter<Mesh> getMesh(size_t id);

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  void updateRenderer(IRenderer &renderer) override;

  void log() const override;

protected:
  Engine* mEngine;
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  std::unique_ptr<Animator> mAnimator;
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
  GLint mActiveAnimation;

  LightSystem& mLights;
  flc::Program* mProgramShadow;
  flc::Program* mProgramShadowColor;
  GLint mUniformLocationCacheBones;
  GLint mUniformLocationCacheBonesShadow;
  GLint mUniformLocationCacheBonesShadowColor;
  vec<Mesh*> mMeshes;
private:
  /* Init */
  void initUniformsCache();

  void initShadowing(Engine *engine);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  /* Animation */
  bool isAnimated() const override;

  void evaluateAnimations();

  void initAnimations(const aiScene* scene);

  void unloadNodes();

  void loadNodeTransformations(aiNode* node, Entity* entity);

  void loadNodes(aiNode* node, const aiScene* scene, Entity* entity);

  void loadNodes(aiNode* node,
      const aiScene* scene,
      Entity* entity,
      flc::Texture2D* diffuse,
      flc::Texture2D* normal,
      flc::Texture2D* specular,
      const Material &material = Material());

  pu<Mesh> loadMesh(const aiMesh *shape,
      const Material &material,
      flc::Texture2D* diffuse,
      flc::Texture2D* normal,
      flc::Texture2D* specular,
      Engine *engine);

  inline const char* getMeshTextureName(aiTextureType type, aiString& path, const aiMaterial* mat);

#else /* FILLWAVE_MODEL_LOADER_ASSIMP */
  pu<Mesh> loadMesh(tinyobj::shape_t& shape,
             tinyobj::attrib_t& attrib,
             const Material& material,
             flc::Texture2D* diffuseMap,
             flc::Texture2D* normalMap,
             flc::Texture2D* specularMap,
             Engine* engine);

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

};

} /* flf */
} /* flw */
