/*
 * Channel.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/animation/Channel.h>

#include <fillwave/extras/Conversion.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Channel", FERROR | FFATAL)

namespace fillwave {
namespace animation {

Channel::Channel(fNodeAnim* assimpChannel) {
	mAffectedNodeName = assimpChannel->mNodeName.C_Str();

	for (int i = 0; i < assimpChannel->mNumPositionKeys; i++) {
		Key<glm::vec3> keyTranslation(assimpChannel->mPositionKeys[i].mTime,
				assimpToGlmVec3(assimpChannel->mPositionKeys[i].mValue));
		mKeysTranslation.push_back(keyTranslation);
	}

	for (int i = 0; i < assimpChannel->mNumRotationKeys; i++) {
		Key<glm::quat> keyQuaternion(assimpChannel->mRotationKeys[i].mTime,
				assimpToGlmQuat(assimpChannel->mRotationKeys[i].mValue));
		mKeysRotation.push_back(keyQuaternion);
	}

	for (int i = 0; i < assimpChannel->mNumScalingKeys; i++) {
		Key<glm::vec3> keyScaling(assimpChannel->mScalingKeys[i].mTime,
				assimpToGlmVec3(assimpChannel->mScalingKeys[i].mValue));
		mKeysScaling.push_back(keyScaling);
	}

	FLOG_DEBUG(
			" Added an animation channel \n name: %s \n keys S: %lu keys R: %lu keys P: %lu",
			mAffectedNodeName.c_str(), mKeysScaling.size(), mKeysRotation.size(),
			mKeysTranslation.size());
}

Channel::~Channel() {

}

} /* animation */
} /* fillwave */
