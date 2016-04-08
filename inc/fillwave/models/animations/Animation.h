/*
 * Animation.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <fillwave/Assets.h>

#include <vector>
#include <string>

namespace fillwave {
namespace framework {
class Channel;

/*! \class Animation
 * \brief wrapper to assimp aiAnimation*
 */

class Animation {
  public:
	Animation(fAnimation* assimpAnimation);
	virtual ~Animation();

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

	Channel* getChannel(int i) {
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
	std::vector<Channel*> mChannels;

};

} /* framework */
} /* fillwave */

#endif /* ANIMATION_H_ */
