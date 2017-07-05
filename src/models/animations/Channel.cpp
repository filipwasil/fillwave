/*
 * Channel.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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
