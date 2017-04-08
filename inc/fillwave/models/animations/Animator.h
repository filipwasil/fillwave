/*
 * Animator.h
 *
 *  Created on: Jun 25, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <fillwave/models/animations/Bone.h>
#include <fillwave/core/pipeline/Program.h>
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

  AssimpNode(aiNode *node);

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

  std::vector<puAnimation> mAnimations;

  void log();

  Channel *findChannel(Animation *animation, const std::string &nodeName) const;

  glm::vec3 getCurrentTranslation(float timeElapsed_s, Channel *channel) const;

  glm::quat getCurrentRotation(float timeElapsed_s, Channel *channel) const;

  glm::vec3 getCurrentScale(float timeElapsed_s, Channel *channel) const;

  GLuint getTranslationStep(float timeElapsed_s, Channel *channel) const;

  GLuint getRotationStep(float timeElapsed_s, Channel *channel) const;

  GLuint getScaleStep(float timeElapsed_s, Channel *channel) const;

  glm::fquat lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha) const;

  AssimpNode *initNode(aiNode *node);

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
} /* fillwave*/

#endif /* BONEMANAGER_H_ */
