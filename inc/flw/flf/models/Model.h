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

#include <flw/flf/models/base/Programmable.h>
#include <flw/flf/models/Mesh.h>

#include <flw/flf/loaders/modelloader/ModelLoaderTraits.h>
#include <flw/flf/loaders/ProgramLoader.h>

#include <flw/cmn/pointers/PointerProtected.h>


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
      const flf::Shape<flc::VertexBasic>& shape,
      flc::Texture2D* diffuseMap,
      flc::Texture2D* normalMap = nullptr,
      flc::Texture2D* specularMap = nullptr,
      const Material &material = Material());

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

  void drawFR(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  void drawDR(ICamera &camera) override;

  /* Animation */
  void performAnimation(GLfloat timeElapsed_us);

  void setActiveAnimation(GLint animationID);

  pp<Mesh> getMesh(size_t id);

  /* IRenderable */
  void updateRenderer(flc::IRenderer &renderer) override;

  void log() const override;

 protected:
  Engine* mEngine;
  ProgramLoader mProgramLoader;
  pu<ModelLoader::Animator> mAnimator;

  LightSystem& mLights;
  flc::Program* mProgramShadow;
  flc::Program* mProgramShadowColor;
  GLint mUniformLocationCacheBones;
  GLint mUniformLocationCacheBonesShadow;
  GLint mUniformLocationCacheBonesShadowColor;
  vecHeap<Mesh*> mMeshes;

 private:
  /* Init */
  void initUniformsCache();
  void initShadowing();

  /* Animation */
  void initAnimations(const ModelLoader::SceneType& scene);
  void evaluateAnimations();
  bool isAnimated() const override;

  void unloadNodes();

  void loadNodes(const ModelLoader::NodeType* node, const ModelLoader::SceneType& scene, Entity* entity);

  void loadNodes(
    const ModelLoader::NodeType* node
    , const ModelLoader::SceneType& scene
    , Entity* entity
    , flc::Texture2D* diffuse
    , flc::Texture2D* normal
    , flc::Texture2D* specular
    , const Material &material = Material());

  pu<Mesh> loadMesh(
    const ModelLoader::ShapeType* shape
    , const Material& material
    , flc::Texture2D* diffuse
    , flc::Texture2D* normal
    , flc::Texture2D* specular
    , Engine *engine);
};

} /* flf */
} /* flw */
