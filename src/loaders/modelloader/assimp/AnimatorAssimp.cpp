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

#include <fillwave/loaders/modelloader/assimp/AnimatorAssimp.h>

#include <fillwave/core/pipeline/Uniform.h>

#include <fillwave/loaders/ModelLoader.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

AnimatorAssimp::BoneAssimp::BoneAssimp(aiBone* assimpBone)
  : BoneDefault(assimpBone->mName.C_Str(), NodeAssimp::convert(assimpBone->mOffsetMatrix), glm::mat4(1.0)) {
  // nothing
}

AnimatorAssimp::BoneAssimp::~BoneAssimp() {
  // nothing
}

AnimatorAssimp::AnimatorAssimp(const aiScene* scene)
  : mTimeSinceStartSeconds(0.0f)
  , mActiveAnimation(ModelLoader::FLAG_ANIMATION_OFF) {
  mAnimationsBufferData.resize(ModelLoader::COUNT_BONES_DEFINED);

  GLuint numBones = 0;

  for (GLuint j = 0; j < scene->mNumMeshes; ++j) {
    for (GLuint i = 0; i < scene->mMeshes[j]->mNumBones; ++i) {
      mBones.push_back(std::make_unique<BoneAssimp>(scene->mMeshes[j]->mBones[i]));
      numBones++;
    }
  }

  if (numBones > ModelLoader::COUNT_BONES_DEFINED) {
    fLogF("We can handle max ", ModelLoader::COUNT_BONES_DEFINED, " bones. The model contains ", numBones, " bones");
  }

  for (GLuint k = 0; k < scene->mNumAnimations; k++) {
    fLogD("Animation ", k, " creation");
    mAnimations.push_back(std::make_unique<Animation>(scene->mAnimations[k]));
  }

  /* Init node tree after bones are added */
  mSceneInverseMatrix = glm::inverse(NodeAssimp::convert(scene->mRootNode->mTransformation));
  mRootAnimationNode = initNode(scene->mRootNode);
}

AnimatorAssimp::~AnimatorAssimp() {
  delete mRootAnimationNode;
}

BoneDefault* AnimatorAssimp::get(GLuint id) {
  if (mBones.size() < id) {
    return mBones[id].get();
  }
  return nullptr;
}


BoneDefault* AnimatorAssimp::get(std::string name) {
  for (auto &it : mBones) {
    if (it->getName() == name) {
      return it.get();
    }
  }
  return nullptr;
}

void UpdateAnimation() {
  // nothing
}

GLint AnimatorAssimp::getBoneId(const std::string& name) const {
  int idx = 0;
  for (auto &it : mBones) {
    if (it->getName() == name) {
      return idx;
    }
    ++idx;
  }
  return -1;
}

AnimatorAssimp::Animation* AnimatorAssimp::getAnimation(GLint i) const {
  return (i != ModelLoader::FLAG_ANIMATION_OFF ? mAnimations[i].get() : nullptr);
}

void AnimatorAssimp::performAnimation(float timeElapsed_s) {
  if (ModelLoader::FLAG_ANIMATION_OFF == mActiveAnimation) {
    mTimeSinceStartSeconds = 0;
    mRootAnimationNode->update(0, glm::mat4(1.0), this, 0);
    return;
  }
  mTimeSinceStartSeconds += timeElapsed_s;
  float TicksPerSecond = (float) (
      mAnimations[mActiveAnimation]->getTicksPerSec() != 0 ? mAnimations[mActiveAnimation]->getTicksPerSec() : 25.0f
  );
  float TimeInTicks = mTimeSinceStartSeconds * TicksPerSecond;
  float AnimationTime = fmod(TimeInTicks, (float) mAnimations[mActiveAnimation]->getDuration());
  mRootAnimationNode->update(AnimationTime, glm::mat4(1.0), this, mActiveAnimation);
}

AnimatorAssimp::NodeAssimp* AnimatorAssimp::initNode(aiNode *node) {
  NodeAssimp* assimpNode = new NodeAssimp(node);
  assimpNode->mBone = get(node->mName.C_Str());

  for (GLuint i = 0; i < node->mNumChildren; i++) {
    assimpNode->mChildren.push_back(initNode(node->mChildren[i]));
  }
  return assimpNode;
}

void AnimatorAssimp::updateBonesBufferRAM() {
  int idx = 0;
  for (auto &it : mBones) {
    mAnimationsBufferData[idx++] = it->getGlobalOffsetMatrix();
  }
}

void AnimatorAssimp::updateBonesBufferVRAM(GLint uniformLocationBones) {
  flc::Uniform::push(uniformLocationBones, mAnimationsBufferData.data(), ModelLoader::COUNT_BONES_DEFINED);
}

void AnimatorAssimp::setActiveAnimation(size_t animationID) {
  if (mAnimations.size() <= animationID) {
    fLogD("Animation ", mActiveAnimation, " has stopped due to setting a non-valid animation id:", animationID);
    mActiveAnimation = ModelLoader::FLAG_ANIMATION_OFF;
    return;
  }

  fLogD("New active animation set: ", mActiveAnimation);
  mActiveAnimation = animationID;
}


AnimatorAssimp::Channel* AnimatorAssimp::findChannel(AnimatorAssimp::Animation *animation, const std::string& nodeName) const {
  for (size_t i = 0; i < animation->getHowManyChannels(); ++i) {
    auto channel = animation->getChannel(i);
    if (std::string(channel->mAffectedNodeName) == nodeName) {
      return channel;
    }
  }
  return nullptr;
}

glm::vec3 AnimatorAssimp::getCurrentTranslation(float timeElapsed_s, Channel *channel) const {
  if (1 == channel->mKeysTranslation.size()) {
    return channel->mKeysTranslation[0].mValue;
  }

  GLuint PositionIndex = getTranslationStep(timeElapsed_s, channel);
  GLuint NextPositionIndex = (PositionIndex + 1);
  assert(NextPositionIndex < channel->mKeysTranslation.size());
  float DeltaTime = (float) (
      channel->mKeysTranslation[NextPositionIndex].mTime - channel->mKeysTranslation[PositionIndex].mTime
  );
  float alpha = (timeElapsed_s - (float) channel->mKeysTranslation[PositionIndex].mTime) / DeltaTime;
  assert(alpha >= 0.0f && alpha <= 1.0f);
  const glm::vec3 &Start = channel->mKeysTranslation[PositionIndex].mValue;
  const glm::vec3 &End = channel->mKeysTranslation[NextPositionIndex].mValue;
  glm::vec3 Delta = End - Start;
  return Start + alpha * Delta;
}

glm::vec3 AnimatorAssimp::getCurrentScale(float timeElapsed_s, Channel *channel) const {
  if (channel->mKeysScaling.size() == 1) {
    return channel->mKeysScaling[0].mValue;
  }

  GLuint ScalingIndex = getScaleStep(timeElapsed_s, channel);
  GLuint NextScalingIndex = (ScalingIndex + 1);
  assert(NextScalingIndex < channel->mKeysScaling.size());
  float DeltaTime = channel->mKeysScaling[NextScalingIndex].mTime - channel->mKeysScaling[ScalingIndex].mTime;
  float alpha = (timeElapsed_s - channel->mKeysScaling[ScalingIndex].mTime) / DeltaTime;
  assert(alpha >= 0.0f && alpha <= 1.0f);
  glm::vec3 Start = channel->mKeysScaling[ScalingIndex].mValue;
  glm::vec3 End = channel->mKeysScaling[NextScalingIndex].mValue;
  glm::vec3 Delta = End - Start;
  return Start + alpha * Delta;
}

glm::quat AnimatorAssimp::getCurrentRotation(float timeElapsed_s, Channel *channel) const {
  if (1 == channel->mKeysRotation.size()) {
    return channel->mKeysRotation[0].mValue;
  }

  GLuint RotationIndex = getRotationStep(timeElapsed_s, channel);
  GLuint NextRotationIndex = (RotationIndex + 1);
  assert(NextRotationIndex < channel->mKeysRotation.size());
  float DeltaTime = channel->mKeysRotation[NextRotationIndex].mTime - channel->mKeysRotation[RotationIndex].mTime;
  float alpha = (timeElapsed_s - (float) channel->mKeysRotation[RotationIndex].mTime) / DeltaTime;
  assert(alpha >= 0.0f && alpha <= 1.0f);
  glm::quat startRotation = channel->mKeysRotation[RotationIndex].mValue;
  glm::quat endRotation = channel->mKeysRotation[NextRotationIndex].mValue;
  return lerp(startRotation, endRotation, alpha);
}

glm::fquat AnimatorAssimp::lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha) const {
  glm::vec4 start = glm::vec4(v0.x, v0.y, v0.z, v0.w);
  glm::vec4 end = glm::vec4(v1.x, v1.y, v1.z, v1.w);
  glm::vec4 interp = glm::mix(start, end, alpha);
  interp = glm::normalize(interp);
  return glm::fquat(interp.w, interp.x, interp.y, interp.z);
}

GLuint AnimatorAssimp::getTranslationStep(float timeElapsed_s, Channel *channel) const {
  for (GLuint i = 0; i < channel->mKeysTranslation.size() - 1; ++i) {
    if (timeElapsed_s < (float) channel->mKeysTranslation[i + 1].mTime) {
      return i;
    }
  }
  fLogF("Animation corrupted. No such translation step.");
  return 0;
}

GLuint AnimatorAssimp::getRotationStep(float timeElapsed_s, Channel *channel) const {
  assert(channel->mKeysRotation.size() > 0);
  for (GLuint i = 0; i < channel->mKeysRotation.size() - 1; ++i) {
    if (timeElapsed_s < channel->mKeysRotation[i + 1].mTime) {
      return i;
    }
  }
  fLogF("No such rotation step");
  return 0;
}

GLuint AnimatorAssimp::getScaleStep(float timeElapsed_s, Channel *channel) const {
  assert(channel->mKeysScaling.size() > 0);
  for (GLuint i = 0; i < channel->mKeysScaling.size() - 1; i++) {
    if (timeElapsed_s < (float) channel->mKeysScaling[i + 1].mTime) {
      return i;
    }
  }
  return 0;
}

} /* flf */
} /* flw */
