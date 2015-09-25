/*
 * Channel.h
 *
 *  Created on: Jul 10, 2014
 *      Author: Filip Wasil
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

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

#include <fillwave/animation/Key.h>

#include <fillwave/Math.h>
#include <fillwave/Assets.h>

#include <vector>
#include <string>

namespace fillwave {
namespace animation {

/*! \class Channel
 * \brief wrapper to assimp aiNodeAnim*
 */

class Channel {
public:
	std::string mAffectedNodeName;

	std::vector<Key<glm::vec3> > mKeysTranslation;
	std::vector<Key<glm::quat> > mKeysRotation;
	std::vector<Key<glm::vec3> > mKeysScaling;

	Channel(fNodeAnim* assimpChannel);
	virtual ~Channel();
};

} /* animation */
} /* fillwave */

#endif /* CHANNEL_H_ */
