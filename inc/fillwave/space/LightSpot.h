/*
 * LightSpot.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Filip Wasil
 */

#ifndef LIGHTSPOT_H_
#define LIGHTSPOT_H_

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

#include <fillwave/space/Light.h>
#include <fillwave/space/CameraPerspective.h>
#include <fillwave/management/TextureManager.h>

namespace fillwave {
namespace space {

/*! \class LightSpot
 * \brief Light implementing directional torch.
 */

class LightSpot: public Light {
protected:
   pCameraPerspective mShadowCamera;
   pTexture2DRenderable mShadowTexture;

public:
   LightSpot(pTexture2DRenderable shadowTexture,
             glm::vec3 position,
             glm::quat rotation,
             glm::vec4 intensity,
             pEntity entity = pEntity());
   virtual ~LightSpot();

   pTexture2DRenderable getShadowTexture();

   pCameraPerspective getShadowCamera();

   void updateShadowCamera();

   void log();

   };

} /* space */
typedef std::shared_ptr<space::LightSpot> pLightSpot;
} /* fillwave */

#endif /* LIGHTSPOT_H_ */
