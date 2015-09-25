/*
 * LightPoint.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHTPOINT_H_
#define LIGHTPOINT_H_

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

#include <fillwave/core/rendering/Texture3DRenderable.h>
#include <fillwave/space/CameraPerspective.h>
#include <fillwave/models/shapes/Sphere.h>
#include <fillwave/space/Light.h>

#include <map>

namespace fillwave {
class Engine;
namespace space {

/*! \class LightPoint
 * \brief Not used.
 */

class LightPoint: public Light {
public:
   LightPoint(pTexture3DRenderable shadowTexture,
              glm::vec3 position,
              glm::vec4 intensity,
              pEntity entity = pEntity());

   virtual ~LightPoint();

   pTexture3DRenderable getShadowTexture();

   pCameraPerspective getShadowCamera(GLenum id);

   void updateShadowCamera();

   void setEntity(pEntity entity);

   /*! getEntity
    * \brief get the entity assigned to this light
    */

   pEntity getEntity();

protected:
   pTexture3DRenderable mShadowTexture;
   std::map<GLenum, pCameraPerspective> mFaceCameras;

private:
   pEntity mEntity;
   models::Sphere mSphere;
};

} /* space */
typedef std::shared_ptr<space::LightPoint> pLightPoint;
} /* fillwave */

#endif /* LIGHTPOINT_H_ */
