/*
 * SceneOrthographic.cpp
 *
 *  Created on: 6 May 2015
 *      Author: Filip Wasil
 */

#include <fillwave/space/SceneOrthographic.h>
#include <algorithm>

namespace fillwave {
namespace framework {

SceneOrthographic::SceneOrthographic(pCameraOrthographic camera)
		: mCamera(camera) {

}

void SceneOrthographic::draw() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void SceneOrthographic::drawDR() {
	if (mSkybox) {
		mSkybox->drawDR(*(mCamera.get()));
	}
	mCamera->update();
	for (auto& it : mChildren) {
		it->drawDR(*(mCamera.get()));
	}
}

void SceneOrthographic::draw(ICamera& camera) {
	for (auto& it : mChildren) {
		it->draw(camera);
	}
}

void SceneOrthographic::drawDR(ICamera& camera) {
	if (mSkybox) {
		mSkybox->drawDR(camera);
	}
	for (auto& it : mChildren) {
		it->draw(camera);
	}
}

void SceneOrthographic::drawPicking() {
	for (auto& it : mChildren) {
		it->drawPicking(*(mCamera.get()));
	}
}

void SceneOrthographic::drawSkybox() {
	if (mSkybox) {
		mSkybox->draw(*(mCamera.get()));
	}
}

void SceneOrthographic::drawDepthInt() {
	for (auto& it : mChildren) {
		it->drawDepth(*(mCamera.get()));
	}
}

void SceneOrthographic::drawAOG() {
	for (auto& it : mChildren) {
		it->drawAOG(*(mCamera.get()));
	}
}

void SceneOrthographic::drawAOC() {
	for (auto& it : mChildren) {
		it->drawAOC(*(mCamera.get()));
	}
}

void SceneOrthographic::drawOcclusion() {
	for (auto& it : mChildren) {
		it->drawOcclusionBox(*(mCamera.get()));
	}
}

void SceneOrthographic::setCamera(pCameraOrthographic camera) {
	mCamera = camera;
}

pICamera SceneOrthographic::getCamera() {
	return mCamera;
}

} /* framework */
} /* fillwave */
