/*
 * Camera.cpp
 *
 *  Created on: May 7, 2014
 *      Author: filip
 */

#include <fillwave/space/Camera.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Camera", FERROR | FFATAL)

namespace fillwave {
namespace space {

Camera::Camera(glm::vec3 position, glm::quat rotation)
		:
				Moveable(position, rotation),
				mRefreshView(GL_TRUE),
				mRefreshProjection(GL_TRUE) {
	updateView();
}

Camera::Camera()
		:
				Moveable(glm::vec3(0.0, 0.0, 1.0)),
				mRefreshView(GL_TRUE),
				mRefreshProjection(GL_TRUE) {
	updateView();
}

inline void Camera::updateView() {
	updateMatrixCache();

	mCameraMatrix =
			glm::lookAt(mTranslation,
					mTranslation
							+ (glm::mat4_cast(mRotation)
									* glm::vec4(0.0, 0.0, -1.0, 1.0)).xyz(),
					(glm::mat4_cast(mRotation) * glm::vec4(0.0, 1.0, 0.0, 1.0)).xyz());

	mRefreshView = GL_FALSE;
	mRefresh = GL_FALSE;
}

void Camera::update() {
	if (mRefreshProjection) {
		FLOG_DEBUG("Camera projection update");
		updateProjection();
	}

	if (mRefresh || mRefreshView) {
		updateView();
	}
}

void Camera::log() {
	FLOG_INFO("Position: %f %f %f", mTranslation[0], mTranslation[1],
			mTranslation[2]);
	FLOG_INFO("Camera rotation: %f %f %f %f ", mRotation[0], mRotation[1],
			mRotation[2], mRotation[4]);
}

glm::mat4 Camera::getEye() {
	return mCameraMatrix;
}

glm::mat4 Camera::getProjection() {
	return mProjectionMatrix;
}

glm::mat4 Camera::getViewProjection() {
	return mProjectionMatrix * mCameraMatrix;
}

} /* space */
} /* fillwave */
