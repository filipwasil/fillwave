/*
 * CameraOrthographic.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERAOrthographic_H_
#define CAMERAOrthographic_H_

#include <fillwave/space/base/ICamera.h>

namespace fillwave {
namespace framework {

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

class CameraOrthographic: public ICamera {
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

} /* framework */
typedef std::shared_ptr<framework::CameraOrthographic> pCameraOrthographic;
typedef std::weak_ptr<framework::CameraOrthographic> pwCameraOrthographic;
} /* fillwave */

#endif /* CAMERAOrthographic_H_ */
