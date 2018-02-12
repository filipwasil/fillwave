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

#include <fillwave/models/animations/Channel.h>
#include <fillwave/models/animations/Conversion.h>

#include <fillwave/Log.h>

FLOGINIT("Channel", FERROR | FFATAL)

namespace flw {
namespace flf {

Channel::Channel(aiNodeAnim *assimpChannel) {
  mAffectedNodeName = assimpChannel->mNodeName.C_Str();

  for (unsigned int i = 0; i < assimpChannel->mNumPositionKeys; ++i) {
    Key<glm::vec3> keyTranslation(static_cast<float>(assimpChannel->mPositionKeys[i].mTime),
                                  assimpToGlmVec3(assimpChannel->mPositionKeys[i].mValue));
    mKeysTranslation.push_back(keyTranslation);
  }

  for (unsigned int i = 0; i < assimpChannel->mNumRotationKeys; ++i) {
    Key<glm::quat> keyQuaternion(static_cast<float>(assimpChannel->mRotationKeys[i].mTime),
                                 assimpToGlmQuat(assimpChannel->mRotationKeys[i].mValue));
    mKeysRotation.push_back(keyQuaternion);
  }

  for (unsigned int i = 0; i < assimpChannel->mNumScalingKeys; ++i) {
    Key<glm::vec3> keyScaling(static_cast<float>(assimpChannel->mScalingKeys[i].mTime),
                              assimpToGlmVec3(assimpChannel->mScalingKeys[i].mValue));
    mKeysScaling.push_back(keyScaling);
  }

  fLogD(" Added an animation channel \n name: %s \n keys S: %du keys R: %du keys P: %du",
        mAffectedNodeName.c_str(),
        mKeysScaling.size(),
        mKeysRotation.size(),
        mKeysTranslation.size());
}

} /* flf */
} /* flw */
