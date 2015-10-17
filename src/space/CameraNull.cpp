/*
 * CameraNull.cpp
 *
 *  Created on: 26 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/space/CameraNull.h>

namespace fillwave {
namespace space {

CameraNull::CameraNull() {
	mProjectionMatrix = glm::mat4(1.0);
	mCameraMatrix = glm::mat4(1.0);
	mRefreshProjection = GL_FALSE;
	mRefreshView = GL_FALSE;
}

void CameraNull::updateProjection() {
	//nothing to be done here
}

GLfloat CameraNull::getProjectionNearPlane() {
	return 0.0f;
}

GLfloat CameraNull::getProjectionFarPlane() {
	return 0.0f;
}

} /* models */
} /* fillwave */
