/*
 * Scene.cpp
 *
 *  Created on: May 2, 2014
 *      Author: filip
 */

#include <fillwave/space/base/IScene.h>
#include <fillwave/renderers/RendererPBRP.h>

#include <algorithm>

FLOGINIT("Scene", FERROR | FFATAL)

namespace fillwave {
namespace framework {

IScene::IScene()
		: mAmbientGlobal(glm::vec3(1.0)),
		  mRenderer(new RendererPBRP()) {
}

void IScene::setSkybox(pSkybox skybox) {
	mSkybox = skybox;
}

pCursor IScene::getCursor() {
	return mCursor;
}

void IScene::setCursor(pCursor cursor) {
	mCursor = cursor;
}

glm::vec3 IScene::getAmbient() {
	return mAmbientGlobal;
}

void IScene::setAmbient(glm::vec3 ambient) {
	mAmbientGlobal = ambient;
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

void IScene::draw(ICamera& c) {
	for (auto& it : mChildren) {
		it->draw(c);
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

void IScene::registerPickable(pEntity entity) {
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
	if (mRenderer->getRefresh()) {
		mRenderer->reset();
		for (auto& it : mChildren) {
			it->updateRenderer(*(mRenderer.get()));
		}
		mRenderer->setRefresh(false);
	}
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
