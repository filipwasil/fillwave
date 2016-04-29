/*
 * IScene.cpp
 *
 *  Created on: May 2, 2014
 *      Author: filip
 */

#include <fillwave/actions/events/ResizeScreenTEvent.h>
#include <fillwave/space/base/IScene.h>
#include <fillwave/renderers/RendererPBRP.h>
#include <fillwave/common/Macros.h>
#include <fillwave/Log.h>
#include <algorithm>

FLOGINIT("Scene", FERROR | FFATAL)

namespace fillwave {
namespace framework {

IScene::IScene(IRenderer* renderer) :
	mAmbientGlobal(glm::vec3(1.0)), mRenderer(renderer) {
}

void IScene::setRenderer(IRenderer* renderer) {
	mRenderer = std::unique_ptr < IRenderer > (renderer);
}

void IScene::setSkybox(pSkybox& skybox) {
	mSkybox = skybox;
}

void IScene::setHUD(pHUD& hud) {
	mHUD = hud;
}

void IScene::setCursor(pCursor& cursor) {
	mCursor = cursor;
}

void IScene::setAmbient(glm::vec3 ambient) {
	mAmbientGlobal = ambient;
}

pCursor IScene::getCursor() {
	return mCursor;
}

void IScene::moveCursor(glm::vec2 position) {
	if (mCursor) {
		mCursor->move(position);
	} else {
		FLOG_DEBUG("No cursor set");
	}
}

void IScene::updateDependencies() {
	for (auto& it : mChildren) {
		it->updateMatrixTree();
	}
}

void IScene::draw(ICamera& camera) {
	camera.update();
	mRenderer->draw(camera);
}

void IScene::drawHUD() {
	if (mHUD) {
		mHUD->draw();
	}
}

void IScene::drawCursor() {
	if (mCursor) {
		mCursor->draw();
	}
}

void IScene::drawDepth(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawDepth(camera);
	}
}

void IScene::drawDepthColor(ICamera& camera, glm::vec3& position) {
	for (auto& it : mChildren) {
		it->drawDepthColor(camera, position);
	}
}

void IScene::registerPickable(Entity* entity) {
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

void IScene::pick(glm::ivec4 color) {
	GLint name = color.r + color.g + color.b;
	if (mPickingTable[name]) {
		mPickingTable[name]->onPicked();
		if (mLastPicked) {
			mLastPicked->onUnpicked();
		}
		mLastPicked = mPickingTable[name];
	}
}

void IScene::updateRenderer() {
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

void IScene::resetRenderer(GLuint screenWidth, GLuint screenHeight) {
	mRenderer->clear();
	mRenderer->reset(screenWidth, screenHeight);
}

void IScene::draw() {
	mCamera->update();
	mRenderer->draw(*(mCamera.get()));
}

void IScene::drawPicking() {
	for (auto& it : mChildren) {
		it->drawPicking(*(mCamera.get()));
	}
}

void IScene::drawDepthInt() {
	for (auto& it : mChildren) {
		it->drawDepth(*(mCamera.get()));
	}
}

void IScene::drawOcclusion() {
	for (auto& it : mChildren) {
		it->drawOcclusionBox(*(mCamera.get()));
	}
}

void IScene::setCamera(puICamera&& camera) {
	mCamera = std::move(camera);
}

ICamera* IScene::getCamera() {
	return mCamera.get();
}

void IScene::onEvent(EventType& event) {
	for (auto& it : mChildren) {
		it->handleHierarchyEvent(event);
	}
}

void IScene::onShow() {

}

void IScene::onHide() {

}

} /* models */
} /* fillwave */
