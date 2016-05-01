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
 public:
	Fog(glm::vec3 colour = glm::vec3(0.1f, 0.1f, 0.1f),
	    GLfloat near = 0.1f,
	    GLfloat far = 20.0f);

	virtual ~Fog() = default;

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

	void preDrawAction(core::Program* program) override;
	void postDrawAction(core::Program* program) override;
	void stopAction(core::Program* program) override;
	void startAction(core::Program* program) ;

 private:
	glm::vec3 mColour;
	GLfloat mNearDistance;
	GLfloat mFarDistance;
};

} /* framework */
typedef std::shared_ptr<framework::Fog> pFog;
} /* fillwave*/
#endif /* FOG_H_ */
