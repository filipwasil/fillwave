/*
 * CameraNull.h
 *
 *  Created on: 26 May 2015
 *      Author: wasilfil
 */

#ifndef CAMERANULL_H_
#define CAMERANULL_H_

#include <fillwave/space/Camera.h>

namespace fillwave {
namespace space {

/*! \class CameraNull
 * \brief Not used. Camera for which both projection and view matrices are always identities.
 */

class CameraNull: public Camera {
public:
	CameraNull();

	virtual ~CameraNull();

	void updateProjection();

	GLfloat getProjectionNearPlane();

	GLfloat getProjectionFarPlane();
};

} /* models */
} /* fillwave */
#endif /* CAMERANULL_H_ */
