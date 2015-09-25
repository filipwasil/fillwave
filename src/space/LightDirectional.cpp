/*
 * LightDirectional.cpp
 *
 *  Created on: Nov 30, 2014
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
 * fillwave@gmail.com
 *
 */

#include <fillwave/space/LightDirectional.h>
#include <fillwave/loaders/ProgramLoader.h>

FLOGINIT("DirectionalLight", FERROR | FFATAL)

namespace fillwave {
namespace space {

LightDirectional::LightDirectional(pTexture2DRenderable shadowTexture,
                                   glm::vec3 position,
                                   glm::quat rotation,
                                   glm::vec4 intensity,
                                   pEntity entity)
:Light(position,
       intensity,
       entity),
 mShadowTexture(shadowTexture),
 mShadowCamera ( pCameraOrthographic (new CameraOrthographic(position,
               rotation,
               -10.0f,
               10.0f,
               10.0f,
               -10.0f,
		         0.1f,
		         1000.0f))) {
}

LightDirectional::~LightDirectional() {

}

pCameraOrthographic LightDirectional::getShadowCamera() {
   return mShadowCamera;
}

pTexture2DRenderable LightDirectional::getShadowTexture() {
   return mShadowTexture;
}

void LightDirectional::updateShadowCamera() {
   if (mShadowCamera->getTranslation() != mTranslation) {
      mShadowCamera->moveTo(mTranslation);
      mShadowCamera->update();
   }
   if (mShadowCamera->getRotation() != mRotation ) {
      mShadowCamera->rotateTo(mRotation);
      mShadowCamera->update();
   }
}

/* Camera */
void LightDirectional::log() {
   FLOG_INFO("mShadowCamera->getTranslation(): :%f :%f :%f",
         mShadowCamera->getTranslation().x, mShadowCamera->getTranslation().y,
         mShadowCamera->getTranslation().z);
   FLOG_INFO("mShadowCamera[0]: :%f :%f :%f :%f", mShadowCamera->getEye()[0].x,
         mShadowCamera->getEye()[0].y, mShadowCamera->getEye()[0].z,
         mShadowCamera->getEye()[0].w);
   FLOG_INFO("mShadowCamera[1]: :%f :%f :%f :%f", mShadowCamera->getEye()[1].x,
         mShadowCamera->getEye()[1].y, mShadowCamera->getEye()[1].z,
         mShadowCamera->getEye()[1].w);
   FLOG_INFO("mShadowCamera[2]: :%f :%f :%f :%f", mShadowCamera->getEye()[2].x,
         mShadowCamera->getEye()[2].y, mShadowCamera->getEye()[2].z,
         mShadowCamera->getEye()[2].w);
   FLOG_INFO("mShadowCamera[3]: :%f :%f :%f :%f", mShadowCamera->getEye()[3].x,
         mShadowCamera->getEye()[3].y, mShadowCamera->getEye()[3].z,
         mShadowCamera->getEye()[3].w);
   FLOG_INFO( "Light mIntensity: R:%f G:%f B:%f A:%f", mIntensity.x, mIntensity.y, mIntensity.z, mIntensity.w );
}

} /* space */
} /* fillwave */
