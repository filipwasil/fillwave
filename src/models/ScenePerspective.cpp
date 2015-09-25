/*
 * ScenePerspective.cpp
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/models/ScenePerspective.h>
#include <algorithm>    // std::find

namespace fillwave {
namespace models {

ScenePerspective::ScenePerspective(pCameraPerspective camera)
:mCamera(camera) {

}

ScenePerspective::~ScenePerspective() {

}

void ScenePerspective::draw() {
   /* Parent-children transformations */
   updateMatrixTree();
   mCamera->update();
   space::CameraPerspective c = *(mCamera.get());
   for (auto it : mChildren) {
      it->draw(c);
   }
}

void ScenePerspective::draw(space::CameraPerspective& camera) {
   /* Parent-children transformations */
   updateMatrixTree();
   for (auto it : mChildren) {
      it->draw(camera);
   }
}

void ScenePerspective::drawDR() {
   if (mSkybox) {
      mSkybox->drawDR(*(mCamera.get()));
   }
   /* Parent-children transformations */
   updateMatrixTree();
   mCamera->update();
   for (auto& it : mChildren) {
      it->drawDR(*(mCamera.get()));
   }
}

void ScenePerspective::drawDR(space::CameraPerspective& camera) {
   if (mSkybox) {
      mSkybox->drawDR(camera);
   }
   /* Parent-children transformations */
   updateMatrixTree();
   for (auto& it : mChildren) {
      it->drawDR(camera);
   }
}

void ScenePerspective::drawSkybox() {
   if (mSkybox) {
      space::CameraPerspective c = *(mCamera.get());
      mSkybox->draw(c);
   }
}

void ScenePerspective::drawPicking() {
   /* Parent-children transformations */
   space::CameraPerspective c = *(mCamera.get());
   for (auto& it : mChildren) {
      it->drawPicking(c);
   }
}

void ScenePerspective::drawDepthInt() {
   for (auto& it : mChildren) {
      it->drawDepth(*(mCamera.get()));
   }
}

void ScenePerspective::drawAOG() {
   for (auto& it : mChildren) {
      it->drawAOG(*(mCamera.get()));
   }
}

void ScenePerspective::drawAOC() {
   for (auto& it : mChildren) {
      it->drawAOC(*(mCamera.get()));
   }
}

void ScenePerspective::setCamera(pCameraPerspective camera) {
   mCamera = camera;
}

pCamera ScenePerspective::getCamera() {
   return mCamera;
}

void ScenePerspective::drawOcclusion() {
   for (auto& it : mChildren) {
      it->drawOcclusionBox(*(mCamera.get()));
   }
}

} /* models */
} /* fillwave */
