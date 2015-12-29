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
		: mCamera(camera) {

}

void ScenePerspective::draw() {
	mCamera->update();
	space::CameraPerspective c = *(mCamera.get());
	for (auto& it : mChildren) {
		it->draw(c);
	}
}

void ScenePerspective::drawPBRP() {
	space::CameraPerspective c = *(mCamera.get());
	for (auto& program : mRenderPasses) {
		core::Program::useProgram(program.first);
		for (auto& node : program.second) {
			node->draw(c );
		}
		core::Program::disusePrograms();
	}
}

void ScenePerspective::draw(space::CameraPerspective& camera) {
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

void ScenePerspective::drawDR(space::CameraPerspective& camera) {
	if (mSkybox) {
		mSkybox->drawDR(camera);
	}
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
