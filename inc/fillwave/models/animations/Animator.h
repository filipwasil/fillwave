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

#include <fillwave/models/animations/Bone.h>
#include <fillwave/models/animations/Animation.h>

namespace flw {
namespace flf {

class Channel;
class Animator;

/*! \class AssimpNode
 * \brief Wrapper for assimp aiNode.
 */

class AssimpNode {
public:
  glm::mat4 mTransformation;
  std::vector<AssimpNode *> mChildren;
  Bone *mBone;
  std::string mName;

  AssimpNode(aiNode*  node);

  virtual ~AssimpNode();

  void update(float time, glm::mat4 parent, Animator *boneManager, GLint activeAnimation);
};

/*! \class Animator
 * \brief Manager to handle Bone objects in animation.
 */

class Animator final {
public:
  Animator(const aiScene *shape);

  ~Animator();

  Bone *get(GLuint id);

  Bone *get(std::string name);

  GLint getId(std::string name) const;

  GLint getElements() const;

  Animation *getAnimation(GLint i) const;

  GLint getAnimations() const;

  std::vector<pu<Animation>> mAnimations;

  void log();

  Channel *findChannel(Animation *animation, const std::string &nodeName) const;

  glm::vec3 getCurrentTranslation(float timeElapsed_s, Channel *channel) const;

  glm::quat getCurrentRotation(float timeElapsed_s, Channel *channel) const;

  glm::vec3 getCurrentScale(float timeElapsed_s, Channel *channel) const;

  GLuint getTranslationStep(float timeElapsed_s, Channel *channel) const;

  GLuint getRotationStep(float timeElapsed_s, Channel *channel) const;

  GLuint getScaleStep(float timeElapsed_s, Channel *channel) const;

  glm::fquat lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha) const;

  AssimpNode *initNode(aiNode*  node);

  void updateBonesBuffer();

  void updateBonesUniform(GLint uniformLocationBones);

  void updateTransformations(GLint activeAnimation, float timeElapsed_s);

private:
  float mTimeSinceStartSeconds;
  AssimpNode *mRootAnimationNode;
  glm::mat4 mSceneInverseMatrix;
  std::vector<puBone> mBones;
  std::vector<glm::mat4> mAnimationsBufferData;
};

} /* flf */
} /* flw */
