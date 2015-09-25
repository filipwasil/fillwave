/*
 * SceneOrthographic.h
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#ifndef SCENEOrthographic_H_
#define SCENEOrthographic_H_

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

#include <fillwave/models/Scene.h>
#include <fillwave/space/CameraOrthographic.h>

namespace fillwave {
namespace models {
class SceneOrthographic;
}
typedef std::shared_ptr<models::SceneOrthographic> pSceneOrthographic;
namespace models {

/*! \class SceneOrthographic
 * \brief Scene with orthographic projection.
 *
 */

class SceneOrthographic: public Scene {
public:
   SceneOrthographic(pCameraOrthographic camera = pCameraOrthographic());

   virtual ~SceneOrthographic();

   void setCamera(pCameraOrthographic camera);

   pCamera getCamera();

   void draw();

   void drawDR();

   void draw(space::CameraOrthographic& camera);

   void drawDR(space::CameraOrthographic& camera);

   void drawPicking();

   void drawSkybox();

   void drawDepthInt();

   void drawAOG();

   void drawAOC();

   void drawOcclusion();

private:
   pCameraOrthographic mCamera;
};

} /* models */
static pSceneOrthographic buildSceneOrthographic(pCameraOrthographic camera = pCameraOrthographic()) {
   return pSceneOrthographic (new models::SceneOrthographic(camera));
}
} /* fillwave */
#endif /* SCENEOrthographic_H_ */
