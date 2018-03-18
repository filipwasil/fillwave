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

#include <fillwave/Math.h>

#include <fillwave/models/animations/Key.h>
#include <fillwave/models/animations/Bone.h>

#include <vector>
#include <string>

#include <assimp/scene.h>

namespace flw {
namespace flf {

/*! \class AnimatorAssimp
 * \brief Manager to handle Bone objects in animation.
 */

class AnimatorAssimp final {

public:
  AnimatorAssimp(const aiScene* scene);
  ~AnimatorAssimp();

 public:
  GLint getAnimationsCount() const;
  GLint getBoneId(const std::string& name) const;

  void updateBonesBufferRAM();
  void updateBonesBufferVRAM(GLint uniformLocationBones);
  void updateAnimation(GLint activeAnimation, float timeElapsed_s);

 private:
  class BoneAssimp : public Bone {
   public:
    BoneAssimp(aiBone* assimpBone);
    ~BoneAssimp() override;
  };

  class NodeAssimp final {
   public:
    NodeAssimp(aiNode* node);
    virtual ~NodeAssimp();

    void update(float time, glm::mat4 parent, AnimatorAssimp* animator, GLint activeAnimation);

    static glm::mat4 convert(aiMatrix4x4 matrix);
    static glm::vec3 convert(aiVector3D vec);
    static glm::vec4 convert(aiColor4D vec);
    static glm::quat convert(aiQuaternion vec);

    Bone* mBone;
    std::vector<NodeAssimp*> mChildren;

   private:
    std::string mName;
    glm::mat4 mTransformation;
  };

  class Channel final {
   public:
    std::string mAffectedNodeName;

    std::vector<Key<glm::vec3> > mKeysTranslation;
    std::vector<Key<glm::quat> > mKeysRotation;
    std::vector<Key<glm::vec3> > mKeysScaling;

    Channel(aiNodeAnim* assimpChannel);
  };

  class Animation final {
   public:
    Animation(aiAnimation* assimpAnimation);
    ~Animation();

    float getTicksPerSec();
    float getDuration();
    Channel* getChannel(int i);
    size_t getHowManyChannels();

   private:
    std::string mName;
    float mDuration;
    float mTicksPerSec;
    std::vector<Channel *> mChannels;
  };

  Bone* get(GLuint id);
  Bone* get(std::string name);
  Channel* findChannel(Animation *animation, const std::string &nodeName) const;
  Animation* getAnimation(GLint i) const;
  NodeAssimp* initNode(aiNode* node);
  glm::fquat lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha) const;

  glm::vec3 getCurrentTranslation(float timeElapsed_s, Channel *channel) const;
  glm::quat getCurrentRotation(float timeElapsed_s, Channel *channel) const;
  glm::vec3 getCurrentScale(float timeElapsed_s, Channel *channel) const;

  GLuint getTranslationStep(float timeElapsed_s, Channel *channel) const;
  GLuint getRotationStep(float timeElapsed_s, Channel *channel) const;
  GLuint getScaleStep(float timeElapsed_s, Channel *channel) const;

  float mTimeSinceStartSeconds;
  NodeAssimp* mRootAnimationNode;
  glm::mat4 mSceneInverseMatrix;
  std::vector<pu<Bone>> mBones;
  std::vector<glm::mat4> mAnimationsBufferData;
  std::vector<pu<Animation>> mAnimations;
};

} /* flf */
} /* flw */
