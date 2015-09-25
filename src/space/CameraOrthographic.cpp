/*
 * CameraOrthographic.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/space/CameraOrthographic.h>
#include <fillwave/extras/Log.h>

FLOGINIT("CameraOrthographic", FERROR | FFATAL)

namespace fillwave {
namespace space {

CameraOrthographic::CameraOrthographic():Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat()){

   mCullingBox.mProjectionBottom = 10.0f;
   mCullingBox.mProjectionFar = 10.0f;
   mCullingBox.mProjectionLeft = 10.0f;
   mCullingBox.mProjectionNear = 10.0f;
   mCullingBox.mProjectionRight = 10.0f;
   mCullingBox.mProjectionTop = 10.0f;

   updateProjection();
}

CameraOrthographic::CameraOrthographic(glm::vec3 position,
      glm::quat rotation,
      GLfloat left,
      GLfloat right,
      GLfloat bottom,
      GLfloat top,
      GLfloat near,
      GLfloat far):Camera(position, rotation){

   mCullingBox.mProjectionBottom = bottom;
   mCullingBox.mProjectionFar = far;
   mCullingBox.mProjectionLeft = left;
   mCullingBox.mProjectionNear = near;
   mCullingBox.mProjectionRight = right;
   mCullingBox.mProjectionTop = top;

   updateProjection();
}

CameraOrthographic::~CameraOrthographic() {

}

void CameraOrthographic::updateProjection() {
   mProjectionMatrix = glm::ortho(mCullingBox.mProjectionLeft,
                                  mCullingBox.mProjectionRight,
                                  mCullingBox.mProjectionBottom,
                                  mCullingBox.mProjectionTop,
                                  mCullingBox.mProjectionNear,
                                  mCullingBox.mProjectionFar);

   mRefreshProjection = GL_FALSE;
}

/*
 * getProjectionNearPlane
 *
 * \brief get the projection near plane distance
 *
 */

GLfloat CameraOrthographic::getProjectionNearPlane() {
   return mCullingBox.mProjectionNear;
}

/*
 * getProjectionFarPlane
 *
 * \brief get the projection far plane distance
 *
 */

GLfloat CameraOrthographic::getProjectionFarPlane() {
   return mCullingBox.mProjectionFar;
}


} /* space */
} /* fillwave */

