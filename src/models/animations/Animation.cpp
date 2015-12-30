/*
 * Animation.cpp
 *
 *  Created on: Jun 23, 2014
 *
 */

#include <fillwave/models/animations/Animation.h>
#include <fillwave/models/animations/Channel.h>
#include <fillwave/Log.h>
#include <fillwave/Assets.h>

FLOGINIT("Animation", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Animation::Animation(fAnimation* assimpAnimation) {
	mName = assimpAnimation->mName.C_Str();
	mDuration = assimpAnimation->mDuration;
	mTicksPerSec = assimpAnimation->mTicksPerSecond;
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

} /* framework */
} /* fillwave */
