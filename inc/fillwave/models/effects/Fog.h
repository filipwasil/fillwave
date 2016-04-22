/*
 * Fog.h
 *
 *  Created on: Jul 18, 2014
 *      Author: Filip Wasil
 */

#ifndef FOG_H_
#define FOG_H_

#include <fillwave/models/effects/Effect.h>

namespace fillwave {
namespace framework {

/*! \class Fog
 * \brief Effect to create a fog.
 */

class Fog: public IEffect {
 private:
	glm::vec3 mColour;
	GLfloat mNearDistance;
	GLfloat mFarDistance;

 public:
	glm::vec3 getColour() {
		return mColour;
	}

	GLfloat getNearDistance() {
		return mNearDistance;
	}

	GLfloat getFarDistance() {
		return mFarDistance;
	}

	void setColour(glm::vec3 colour) {
		mColour = colour;
	}
	void setNearDistance(GLfloat near) {
		mNearDistance = near;
	}
	void setFarDistance(GLfloat far) {
		mFarDistance = far;
	}

	Fog(
	   glm::vec3 colour = glm::vec3(0.1, 0.1, 0.1),
	   GLfloat near = 0.1,
	   GLfloat far = 20.0f);

	virtual ~Fog() = default;

	void preDrawAction(core::Program* program);
	void postDrawAction(core::Program* program);
	void stopAction(core::Program* program);
	void startAction(core::Program* program);
};

} /* framework */
typedef framework::PtrShared<framework::Fog> pFog;
} /* fillwave*/
#endif /* FOG_H_ */
