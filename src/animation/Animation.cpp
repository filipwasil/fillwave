/*
 * Animation.cpp
 *
 *  Created on: Jun 23, 2014
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

#include <fillwave/animation/Animation.h>
#include <fillwave/animation/Channel.h>
#include <fillwave/extras/Log.h>
#include <fillwave/Assets.h>

FLOGINIT("Animation", FERROR | FFATAL)

namespace fillwave {
namespace animation {

Animation::Animation(fAnimation* assimpAnimation) {
   mName = assimpAnimation->mName.C_Str();
   mDuration = assimpAnimation->mDuration;
   mTicksPerSec = assimpAnimation->mTicksPerSecond;
   mChannels.reserve(assimpAnimation->mNumChannels);
   for (int i=0; i<assimpAnimation->mNumChannels; i++) {
      mChannels.push_back(new Channel(assimpAnimation->mChannels[i]));
   }
}

Animation::~Animation() {
   for (auto it : mChannels) {
      delete it;
   }
   mChannels.clear();
}

} /* animation */
} /* fillwave */
