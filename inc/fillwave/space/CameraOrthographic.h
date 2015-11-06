/*
 * CameraOrthographic.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERAOrthographic_H_
#define CAMERAOrthographic_H_

#include <fillwave/space/Camera.h>

namespace fillwave {
namespace space {

/*! \class CullingBox
 * \brief Stores culling box parameters for Orthographic projection.
 */

struct CullingBox {
	GLfloat mProjectionLeft, mProjectionRight, mProjectionBottom, mProjectionTop,
			mProjectionNear, mProjectionFar;
};

/*! \class CameraOrthographic
 * \brief Camera with Orthographic projection.
 */

class CameraOrthographic: public Camera {
public:
	CameraOrthographic();
	CameraOrthographic(
			glm::vec3 position,
			glm::quat rotation,
			GLfloat left,
			GLfloat right,
			GLfloat bottom,
			GLfloat top,
			GLfloat near,
			GLfloat far);
	virtual ~CameraOrthographic() = default;

	void updateProjection();
	GLfloat getProjectionNearPlane();
	GLfloat getProjectionFarPlane();

private:
	CullingBox mCullingBox;

};

} /* space */
typedef std::shared_ptr<space::CameraOrthographic> pCameraOrthographic;
typedef std::weak_ptr<space::CameraOrthographic> pwCameraOrthographic;
} /* fillwave */

#endif /* CAMERAOrthographic_H_ */
