/*
 * Animation.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Filip Wasil
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/Assets.h>

#include <vector>
#include <string>

namespace fillwave {
namespace animation {
class Channel;

/*! \class Animation
 * \brief wrapper to assimp aiAnimation*
 */

class Animation {
public:
	Animation(fAnimation* assimpAnimation);
	virtual ~Animation();

	/*
	 * getTicksPerSec
	 *
	 * \brief returns an animation parameter:
	 */

	float getTicksPerSec() {
		return mTicksPerSec;
	}

	/*
	 * getDuration
	 *
	 * \brief returns an animation parameter
	 */

	float getDuration() {
		return mDuration;
	}

	/*
	 * getChannel
	 *
	 * \brief returns particular animation channel
	 */

	Channel* getChannel(int i) {
		return mChannels[i];
	}

	/*
	 * getHowManyChannels
	 *
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

} /* animation */
} /* fillwave */

#endif /* ANIMATION_H_ */
