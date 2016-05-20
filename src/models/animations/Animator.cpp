/*
 * Animator.cpp
 *
 *  Created on: Jun 25, 2014
 *      Author: filip
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


#include <fillwave/models/animations/Animator.h>
#include <fillwave/models/animations/Channel.h>
#include <fillwave/models/animations/Conversion.h>
#include <fillwave/models/animations/Bone.h>
#include <fillwave/Log.h>

FLOGINIT("Animator", FERROR | FFATAL)

namespace fillwave {
namespace framework {

AssimpNode::AssimpNode(aiNode* node) :
	mTransformation(assimpToGlmMat4(node->mTransformation)),
	mName(node->mName.C_Str()) {

}

void AssimpNode::update(
   float timeElapsed_s,
   glm::mat4 parent,
   Animator* boneManager,
   GLint activeAnimation) {
	std::string nodeName(mName);
	Animation* a = boneManager->getAnimation(activeAnimation);
	if (nullptr == a) {
		return;
	}
	glm::mat4 transformation = mTransformation;
	Channel* channel = boneManager->findChannel(a, nodeName);

	if (channel) {
		glm::vec3 scaling = boneManager->getCurrentScale(timeElapsed_s, channel);
		glm::mat4 scale = glm::scale(glm::mat4(1.0), scaling);

		glm::quat rotation = boneManager->getCurrentRotation(timeElapsed_s,
		                     channel);
		glm::mat4 rotate = glm::mat4_cast(rotation);

		glm::vec3 translation = boneManager->getCurrentTranslation(timeElapsed_s,
		                        channel);
		glm::mat4 translate = glm::translate(glm::mat4(1.0), translation);

		transformation = translate * rotate * scale;
	}

	glm::mat4 m = parent * transformation;

	if (mBone) {
		mBone->setGlobalOffsetMatrix(m * mBone->getOffsetMatrix());
	}

	for (auto& it : mChildren) {
		it->update(timeElapsed_s, m, boneManager, activeAnimation);
	}
}

AssimpNode::~AssimpNode() {
	for (auto& it : mChildren) {
		delete it;
	}
}

Animator::Animator(const aiScene* scene) :
	mTimeSinceStartSeconds(0.0) {
	mAnimationsBufferData.reserve(FILLWAVE_MAX_BONES);

	GLuint numBones = 0;

	for (GLuint j = 0; j < scene->mNumMeshes; j++) {
		for (GLuint i = 0; i < scene->mMeshes[j]->mNumBones; i++) {
			mBones.push_back(std::make_unique<Bone>(scene->mMeshes[j]->mBones[i]));
			numBones++;
		}
	}

	if (numBones > FILLWAVE_MAX_BONES) {
		FLOG_FATAL(
		   "Crater can handle maximum %d bones. The model contains %d bones.",
		   FILLWAVE_MAX_BONES, numBones);
	}

	for (GLuint k = 0; k < scene->mNumAnimations; k++) {
		FLOG_DEBUG("Animation %d creation", k);
		mAnimations.push_back(std::make_unique<Animation>(scene->mAnimations[k]));
	}

	/* Init node tree after bones are added */
	mSceneInverseMatrix = glm::inverse(
	                         assimpToGlmMat4(scene->mRootNode->mTransformation));
	mRootAnimationNode = initNode(scene->mRootNode);
}

Animator::~Animator() {
	delete mRootAnimationNode;
}

Bone* Animator::get(GLuint id) {
	if (mBones.size() < id) {
		return  mBones[id].get();
	}
	return nullptr;
}


Bone* Animator::get(std::string name) {
	for (auto& it : mBones) {
		if (it->getName() == name) {
			return it.get();
		}
	}
	return nullptr;
}

GLint Animator::getId(std::string name) const {
	int idx = 0;
	for (auto& it : mBones) {
		if (it->getName() == name) {
			return idx;
		}
		++idx;
	}
	return -1;
}

Animation* Animator::getAnimation(GLint i) const {
	return (i != FILLWAVE_DO_NOT_ANIMATE ? mAnimations[i].get() : nullptr);
}

GLint Animator::getAnimations() const {
	return mAnimations.size();
}

void Animator::updateTransformations(
   GLint activeAnimation,
   float timeElapsed_s) {

	if (activeAnimation == FILLWAVE_DO_NOT_ANIMATE) {
		mTimeSinceStartSeconds = 0;
		mRootAnimationNode->update(0, glm::mat4(1.0), this, 0);
	} else {
		//FLOG_INFO("Update full transformation with time: %f", timeElapsed_s);
		mTimeSinceStartSeconds += timeElapsed_s;
		float TicksPerSecond = (float) (
		                          mAnimations[activeAnimation]->getTicksPerSec() != 0 ?
		                          mAnimations[activeAnimation]->getTicksPerSec() : 25.0f);
		float TimeInTicks = mTimeSinceStartSeconds * TicksPerSecond;
		float AnimationTime = fmod(TimeInTicks,
		                           (float) mAnimations[activeAnimation]->getDuration());
		mRootAnimationNode->update(AnimationTime, glm::mat4(1.0), this,
		                           activeAnimation);
	}
}

AssimpNode* Animator::initNode(aiNode* node) {
	AssimpNode* assimpNode = new AssimpNode(node);
	assimpNode->mBone = get(node->mName.C_Str());

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		assimpNode->mChildren.push_back(initNode(node->mChildren[i]));
	}
	return assimpNode;
}

void Animator::updateBonesBuffer() {
	int idx = 0;
	for (auto& it : mBones) {
		mAnimationsBufferData[idx++] = it->getGlobalOffsetMatrix();
	}
}

void Animator::updateBonesUniform(GLint uniformLocationBones) {
	core::Uniform::push(uniformLocationBones, mAnimationsBufferData.data(),
	                    FILLWAVE_MAX_BONES);
}

void Animator::log() {
	FLOG_INFO("Bones %lu ", mBones.size());
}

Channel* Animator::findChannel(
   Animation* animation,
   const std::string& nodeName) const {
	for (int i = 0; i < animation->getHowManyChannels(); i++) {
		Channel* channel = animation->getChannel(i);

		if (std::string(channel->mAffectedNodeName) == nodeName) {
			return channel;
		}
	}
	return nullptr;
}

glm::vec3 Animator::getCurrentTranslation(
   float timeElapsed_s,
   Channel* channel) const {
	if (channel->mKeysTranslation.size() == 1) {
		return channel->mKeysTranslation[0].mValue;
	}

	GLuint PositionIndex = getTranslationStep(timeElapsed_s, channel);
	GLuint NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < channel->mKeysTranslation.size());
	float DeltaTime = (float) (channel->mKeysTranslation[NextPositionIndex].mTime
	                           - channel->mKeysTranslation[PositionIndex].mTime);
	float alpha = (timeElapsed_s
	               - (float) channel->mKeysTranslation[PositionIndex].mTime) / DeltaTime;
	assert(alpha >= 0.0f && alpha <= 1.0f);
	const glm::vec3& Start = channel->mKeysTranslation[PositionIndex].mValue;
	const glm::vec3& End = channel->mKeysTranslation[NextPositionIndex].mValue;
	glm::vec3 Delta = End - Start;
	return Start + alpha * Delta;
}

glm::vec3 Animator::getCurrentScale(
   float timeElapsed_s,
   Channel* channel) const {
	if (channel->mKeysScaling.size() == 1) {
		return channel->mKeysScaling[0].mValue;
	}

	GLuint ScalingIndex = getScaleStep(timeElapsed_s, channel);
	GLuint NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < channel->mKeysScaling.size());
	float DeltaTime = (float) (channel->mKeysScaling[NextScalingIndex].mTime
	                           - channel->mKeysScaling[ScalingIndex].mTime);
	float alpha = (timeElapsed_s
	               - (float) channel->mKeysScaling[ScalingIndex].mTime) / DeltaTime;
	assert(alpha >= 0.0f && alpha <= 1.0f);
	glm::vec3 Start = channel->mKeysScaling[ScalingIndex].mValue;
	glm::vec3 End = channel->mKeysScaling[NextScalingIndex].mValue;
	glm::vec3 Delta = End - Start;
	return Start + alpha * Delta;
}

glm::quat Animator::getCurrentRotation(
   float timeElapsed_s,
   Channel* channel) const {
	if (channel->mKeysRotation.size() == 1) {
		return channel->mKeysRotation[0].mValue;
	}

	GLuint RotationIndex = getRotationStep(timeElapsed_s, channel);
	GLuint NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < channel->mKeysRotation.size());
	float DeltaTime = (float) (channel->mKeysRotation[NextRotationIndex].mTime
	                           - channel->mKeysRotation[RotationIndex].mTime);
	float alpha = (timeElapsed_s
	               - (float) channel->mKeysRotation[RotationIndex].mTime) / DeltaTime;
	assert(alpha >= 0.0f && alpha <= 1.0f);
	glm::quat startRotation = channel->mKeysRotation[RotationIndex].mValue;
	glm::quat endRotation = channel->mKeysRotation[NextRotationIndex].mValue;
	return lerp(startRotation, endRotation, alpha);
}

glm::fquat Animator::lerp(
   const glm::fquat &v0,
   const glm::fquat &v1,
   float alpha) const {
	glm::vec4 start = glm::vec4(v0.x, v0.y, v0.z, v0.w);
	glm::vec4 end = glm::vec4(v1.x, v1.y, v1.z, v1.w);
	glm::vec4 interp = glm::mix(start, end, alpha);
	interp = glm::normalize(interp);
	return glm::fquat(interp.w, interp.x, interp.y, interp.z);
}

GLuint Animator::getTranslationStep(
   float timeElapsed_s,
   Channel* channel) const {
	for (GLuint i = 0; i < channel->mKeysTranslation.size() - 1; i++) {
		if (timeElapsed_s < (float) channel->mKeysTranslation[i + 1].mTime) {
			return i;
		}
	}
	FLOG_FATAL("Animation corrupted. No such translation step.");
	return 0;
}

GLuint Animator::getRotationStep(float timeElapsed_s, Channel* channel) const {
	assert(channel->mKeysRotation.size() > 0);
	for (GLuint i = 0; i < channel->mKeysRotation.size() - 1; i++) {
		if (timeElapsed_s < (float) channel->mKeysRotation[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

GLuint Animator::getScaleStep(float timeElapsed_s, Channel* channel) const {
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

} /* framework */
} /* fillwave*/
