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

#include <flw/flf/loaders/modelloader/assimp/AnimatorAssimp.h>

namespace flw {
namespace flf {

AnimatorAssimp::Animation::Animation(aiAnimation* assimpAnimation) {
  mName = assimpAnimation->mName.C_Str();
  mDuration = static_cast<float>(assimpAnimation->mDuration);
  mTicksPerSec = static_cast<float>(assimpAnimation->mTicksPerSecond);
  mChannels.reserve(assimpAnimation->mNumChannels);
  for (unsigned int i = 0; i < assimpAnimation->mNumChannels; ++i) {
    mChannels.push_back(new AnimatorAssimp::Channel(assimpAnimation->mChannels[i]));
  }
}

AnimatorAssimp::Animation::~Animation() {
  for (auto it : mChannels) {
    delete it;
  }
  mChannels.clear();
}

float AnimatorAssimp::Animation::getTicksPerSec() {
  return mTicksPerSec;
}

float AnimatorAssimp::Animation::getDuration() {
  return mDuration;
}

AnimatorAssimp::Channel* AnimatorAssimp::Animation::getChannel(int i) {
  return mChannels[i];
}

size_t AnimatorAssimp::Animation::getHowManyChannels() {
  return mChannels.size();
}

} /* flf */
} /* flw */
