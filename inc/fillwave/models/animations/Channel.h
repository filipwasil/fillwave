/*
 * Channel.h
 *
 *  Created on: Jul 10, 2014
 *      Author: Filip Wasil
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <fillwave/models/animations/Key.h>

#include <fillwave/Math.h>
#include <fillwave/Assets.h>

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

#include <vector>
#include <string>

namespace fillwave {
namespace framework {

/*! \class Channel
 * \brief wrapper to assimp aiNodeAnim*
 */
class Channel {
 public:
	std::string mAffectedNodeName;

	std::vector<Key<glm::vec3> > mKeysTranslation;
	std::vector<Key<glm::quat> > mKeysRotation;
	std::vector<Key<glm::vec3> > mKeysScaling;

	Channel(aiNodeAnim* assimpChannel);
	virtual ~Channel() = default;
};

} /* framework */
} /* fillwave */

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

#endif /* CHANNEL_H_ */
