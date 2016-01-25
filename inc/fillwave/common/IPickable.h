/*
 * IPickable.h
 *
 *  Created on: Jan 10, 2016
 *      Author: filip
 */

#ifndef INC_FILLWAVE_COMMON_IPICKABLE_H_
#define INC_FILLWAVE_COMMON_IPICKABLE_H_

#include <fillwave/Math.h>

namespace fillwave {
namespace framework {

/*! \class IPickable
 * \brief Pickable Interface.
 */

class IPickable {
public:
	IPickable();
	virtual ~IPickable() = default;

	bool isPickable() {
		return mFlagPickable;
	}

	glm::vec3 getPickableColor() {
		return mPickColor;
	}

	virtual void pick(glm::vec3 color) = 0;
	virtual void unpick() = 0;
	virtual void onPicked() = 0;
	virtual void onUnpicked() = 0;

protected:
	bool mFlagPickable;
	glm::vec3 mPickColor;
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_COMMON_IPICKABLE_H_ */
