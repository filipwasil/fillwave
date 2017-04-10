/*
 * Animation.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
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

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <fillwave/Assets.h>

#include <vector>
#include <memory>
#include <string>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

namespace flw {
namespace flf {
class Channel;

/*! \class Animation
 * \brief wrapper to assimp aiAnimation*
 */

class Animation final {
public:
  Animation(aiAnimation *assimpAnimation);

  ~Animation();

  /* getTicksPerSec
   * \brief returns an animation parameter:
   */

  float getTicksPerSec() {
    return mTicksPerSec;
  }

  /* getDuration
   * \brief returns an animation parameter
   */

  float getDuration() {
    return mDuration;
  }

  /* getChannel
   * \brief returns particular animation channel
   */

  Channel *getChannel(int i) {
    return mChannels[i];
  }

  /* getHowManyChannels
   * \brief returns how many animation channels are hidden in animation
   */

  int getHowManyChannels() {
    return mChannels.size();
  }

private:
  std::string mName;
  float mDuration;
  float mTicksPerSec;
  std::vector<Channel *> mChannels;

};

} /* flf */
typedef std::unique_ptr<flf::Animation> puAnimation;
} /* flw */

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

#endif /* ANIMATION_H_ */
