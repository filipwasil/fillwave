/*
 * Bone.cpp
 *
 *  Created on: Jun 23, 2014
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


#include <memory>

#include <fillwave/models/animations/Bone.h>
#include <fillwave/Log.h>
#include <fillwave/models/animations/Conversion.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

FLOGINIT("Bone", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Bone::Bone(aiBone *assimpBone) {
  mName = assimpBone->mName.C_Str ();
  mOffsetMatrix = assimpToGlmMat4 (assimpBone->mOffsetMatrix);
  mGlobalOffsetMatrix = glm::mat4 (1.0);
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
  fLogI("Name: %s", (mName.c_str ()));
}

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

} /* framwework */
} /* fillwave */
