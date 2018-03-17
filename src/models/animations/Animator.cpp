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

#include <fillwave/models/animations/Animator.h>

#include <fillwave/core/pipeline/Program.h>

#include <fillwave/Log.h>

FLOGINIT("Animator", FERROR | FFATAL)

namespace flw {
namespace flf {

Animator::Animator(const ModelLoader::Scene* scene)
  : mTimeSinceStartSeconds(0.0f) {
  mAnimationsBufferData.resize(FILLWAVE_MAX_BONES);

  GLuint numBones = 0;

  for (GLuint j = 0; j < scene->mNumMeshes; ++j) {
    for (GLuint i = 0; i < scene->mMeshes[j]->mNumBones; ++i) {
      mBones.push_back(std::make_unique<Bone>(scene->mMeshes[j]->mBones[i]));
      numBones++;
    }
  }

  if (numBones > FILLWAVE_MAX_BONES) {
    fLogF("Crater can handle maximum %d bones. The model contains %d bones.", FILLWAVE_MAX_BONES, numBones);
  }

  for (GLuint k = 0; k < scene->mNumAnimations; k++) {
    fLogD("Animation %d creation", k);
    mAnimations.push_back(std::make_unique<Animation>(scene->mAnimations[k]));
  }

  /* Init node tree after bones are added */
  mSceneInverseMatrix = glm::inverse(AssimpNode::convert(scene->mRootNode->mTransformation));
  mRootAnimationNode = initNode(scene->mRootNode);
}

Animator::~Animator() {
  delete mRootAnimationNode;
}

Animator::Bone* Animator::get(GLuint id) {
  if (mBones.size() < id) {
    return mBones[id].get();
  }
  return nullptr;
}


Animator::Bone *Animator::get(std::string name) {
  for (auto &it : mBones) {
    if (it->getName() == name) {
      return it.get();
    }
  }
  return nullptr;
}

GLint Animator::getId(std::string name) const {
  int idx = 0;
  for (auto &it : mBones) {
    if (it->getName() == name) {
      return idx;
    }
    ++idx;
  }
  return -1;
}

Animator::Animation* Animator::getAnimation(GLint i) const {
  return (i != FILLWAVE_DO_NOT_ANIMATE ? mAnimations[i].get() : nullptr);
}

GLint Animator::getAnimations() const {
  return mAnimations.size();
}

void Animator::updateTransformations(GLint activeAnimation, float timeElapsed_s) {

  if (FILLWAVE_DO_NOT_ANIMATE == activeAnimation) {
    mTimeSinceStartSeconds = 0;
    mRootAnimationNode->update(0, glm::mat4(1.0), this, 0);
    return;
  }
  mTimeSinceStartSeconds += timeElapsed_s;
  float TicksPerSecond = (float) (
      mAnimations[activeAnimation]->getTicksPerSec() != 0 ? mAnimations[activeAnimation]->getTicksPerSec() : 25.0f
  );
  float TimeInTicks = mTimeSinceStartSeconds * TicksPerSecond;
  float AnimationTime = fmod(TimeInTicks, (float) mAnimations[activeAnimation]->getDuration());
  mRootAnimationNode->update(AnimationTime, glm::mat4(1.0), this, activeAnimation);
}

Animator::AssimpNode* Animator::initNode(aiNode *node) {
  AssimpNode* assimpNode = new AssimpNode(node);
  assimpNode->mBone = get(node->mName.C_Str());

  for (GLuint i = 0; i < node->mNumChildren; i++) {
    assimpNode->mChildren.push_back(initNode(node->mChildren[i]));
  }
  return assimpNode;
}

void Animator::updateBonesBuffer() {
  int idx = 0;
  for (auto &it : mBones) {
    mAnimationsBufferData[idx++] = it->getGlobalOffsetMatrix();
  }
}

void Animator::updateBonesUniform(GLint uniformLocationBones) {
  flc::Uniform::push(uniformLocationBones, mAnimationsBufferData.data(), FILLWAVE_MAX_BONES);
}

void Animator::log() {
  fLogI("Bones %du ", mBones.size());
}

Animator::Channel* Animator::findChannel(Animator::Animation *animation, const std::string& nodeName) const {
  for (size_t i = 0; i < animation->getHowManyChannels(); ++i) {
    Channel* channel = animation->getChannel(i);

    if (std::string(channel->mAffectedNodeName) == nodeName) {
      return channel;
    }
  }
  return nullptr;
}

glm::vec3 Animator::getCurrentTranslation(float timeElapsed_s, Channel *channel) const {
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

glm::vec3 Animator::getCurrentScale(float timeElapsed_s, Channel *channel) const {
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

glm::quat Animator::getCurrentRotation(float timeElapsed_s, Channel *channel) const {
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

glm::fquat Animator::lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha) const {
  glm::vec4 start = glm::vec4(v0.x, v0.y, v0.z, v0.w);
  glm::vec4 end = glm::vec4(v1.x, v1.y, v1.z, v1.w);
  glm::vec4 interp = glm::mix(start, end, alpha);
  interp = glm::normalize(interp);
  return glm::fquat(interp.w, interp.x, interp.y, interp.z);
}

GLuint Animator::getTranslationStep(float timeElapsed_s, Channel *channel) const {
  for (GLuint i = 0; i < channel->mKeysTranslation.size() - 1; ++i) {
    if (timeElapsed_s < (float) channel->mKeysTranslation[i + 1].mTime) {
      return i;
    }
  }
  fLogF("Animation corrupted. No such translation step.");
  return 0;
}

GLuint Animator::getRotationStep(float timeElapsed_s, Channel *channel) const {
  assert(channel->mKeysRotation.size() > 0);
  for (GLuint i = 0; i < channel->mKeysRotation.size() - 1; ++i) {
    if (timeElapsed_s < channel->mKeysRotation[i + 1].mTime) {
      return i;
    }
  }
  fLogF("No such rotation step");
  return 0;
}

GLuint Animator::getScaleStep(float timeElapsed_s, Channel *channel) const {
  assert(channel->mKeysScaling.size() > 0);
  for (GLuint i = 0; i < channel->mKeysScaling.size() - 1; i++) {
    if (timeElapsed_s < (float) channel->mKeysScaling[i + 1].mTime) {
      return i;
    }
  }
  return 0;
}

GLint Animator::getElements() const {
  return mBones.size();
}

} /* flf */
} /* flw */
