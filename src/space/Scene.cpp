/*
 * Scene.cpp
 *
 *  Created on: May 2, 2014
 *      Author: filip
 */

#include <fillwave/space/Scene.h>

#include <algorithm>

FLOGINIT("Scene", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Scene::Scene()
		:
				mCursor(pCursor()),
				mSkybox(pSkybox()),
				mLastPicked(pEntity()),
				mAmbientGlobal(glm::vec3(1.0)) {
}

void Scene::setSkybox(pSkybox skybox) {
	mSkybox = skybox;
}

pCursor Scene::getCursor() {
	return mCursor;
}

void Scene::setCursor(pCursor cursor) {
	mCursor = cursor;
}

glm::vec3 Scene::getAmbient() {
	return mAmbientGlobal;
}

void Scene::setAmbient(glm::vec3 ambient) {
	mAmbientGlobal = ambient;
}

void Scene::moveCursor(glm::vec2 position) {
	if (mCursor) {
		mCursor->move(position);
	} else {
		FLOG_DEBUG("No cursor set");
	}
}

void Scene::drawFromCustomCamera(Camera& c) {
	/* Parent-children transformations */
	for (auto& it : mChildren) {
		it->draw(c);
	}
}

void Scene::drawCursor() {
	if (mCursor) {
		mCursor->draw();
	}
}

void Scene::registerPickable(pEntity entity) {
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

void Scene::updateRenderPasses() {
	mRenderPasses.clear();
	for (auto& it : mChildren) {
		it->updateRenderpass(mRenderPasses);
	}
}

void Scene::onShow() {

}

void Scene::onHide() {

}

} /* models */
} /* fillwave */
