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

#include <fillwave/loaders/modelloader/assimp/AnimatorAssimp.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

AnimatorAssimp::Channel::Channel(aiNodeAnim *assimpChannel) {
  mAffectedNodeName = assimpChannel->mNodeName.C_Str();

  mKeysTranslation.reserve(assimpChannel->mNumPositionKeys);
  mKeysRotation.reserve(assimpChannel->mNumRotationKeys);
  mKeysScaling.reserve(assimpChannel->mNumScalingKeys);

  for (unsigned int i = 0; i < assimpChannel->mNumPositionKeys; ++i) {
    mKeysTranslation.emplace_back(
      static_cast<float>(assimpChannel->mPositionKeys[i].mTime)
      , NodeAssimp::convert(assimpChannel->mPositionKeys[i].mValue));
  }

  for (unsigned int i = 0; i < assimpChannel->mNumRotationKeys; ++i) {
    mKeysRotation.emplace_back(
      static_cast<float>(assimpChannel->mRotationKeys[i].mTime)
      , NodeAssimp::convert(assimpChannel->mRotationKeys[i].mValue));
  }

  for (unsigned int i = 0; i < assimpChannel->mNumScalingKeys; ++i) {
    mKeysScaling.emplace_back(
      static_cast<float>(assimpChannel->mScalingKeys[i].mTime)
      , NodeAssimp::convert(assimpChannel->mScalingKeys[i].mValue)
    );
  }

  fLogD(
    "Added an animation channel name: "
    , mAffectedNodeName
    , " keys S: "
    , mKeysScaling.size()
    , " keys R: "
    , mKeysRotation.size()
    , " keys P:"
    , mKeysTranslation.size()
  );
}

} /* flf */
} /* flw */
