/*
 * Camera.h
 *
 *  Created on: May 7, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <fillwave/models/base/Moveable.h>
#include <memory>

namespace fillwave {
namespace framework {

/*! \class ICamera
 * \brief Stores camera view parameters.
 */

class ICamera: public Moveable {
 public:
	ICamera();

	ICamera(glm::vec3, glm::quat rotation);

	virtual ~ICamera() = default;

	void update();
	void updateView();

	glm::mat4 getEye();
	glm::mat4 getProjection();
	glm::mat4 getViewProjection();

	virtual void updateProjection() = 0;
	virtual GLfloat getProjectionNearPlane() = 0;
	virtual GLfloat getProjectionFarPlane() = 0;
	virtual void log() const;

 protected:
	glm::mat4 mCameraMatrix;
	glm::mat4 mProjectionMatrix;

	GLboolean mRefreshView;
	GLboolean mRefreshProjection;
};
} /* framework */
typedef framework::PtrShared<framework::ICamera> pICamera;
} /* fillwave */

#endif /* CAMERA_H_ */
