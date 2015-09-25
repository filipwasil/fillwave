/*
 * BoneManager.h
 *
 *  Created on: Jun 25, 2014
 *      Author: Filip Wasil
 */

#ifndef BONEMANAGER_H_
#define BONEMANAGER_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/animation/Bone.h>
#include <fillwave/core/pipeline/Program.h>

#include <map>

namespace fillwave {
namespace animation {
class Animation;
class Channel;
}

namespace manager {

class BoneManager;

/*! \class AssimpNode
 * \brief Wrapper for assimp aiNode.
 */

class AssimpNode {
public:
	std::string mName;
	std::vector<AssimpNode*> mChildren;
	pBone mBone;
	glm::mat4 mTransformation;

	AssimpNode(aiNode* node);

	virtual ~AssimpNode();

	void update(
			float time,
			glm::mat4 parent,
			BoneManager* boneManager,
			GLint activeAnimation);
};

/*! \class BoneManager
 * \brief Manager to handle Bone objects in animation.
 */

class BoneManager {
public:
	BoneManager(const aiScene* shape);
	virtual ~BoneManager();
	void add(aiBone* bone);
	void add(pBone bone);
	void add(animation::Animation* animation);
	pBone get(GLint id);
	pBone get(std::string name);
	GLint getId(std::string name);
	GLint getElements() {
		return mElements;
	}
	animation::Animation* getAnimation(GLint i);
	GLint getAnimations();
	std::vector<animation::Animation*> mAnimations;
	void log();

	animation::Channel* findChannel(
			animation::Animation* animation,
			const std::string& nodeName);

	glm::vec3 getCurrentTranslation(
			float timeElapsed_s,
			animation::Channel* channel);
	glm::quat getCurrentRotation(
			float timeElapsed_s,
			animation::Channel* channel);
	glm::vec3 getCurrentScale(float timeElapsed_s, animation::Channel* channel);

	GLuint getTranslationStep(float timeElapsed_s, animation::Channel* channel);
	GLuint getRotationStep(float timeElapsed_s, animation::Channel* channel);
	GLuint getScaleStep(float timeElapsed_s, animation::Channel* channel);

	glm::fquat lerp(const glm::fquat &v0, const glm::fquat &v1, float alpha);

	AssimpNode* initNode(aiNode* node);
	void updateBonesBuffer();
	void updateBonesUniform(GLint uniformLocationBones);
	void updateTransformations(GLint activeAnimation, float timeElapsed_s);

private:
	float mTimeSinceStartSeconds;
	GLint mElements;
	AssimpNode* mRootAnimationNode;
	glm::mat4 mSceneInverseMatrix;
	std::map<GLint, pBone> mBones;
	std::vector<glm::mat4> mAnimationsBufferData;
};

} /* manager */
} /* fillwave*/

#endif /* BONEMANAGER_H_ */
