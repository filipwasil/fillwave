/*
 * Animation.cpp
 *
 *  Created on: Jun 23, 2014
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


#include <fillwave/models/animations/Animation.h>
#include <fillwave/models/animations/Channel.h>


namespace flw {
namespace flf {

Animation::Animation(aiAnimation *assimpAnimation) {
  mName = assimpAnimation->mName.C_Str();
  mDuration = static_cast<float>(assimpAnimation->mDuration);
  mTicksPerSec = static_cast<float>(assimpAnimation->mTicksPerSecond);
  mChannels.reserve(assimpAnimation->mNumChannels);
  for (unsigned int i = 0; i < assimpAnimation->mNumChannels; i++) {
    mChannels.push_back(new Channel(assimpAnimation->mChannels[i]));
  }
}

Animation::~Animation() {
  for (auto it : mChannels) {
    delete it;
  }
  mChannels.clear();
}

} /* flf */
} /* flw */
