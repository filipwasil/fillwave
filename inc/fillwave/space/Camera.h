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

/*! \class Camera
 * \brief Stores camera view parameters.
 */

class Camera: public Moveable {
public:
	Camera();

	Camera(glm::vec3, glm::quat rotation);

	virtual ~Camera() = default;

	void update();
	void updateView();
	virtual void updateProjection() = 0;

	glm::mat4 getEye();

	virtual GLfloat getProjectionNearPlane() = 0;
	virtual GLfloat getProjectionFarPlane() = 0;
	glm::mat4 getProjection();
	glm::mat4 getViewProjection();
	void log();

protected:
	glm::mat4 mCameraMatrix;
	glm::mat4 mProjectionMatrix;

	GLboolean mRefreshView;
	GLboolean mRefreshProjection;
};
} /* framework */
typedef std::shared_ptr<framework::Camera> pCamera;
typedef std::weak_ptr<framework::Camera> pwCamera;
} /* fillwave */

#endif /* CAMERA_H_ */
