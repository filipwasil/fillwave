/*
 * CameraPerspective.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: filip
 */

#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace framework {

CameraPerspective::CameraPerspective()
		:
				mProjectionFovy(glm::radians(90.0)),
				mProjectionAspectRatio(1.0),
				mProjectionNearPlane(0.01),
				mProjectionFarPlane(100.0) {
	updateProjection();
}

CameraPerspective::CameraPerspective(
		glm::vec3 position,
		glm::quat rotation,
		GLfloat fovy,
		GLfloat aspectRatio,
		GLfloat nearPlane,
		GLfloat farPlane)
		:
				ICamera(position, rotation),
				mProjectionFovy(fovy),
				mProjectionAspectRatio(aspectRatio),
				mProjectionNearPlane(nearPlane),
				mProjectionFarPlane(farPlane) {
	updateProjection();
}

void CameraPerspective::updateProjection() {
	mProjectionMatrix = glm::perspective(mProjectionFovy, mProjectionAspectRatio,
			mProjectionNearPlane, mProjectionFarPlane);
	mRefreshProjection = GL_FALSE;
}

GLfloat CameraPerspective::getProjectionFovy() {
	return mProjectionFovy;
}

GLfloat CameraPerspective::getProjectionAspectRatio() {
	return mProjectionAspectRatio;
}

GLfloat CameraPerspective::getProjectionNearPlane() {
	return mProjectionNearPlane;
}

GLfloat CameraPerspective::getProjectionFarPlane() {
	return mProjectionFarPlane;
}

void CameraPerspective::setProjectionFovy(GLfloat fovy) {
	mProjectionFovy = fovy;
	mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionAspectRatio(GLfloat aspect) {
	mProjectionAspectRatio = aspect;
	mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionNearPlane(GLfloat nearPlane) {
	mProjectionNearPlane = nearPlane;
	mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionFarPlane(GLfloat farPlane) {
	mProjectionFarPlane = farPlane;
	mRefreshProjection = GL_TRUE;
}

} /* framework */
} /* fillwave */
