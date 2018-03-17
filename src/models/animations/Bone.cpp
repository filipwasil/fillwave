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
#include <fillwave/Log.h>

FLOGINIT("Bone", FERROR | FFATAL)

namespace flw {
namespace flf {

Animator::Bone::Bone(aiBone* assimpBone) {
  mName = assimpBone->mName.C_Str();
  mOffsetMatrix = AssimpNode::convert(assimpBone->mOffsetMatrix);
  mGlobalOffsetMatrix = glm::mat4(1.0);
}

void Animator::Bone::setName(std::string name) {
  mName = name;
}

std::string Animator::Bone::getName() const {
  return mName;
}

glm::mat4 Animator::Bone::getOffsetMatrix() const {
  return mOffsetMatrix;
}

glm::mat4 Animator::Bone::getGlobalOffsetMatrix() const {
  return mGlobalOffsetMatrix;
}

void Animator::Bone::setOffsetMatrix(glm::mat4 m) {
  mOffsetMatrix = m;
}

void Animator::Bone::setGlobalOffsetMatrix(glm::mat4 m) {
  mGlobalOffsetMatrix = m;
}

void Animator::Bone::log() const {
  fLogI("Name: %s", (mName.c_str()));
}

} /* flf */
} /* flw */
