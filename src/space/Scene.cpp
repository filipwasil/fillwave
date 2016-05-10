/*
 * IScene.cpp
 *
 *  Created on: May 2, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/actions/events/ResizeScreenTEvent.h>
#include <fillwave/space/Scene.h>
#include <fillwave/renderers/RendererPBRP.h>
#include <fillwave/common/Macros.h>
#include <fillwave/Log.h>
#include <algorithm>

FLOGINIT("Scene", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Scene::Scene(IRenderer* renderer) :
	mAmbientGlobal(glm::vec3(1.0)), mRenderer(renderer) {
}

void Scene::setRenderer(IRenderer* renderer) {
	mRenderer = std::unique_ptr < IRenderer > (renderer);
}

void Scene::setSkybox(puSkybox&& skybox) {
	mSkybox = std::move(skybox);
}

void Scene::setCursor(puCursor&& cursor) {
	mCursor = std::move(cursor);
}

void Scene::setHUD(pHUD& hud) {
	mHUD = hud;
}



void Scene::setAmbient(glm::vec3 ambient) {
	mAmbientGlobal = ambient;
}

Cursor* Scene::getCursor() {
	return mCursor.get();
}

void Scene::moveCursor(glm::vec2 position) {
	if (mCursor) {
		mCursor->move(position);
	} else {
		FLOG_DEBUG("No cursor set");
	}
}

void Scene::updateDependencies() {
	for (auto& it : mChildren) {
		it->updateMatrixTree();
	}
}

void Scene::draw(ICamera& camera) {
	camera.update();
	mRenderer->draw(camera);
}

void Scene::drawHUD() {
	if (mHUD) {
		mHUD->draw();
	}
}

void Scene::drawCursor() {
	if (mCursor) {
		mCursor->draw();
	}
}

void Scene::drawDepth(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawDepth(camera);
	}
}

void Scene::drawDepthColor(ICamera& camera, glm::vec3& position) {
	for (auto& it : mChildren) {
		it->drawDepthColor(camera, position);
	}
}

void Scene::registerPickable(Entity* entity) {
	GLint rand_r, rand_g, rand_b;
	glm::vec3 color;

	for (GLint i = 0; i < MAXIMUM_TRIALS_TO_PICK_COLOR; i++) {

		rand_r = (GLfloat) (rand() % 256);
		rand_g = (GLfloat) (rand() % 256);
		rand_b = (GLfloat) (rand() % 256);

		color = glm::vec3(rand_r / 255.0, rand_g / 255.0, rand_b / 255.0);
		GLint name = (GLint) (rand_r) + (GLint) (rand_g) + (GLint) (rand_b);

		auto it = mPickingTable.find(name);
		if (it == mPickingTable.end()) {
			mPickingTable[name] = entity;
			entity->pick(color);
			return;
		}
	}
	FLOG_ERROR("Failed to register pickable entity");
}

void Scene::pick(glm::ivec4 color) {
	GLint name = color.r + color.g + color.b;
	if (mPickingTable[name]) {
		mPickingTable[name]->onPicked();
		if (mLastPicked) {
			mLastPicked->onUnpicked();
		}
		mLastPicked = mPickingTable[name];
	}
}

void Scene::updateRenderer() {
	if (mRenderer->mFlagReload) {
		FLOG_DEBUG("Renderer update");
		mRenderer->clear();
		if (mSkybox) {
			mRenderer->mSkybox = mSkybox.get();
		} else {
			mRenderer->mSkybox = nullptr;
		}
		for (auto& it : mChildren) {
			it->updateRenderer(*(mRenderer.get()));
		}
		mRenderer->mFlagReload = false;
	} else {
		FLOG_DEBUG("Renderer waiting for update");
		mRenderer->mFlagReload = isAttachedDetached();
	}
}

void Scene::resetRenderer(GLuint screenWidth, GLuint screenHeight) {
	mRenderer->clear();
	mRenderer->reset(screenWidth, screenHeight);
}

void Scene::draw() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void Scene::drawPicking() {
	for (auto& it : mChildren) {
		it->drawPicking(*(mCamera.get()));
	}
}

void Scene::drawDepthInt() {
	for (auto& it : mChildren) {
		it->drawDepth(*(mCamera.get()));
	}
}

void Scene::drawOcclusion() {
	for (auto& it : mChildren) {
		it->drawOcclusionBox(*(mCamera.get()));
	}
}

void Scene::setCamera(puICamera&& camera) {
	mCamera = std::move(camera);
}

ICamera* Scene::getCamera() {
	return mCamera.get();
}

void Scene::onEvent(EventType& event) {
	for (auto& it : mChildren) {
		it->handleHierarchyEvent(event);
	}
}

void Scene::onShow() {

}

void Scene::onHide() {

}

} /* models */
} /* fillwave */
