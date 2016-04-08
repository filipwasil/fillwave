/*
 * Camera.cpp
 *
 *  Created on: May 7, 2014
 *      Author: filip
 */

#include <fillwave/space/base/ICamera.h>
#include <fillwave/Log.h>

FLOGINIT("Camera", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace framework {

ICamera::ICamera(glm::vec3 position, glm::quat rotation) :
	Moveable(position, rotation),
	mRefreshView(GL_TRUE),
	mRefreshProjection(GL_TRUE) {
	updateView();
}

ICamera::ICamera() :
	Moveable(glm::vec3(0.0, 0.0, 1.0)),
	mRefreshView(GL_TRUE),
	mRefreshProjection(GL_TRUE) {
	updateView();
}

inline void ICamera::updateView() {
	updateMatrixCache();

	mCameraMatrix =
	    glm::lookAt(mTranslation,
	                mTranslation
	                + (glm::mat4_cast(mRotation) * glm::vec4(0.0, 0.0, -1.0, 1.0)).xyz(),
	                (glm::mat4_cast(mRotation) * glm::vec4(0.0, 1.0, 0.0, 1.0)).xyz());

	mRefreshView = GL_FALSE;
	mRefresh = GL_FALSE;
}

void ICamera::update() {
	if (mRefreshProjection) {
		FLOG_DEBUG("Camera projection update");
		updateProjection();
	}

	if (mRefresh || mRefreshView) {
		updateView();
	}
}

void ICamera::log() const {
	auto d = [] (GLfloat f) {
		return static_cast<double>(f);
	};
	FLOG_INFO("Position: %f %f %f", d(mTranslation[0]), d(mTranslation[1]),
	          d(mTranslation[2]));
//	FLOG_INFO("Camera rotation: %f %f %f %f ", d(mRotation[0]), d(mRotation[1]),
//			d(mRotation[2]), d(mRotation[4]));
}

glm::mat4 ICamera::getEye() {
	return mCameraMatrix;
}

glm::mat4 ICamera::getProjection() {
	return mProjectionMatrix;
}

glm::mat4 ICamera::getViewProjection() {
	return mProjectionMatrix * mCameraMatrix;
}

} /* framework */
} /* fillwave */
