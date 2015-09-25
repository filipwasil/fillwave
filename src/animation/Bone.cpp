/*
 * Bone.cpp
 *
 *  Created on: Jun 23, 2014
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

#include <memory>

#include <fillwave/animation/Bone.h>
#include <fillwave/extras/Log.h>
#include <fillwave/extras/Conversion.h>

FLOGINIT("Bone", FERROR | FFATAL)

namespace fillwave {
namespace animation {

Bone::Bone(fBone* assimpBone) {
   mName = assimpBone->mName.C_Str();
   mOffsetMatrix = assimpToGlmMat4(assimpBone->mOffsetMatrix);
   mGlobalOffsetMatrix = glm::mat4(1.0);
}

Bone::~Bone() {

}

void Bone::setName(std::string name) {
   mName = name;
}
std::string Bone::getName() {
   return mName;
}

glm::mat4 Bone::getOffsetMatrix() {
   return mOffsetMatrix;
}
glm::mat4 Bone::getGlobalOffsetMatrix() {
   return mGlobalOffsetMatrix;
}

void Bone::setOffsetMatrix(glm::mat4 m) {
   mOffsetMatrix = m;
}
void Bone::setGlobalOffsetMatrix(glm::mat4 m) {
   mGlobalOffsetMatrix = m;
}

void Bone::log() {
   FLOG_INFO("Name: %s", mName.c_str()) ;
}

} /* animation */
} /* fillwave */
