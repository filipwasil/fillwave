/*
 * ScenePerspective.cpp
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/space/ScenePerspective.h>
#include <algorithm>    // std::find

namespace fillwave {
namespace framework {

ScenePerspective::ScenePerspective(pCameraPerspective camera) :
	mCamera(camera) {

}

void ScenePerspective::draw() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void ScenePerspective::drawPicking() {
	for (auto& it : mChildren) {
		it->drawPicking(*(mCamera.get()));
	}
}

void ScenePerspective::drawDepthInt() {
	for (auto& it : mChildren) {
		it->drawDepth(*(mCamera.get()));
	}
}

void ScenePerspective::drawOcclusion() {
	for (auto& it : mChildren) {
		it->drawOcclusionBox(*(mCamera.get()));
	}
}

void ScenePerspective::setCamera(pCameraPerspective camera) {
	mCamera = camera;
}

pICamera ScenePerspective::getCamera() {
	return mCamera;
}

} /* models */
pScenePerspective buildScenePerspective(pCameraPerspective camera) {
	return framework::make_shared < framework::ScenePerspective > (camera);
}
} /* fillwave */
