/*
 * Camera.h
 *
 *  Created on: May 7, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <fillwave/models/Moveable.h>
#include <memory>

namespace fillwave {
namespace space {

/*! \class Camera
 * \brief Stores camera view parameters.
 */

class Camera: public models::Moveable {
public:
	Camera();

	Camera(glm::vec3, glm::quat rotation);

	virtual ~Camera() = default;

	/*
	 * update
	 *
	 * \brief update projection and camera matrices according to other camera data.
	 *
	 */

	void update();

	/*
	 * updateView
	 *
	 * \brief update view matrix according to other camera data.
	 *
	 */

	void updateView();

	/*
	 * updateProjection
	 *
	 * \brief update projection matrix according to other camera data.
	 *
	 */

	virtual void updateProjection() = 0;

	/*
	 * getEye
	 *
	 * \brief get the camera 4x4 matrix
	 *
	 */

	glm::mat4 getEye();

	/*
	 * getProjectionNearPlane
	 *
	 * \brief get the projection near plane distance
	 *
	 */

	virtual GLfloat getProjectionNearPlane() = 0;

	/*
	 * getProjectionFarPlane
	 *
	 * \brief get the projection far plane distance
	 *
	 */

	virtual GLfloat getProjectionFarPlane() = 0;

	/*
	 * getProjection
	 *
	 * \brief get the projection 4x4 matrix
	 *
	 */

	glm::mat4 getProjection();

	/*
	 * getViewProjection
	 *
	 * \brief get the projection 4x4 matrix multipied by view 4x4 matrix
	 *
	 */

	glm::mat4 getViewProjection();

	/*
	 * log
	 *
	 * \brief log
	 *
	 */

	void log();

protected:
	glm::mat4 mCameraMatrix;
	glm::mat4 mProjectionMatrix;

	GLboolean mRefreshProjection;
	GLboolean mRefreshView;
};
} /* space */
typedef std::shared_ptr<space::Camera> pCamera;
typedef std::weak_ptr<space::Camera> pwCamera;
} /* fillwave */

#endif /* CAMERA_H_ */
