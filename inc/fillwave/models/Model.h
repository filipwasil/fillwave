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

#include <fillwave/models/base/Programmable.h>
#include <fillwave/common/IFocusable.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Assets.h>

namespace flw {
class Engine;
namespace flf {
class TimedBoneUpdateCallback;

/*! \class Model
 * \brief Drawable Mesh set.
 */

class Model : public IFocusable, public Programmable {
public:

  Model(Engine *engine,
      flc::Program *program,
      flf::Shape<flc::VertexBasic> &shape,
      flc::Texture2D *diffuseMap,
      flc::Texture2D *normalMap,
      flc::Texture2D *specularMap,
      const Material &material);

  Model(Engine *engine, flc::Program *program, const std::string &shapePath);

  Model(Engine *engine,
      flc::Program *program,
      const std::string &shapePath,
      const std::string &diffuseMapPath,
      const std::string &normalMapPath = "",
      const std::string &specularMapPath = "");

  Model(Engine *engine,
      flc::Program *program,
      const std::string &shapePath,
      flc::Texture2D *diffuseMap,
      flc::Texture2D *normalMap = nullptr,
      flc::Texture2D *specularMap = nullptr,
      const Material &material = Material());

  virtual ~Model();

  Model &operator=(Model &&) = default;

  Model(Model &&obj) = default;

  void reload();

  void draw(ICamera &camera);

  void drawPBRP(ICamera &camera);

  void drawDR(ICamera &camera);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  /* Animation */
  void performAnimation(GLfloat timeElapsed_us);

  void setActiveAnimation(GLint animationID);

  GLint getActiveAnimations();

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  void handleFocusEvent(EventType &event) override;

  void updateRenderer(IRenderer &renderer) override;

  void log() const;

protected:
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
  std::unique_ptr<Animator> mAnimator;
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
  GLint mActiveAnimation;

  LightSystem *mLights;
  flc::Program *mProgramShadow;
  flc::Program *mProgramShadowColor;
  GLint mUniformLocationCacheBones, mUniformLocationCacheBonesShadow, mUniformLocationCacheBonesShadowColor;
private:
  /* Init */
  void initUniformsCache();

  void initShadowing(Engine *engine);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  /* Animation */
  bool isAnimated() const;

  void evaluateAnimations();

  void initAnimations(const aiScene *scene);

  void loadNodeTransformations(aiNode *node, Entity *entity);

  void loadNodes(aiNode *node, const aiScene *scene, Engine *engine, Entity *entity);

  void loadNodes(aiNode *node,
      const aiScene *scene,
      Engine *engine,
      Entity *entity,
      const std::string &diffuseMapPath,
      const std::string &normalMapPath,
      const std::string &specularMapPath);

  void loadNodes(aiNode *node,
      const aiScene *scene,
      Engine *engine,
      Entity *entity,
      flc::Texture2D *diffuseMap,
      flc::Texture2D *normalMap,
      flc::Texture2D *specularMap,
      const Material &material);

  puMesh loadMesh(const aiMesh *shape,
      const Material &material,
      flc::Texture2D *diffuseMap,
      flc::Texture2D *normalMap,
      flc::Texture2D *specularMap,
      Engine *engine);

#else /* FILLWAVE_MODEL_LOADER_ASSIMP */
  puMesh loadMesh(tinyobj::shape_t& shape,
             tinyobj::attrib_t& attrib,
             const Material& material,
             flc::Texture2D* diffuseMap,
             flc::Texture2D* normalMap,
             flc::Texture2D* specularMap,
             Engine* engine);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

};

} /* flf */
typedef std::unique_ptr<flf::Model> puModel;
} /* flw */
