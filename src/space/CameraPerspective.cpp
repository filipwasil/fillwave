/*
 * CameraPerspective.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: filip
 */

#include <fillwave/space/CameraPerspective.h>

namespace fillwave {
namespace space {

CameraPerspective::CameraPerspective():mProjectionFovy(glm::radians(90.0)),
                                       mProjectionAspectRatio(1.0),
                                       mProjectionNearPlane(0.01),
                                       mProjectionFarPlane(100.0){
   updateProjection();
}

CameraPerspective::CameraPerspective(glm::vec3 position,
      glm::quat rotation,
      GLfloat fovy,
      GLfloat aspectRatio,
      GLfloat nearPlane,
      GLfloat farPlane):Camera(position,rotation),
            mProjectionFovy(fovy),
            mProjectionAspectRatio(aspectRatio),
            mProjectionNearPlane(nearPlane),
            mProjectionFarPlane(farPlane){
   updateProjection();
}

CameraPerspective::~CameraPerspective() {

}

void CameraPerspective::updateProjection() {
   mProjectionMatrix = glm::perspective(mProjectionFovy,
                                        mProjectionAspectRatio,
                                        mProjectionNearPlane,
                                        mProjectionFarPlane);
   mRefreshProjection = GL_FALSE;
}

} /* space */
} /* fillwave */
