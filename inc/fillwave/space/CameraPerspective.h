/*
 * CameraPerspective.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERAPERSPECTIVE_H_
#define CAMERAPERSPECTIVE_H_

#include <fillwave/space/Camera.h>

namespace fillwave {
namespace space {

/*! \class CameraPerspective
 * \brief Camera with perspective projection.
 */

class CameraPerspective: public Camera {
private:
	GLfloat mProjectionFovy, mProjectionAspectRatio, mProjectionNearPlane,
			mProjectionFarPlane;

public:
	CameraPerspective();

	CameraPerspective(
			glm::vec3 position,
			glm::quat rotation,
			GLfloat fovy = 90,
			GLfloat aspectRatio = 1,
			GLfloat nearPlane = 0.01,
			GLfloat farPlane = 100.0);

	virtual ~CameraPerspective() = default;

	GLfloat getProjectionFovy() {
		return mProjectionFovy;
	}

	GLfloat getProjectionAspectRatio() {
		return mProjectionAspectRatio;
	}

	GLfloat getProjectionNearPlane() {
		return mProjectionNearPlane;
	}

	GLfloat getProjectionFarPlane() {
		return mProjectionFarPlane;
	}

	void setProjectionFovy(GLfloat fovy) {
		mProjectionFovy = fovy;
		mRefreshProjection = GL_TRUE;
	}

	void setProjectionAspectRatio(GLfloat aspect) {
		mProjectionAspectRatio = aspect;
		mRefreshProjection = GL_TRUE;
	}

	void setProjectionNearPlane(GLfloat nearPlane) {
		mProjectionNearPlane = nearPlane;
		mRefreshProjection = GL_TRUE;
	}

	void setProjectionFarPlane(GLfloat farPlane) {
		mProjectionFarPlane = farPlane;
		mRefreshProjection = GL_TRUE;
	}

	void updateProjection();
};
} /* space */
typedef std::shared_ptr<space::CameraPerspective> pCameraPerspective;
typedef std::weak_ptr<space::CameraPerspective> pwCameraPerspective;
} /* fillwave */

#endif /* CAMERAPERSPECTIVE_H_ */
