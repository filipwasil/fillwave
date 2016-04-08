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

	Channel(fNodeAnim* assimpChannel);
	virtual ~Channel() = default;
};

} /* framework */
} /* fillwave */

#endif /* CHANNEL_H_ */
