/*
 * Bone.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: filip
 */

#include <memory>

#include <fillwave/models/animations/Bone.h>
#include <fillwave/Log.h>
#include <fillwave/models/animations/Conversion.h>

FLOGINIT("Bone", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Bone::Bone(fBone* assimpBone) {
	mName = assimpBone->mName.C_Str();
	mOffsetMatrix = assimpToGlmMat4(assimpBone->mOffsetMatrix);
	mGlobalOffsetMatrix = glm::mat4(1.0);
}

void Bone::setName(std::string name) {
	mName = name;
}
std::string Bone::getName() const {
	return mName;
}

glm::mat4 Bone::getOffsetMatrix() const {
	return mOffsetMatrix;
}
glm::mat4 Bone::getGlobalOffsetMatrix() const {
	return mGlobalOffsetMatrix;
}

void Bone::setOffsetMatrix(glm::mat4 m) {
	mOffsetMatrix = m;
}
void Bone::setGlobalOffsetMatrix(glm::mat4 m) {
	mGlobalOffsetMatrix = m;
}

void Bone::log() {
	FLOG_INFO("Name: %s", (mName.c_str()));
}

} /* framwework */
} /* fillwave */
