/*
 * CameraNull.h
 *
 *  Created on: 26 May 2015
 *      Author: Filip Wasil
 */

#ifndef CAMERANULL_H_
#define CAMERANULL_H_

#include <fillwave/space/base/ICamera.h>

namespace fillwave {
namespace framework {

/*! \class CameraNull
 * \brief Not used. Camera for which both projection and view matrices are always identities.
 */

class CameraNull: public ICamera {
 public:
	CameraNull();

	virtual ~CameraNull() = default;

	void updateProjection();

	GLfloat getProjectionNearPlane();

	GLfloat getProjectionFarPlane();
};

} /* framework */
} /* fillwave */
#endif /* CAMERANULL_H_ */
