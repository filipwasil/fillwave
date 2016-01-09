/*
 * CameraPerspective.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERAPERSPECTIVE_H_
#define CAMERAPERSPECTIVE_H_

#include <fillwave/space/base/ICamera.h>

namespace fillwave {
namespace framework {

/*! \class CameraPerspective
 * \brief Camera with perspective projection.
 */

class CameraPerspective: public ICamera {
private:
	GLfloat mProjectionFovy, mProjectionAspectRatio, mProjectionNearPlane,
			mProjectionFarPlane;

public:
	CameraPerspective();

	CameraPerspective(
			glm::vec3 position,
			glm::quat rotation,
			GLfloat fovy = glm::radians(90.0f),
			GLfloat aspectRatio = 1.0f,
			GLfloat nearPlane = 0.01f,
			GLfloat farPlane = 100.0f);

	virtual ~CameraPerspective() = default;

	GLfloat getProjectionFovy();
	GLfloat getProjectionAspectRatio();
	GLfloat getProjectionNearPlane();
	GLfloat getProjectionFarPlane();

	void setProjectionFovy(GLfloat fovy);
	void setProjectionAspectRatio(GLfloat aspect);
	void setProjectionNearPlane(GLfloat nearPlane);
	void setProjectionFarPlane(GLfloat farPlane);

	void updateProjection();
};
} /* framework */
typedef std::shared_ptr<framework::CameraPerspective> pCameraPerspective;
typedef std::weak_ptr<framework::CameraPerspective> pwCameraPerspective;
} /* fillwave */

#endif /* CAMERAPERSPECTIVE_H_ */
