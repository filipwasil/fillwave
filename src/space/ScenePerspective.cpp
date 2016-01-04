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

ScenePerspective::ScenePerspective(pCameraPerspective camera)
		: mCamera(camera) {

}

void ScenePerspective::draw() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void ScenePerspective::drawPBRP() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void ScenePerspective::draw(ICamera& camera) {
	for (auto& it : mChildren) {
		it->draw(camera);
	}
}

void ScenePerspective::drawDR() {
	if (mSkybox) {
		mSkybox->drawDR(*(mCamera.get()));
	}
	mCamera->update();
	for (auto& it : mChildren) {
		it->drawDR(*(mCamera.get()));
	}
}

void ScenePerspective::drawDR(ICamera& camera) {
	if (mSkybox) {
		mSkybox->drawDR(camera);
	}
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}
}

void ScenePerspective::drawSkybox() {
	if (mSkybox) {
		CameraPerspective c = *(mCamera.get());
		mSkybox->draw(c);
	}
}

void ScenePerspective::drawPicking() {
	/* Parent-children transformations */
	CameraPerspective c = *(mCamera.get());
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
} /* fillwave */
