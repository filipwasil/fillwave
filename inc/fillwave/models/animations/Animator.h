/*
 * Animator.h
 *
 *  Created on: Jun 25, 2014
 *      Author: Filip Wasil
 */

#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <fillwave/models/animations/Bone.h>
#include <fillwave/core/pipeline/Program.h>
#include <map>

namespace fillwave {
namespace framework {

class Animation;
class Channel;
class Animator;

/*! \class AssimpNode
 * \brief Wrapper for assimp aiNode.
 */

class AssimpNode {
 public:
	glm::mat4 mTransformation;
	std::vector<AssimpNode*> mChildren;
	pBone mBone;
	std::string mName;

	AssimpNode(aiNode* node);

	virtual ~AssimpNode();

	void update(
	   float time,
	   glm::mat4 parent,
	   Animator* boneManager,
	   GLint activeAnimation);
};

/*! \class Animator
 * \brief Manager to handle Bone objects in animation.
 */

class Animator {
 public:
	Animator(const aiScene* shape);
	virtual ~Animator();
	void add(aiBone* bone);
	void add(pBone bone);
	void add(Animation* animation);
	pBone get(GLint id);
	pBone get(std::string name);
	GLint getId(std::string name) const;
	GLint getElements() const;
	Animation* getAnimation(GLint i) const;
	GLint getAnimations() const;
	std::vector<Animation*> mAnimations;
	void log();

	Channel* findChannel(
	   Animation* animation,
	   const std::string& nodeName) const;

	glm::vec3 getCurrentTranslation(float timeElapsed_s, Channel* channel) const;
	glm::quat getCurrentRotation(float timeElapsed_s, Channel* channel) const;
	glm::vec3 getCurrentScale(float timeElapsed_s, Channel* channel) const;

	GLuint getTranslationStep(float timeElapsed_s, Channel* channel) const;
	GLuint getRotationStep(float timeElapsed_s, Channel* channel) const;
	GLuint getScaleStep(float timeElapsed_s, Channel* channel) const;

	glm::fquat lerp(
	   const glm::fquat &v0,
	   const glm::fquat &v1,
	   float alpha) const;

	AssimpNode* initNode(aiNode* node);
	void updateBonesBuffer();
	void updateBonesUniform(GLint uniformLocationBones);
	void updateTransformations(GLint activeAnimation, float timeElapsed_s);

 private:
	GLint mElements;
	float mTimeSinceStartSeconds;
	AssimpNode* mRootAnimationNode;
	glm::mat4 mSceneInverseMatrix;
	std::map<GLint, pBone> mBones;
	std::vector<glm::mat4> mAnimationsBufferData;
};

} /* framework */
} /* fillwave*/

#endif /* BONEMANAGER_H_ */
