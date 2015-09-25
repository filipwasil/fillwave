/*
 * CameraOrthographic.h
 *
 *  Created on: Dec 21, 2014
 *      Author: Filip Wasil
 */

#ifndef CAMERAOrthographic_H_
#define CAMERAOrthographic_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/space/Camera.h>

namespace fillwave {
namespace space {

/*! \class CullingBox
 * \brief Stores culling box parameters for Orthographic projection.
 */

struct CullingBox {
   GLfloat mProjectionLeft,
           mProjectionRight,
           mProjectionBottom,
           mProjectionTop,
           mProjectionNear,
           mProjectionFar;
};

/*! \class CameraOrthographic
 * \brief Camera with Orthographic projection.
 */

class CameraOrthographic: public Camera {
public:
   CameraOrthographic();

   CameraOrthographic(glm::vec3 position,
         glm::quat rotation,
         GLfloat left,
         GLfloat right,
         GLfloat bottom,
         GLfloat top,
         GLfloat near,
         GLfloat far);
   virtual ~CameraOrthographic();

   void updateProjection();
   /*
    * getProjectionNearPlane
    *
    * \brief get the projection near plane distance
    *
    */

   GLfloat getProjectionNearPlane();

   /*
    * getProjectionFarPlane
    *
    * \brief get the projection far plane distance
    *
    */

   GLfloat getProjectionFarPlane();

private:
   CullingBox mCullingBox;

};

} /* space */
typedef std::shared_ptr<space::CameraOrthographic> pCameraOrthographic;
typedef std::weak_ptr<space::CameraOrthographic> pwCameraOrthographic;
} /* fillwave */

#endif /* CAMERAOrthographic_H_ */
