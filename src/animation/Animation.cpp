/*
 * Animation.cpp
 *
 *  Created on: Jun 23, 2014
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
	for (int i = 0; i < assimpAnimation->mNumChannels; i++) {
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
