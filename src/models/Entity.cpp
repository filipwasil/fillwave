/*
 * Entity.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/models/Entity.h>

#include <fillwave/extras/Log.h>

#include <algorithm>

FLOGINIT("Entity", FERROR | FFATAL)

namespace fillwave {
namespace models {

Entity::Entity(glm::vec3 translation, glm::quat rotation)
		:
				Moveable(translation, rotation),
				mChildrenPropagateEvent(GL_TRUE),
				mParentRefresh(GL_TRUE),
				mPSC(GL_TRUE),
				mPSR(GL_TRUE),
				mRefreshExternal(GL_TRUE),
				mPickable(GL_FALSE) {

}

Entity::~Entity() {
	detachChildren();
	FLOG_DEBUG("Entity destroyed");
}

void Entity::attach(pEntity child) {
	mChildren.push_back(child);
	child->onAttached(this);
}

void Entity::detach(pEntity child) {
	auto _compare_function =
			[child](const pEntity e) -> bool {bool found = (e == child); if (found) child->onDetached(); return found;};
	auto _begin = mChildren.begin();
	auto _end = mChildren.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	mChildren.erase(it, _end);
}

void Entity::onAttached(Entity*) {
	FLOG_DEBUG("Attached enity");
}

void Entity::onDetached() {
	FLOG_DEBUG("Detached enity");
}

void Entity::draw(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();
	for (auto& it : mChildren) {
		it->draw(camera);
	}
}

void Entity::drawDR(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}
}

void Entity::drawPicking(space::Camera& camera) {
	for (auto& it : mChildren) {
		it->drawPicking(camera);
	}
}

void Entity::drawDepth(space::Camera& camera) {
	for (auto& it : mChildren) {
		it->drawDepth(camera);
	}
}

void Entity::drawDepthColor(space::Camera& camera, glm::vec3& position) {
	for (auto& it : mChildren) {
		it->drawDepthColor(camera, position);
	}
}

void Entity::drawAOG(space::Camera& camera) {
	for (auto& it : mChildren) {
		it->drawAOG(camera);
	}
}

void Entity::drawAOC(space::Camera& camera) {
	for (auto& it : mChildren) {
		it->drawAOC(camera);
	}
}

void Entity::drawOcclusionBox(space::Camera& camera) {
	for (auto& it : mChildren) {
		it->drawOcclusionBox(camera);
	}
}

void Entity::onPicked() {

}

void Entity::onUnpicked() {

}

void Entity::updateMatrixTree() {
	if (mRefresh) {
		updateMatrixCache();
		mParentRefresh = GL_TRUE;
		mRefresh = GL_FALSE;
	}

	if (mParentRefresh) {
		mTransformation = mParentMatrix * mModelMatrixCache;
		for (auto& it : mChildren) {
			it->updateParentMatrix(mTransformation);
		}
		mRefreshExternal = GL_TRUE;
		mParentRefresh = GL_FALSE;
	}
}

void Entity::handleHierarchyEvent(actions::EventType* event) {
	handleEvent(mCallbacksHierarchy, event);
	if (mChildrenPropagateEvent) {
		std::for_each(mChildren.begin(), mChildren.end(),
				[event](pEntity e) {e->handleHierarchyEvent(event);});
	}
}

void Entity::handlePrivateEvent(actions::EventType* event) {
	handleEvent(mCallbacksPrivate, event);
}

void Entity::setTransformation(glm::mat4 modelMatrix) {
	mModelMatrixCache = modelMatrix;
	mTransformation = mParentMatrix * mModelMatrixCache;
	for (auto& it : mChildren) {
		it->updateParentMatrix(mTransformation);
	}
	mRefreshExternal = GL_TRUE;
}

glm::mat4 Entity::getTransformation() {
	return mTransformation;
}

glm::mat4 Entity::getParentMatrix() {
	return mParentMatrix;
}

glm::quat Entity::getParentRotation() {
	return mParentRotation;
}

void Entity::updateParentMatrix(glm::mat4& parent) {
	mParentMatrix = parent;
	mTransformation = mParentMatrix * mModelMatrixCache;
	for (auto& it : mChildren) {
		it->updateParentMatrix(mTransformation);
	}
//   std::for_each(mChildren.begin(), mChildren.end(), [localTransformation](pEntity e){ e->updateParentMatrix(mTransformation); });
	mParentRefresh = GL_FALSE;
	mRefreshExternal = GL_TRUE;
}

void Entity::updateParentRotation(glm::quat& parent) {
	mParentRotation = parent;
	glm::quat localRotation(mParentRotation * mRotation);
	for (auto& it : mChildren) {
		it->updateParentRotation(localRotation);
	}
	mRefreshExternal = GL_TRUE;
}

void Entity::attachHierarchyCallback(actions::ItemCallback* callback) {
	mCallbacksHierarchy.push_back(callback);
}

void Entity::attachPrivateCallback(actions::ItemCallback* callback) {
	mCallbacksPrivate.push_back(callback);
}

void Entity::detachHierarchyCallback(actions::ItemCallback* callback) {
	detachCallback(mCallbacksHierarchy, callback);
}

void Entity::detachPrivateCallback(actions::ItemCallback* callback) {
	detachCallback(mCallbacksPrivate, callback);
}

void Entity::pick(glm::vec3 color) {
	mPickable = GL_TRUE;
	mPickColor = color;
	std::for_each(mChildren.begin(), mChildren.end(),
			[color](pEntity e) {e->pick(color);});
}

void Entity::unpick() {
	mPickable = GL_FALSE;
	std::for_each(mChildren.begin(), mChildren.end(),
			[](pEntity e) {e->unpick();});
}

GLboolean Entity::isPickable() {
	return mPickable;
}

GLboolean Entity::isExternalRefresh() {
	return mRefreshExternal;
}

void Entity::setExternalRefresh(GLboolean state) {
	mRefreshExternal = state;
}

GLboolean Entity::isPSC() {
	return mPSC;
}

GLboolean Entity::isPSR() {
	return mPSR;
}

//void Entity::setPSR(GLboolean value) {
//   mPSR = value;
//}

glm::vec3 Entity::getPickableColor() {
	return mPickColor;
}

void Entity::log() {

}

/* Private inline */

inline void Entity::detachChildren() {
	Entity* _this = this;
	std::for_each(mChildren.begin(), mChildren.end(),
			[_this](pEntity e) {_this->detach(e);});
}

inline void Entity::handleEvent(
		std::vector<actions::ItemCallback*>& callbacks,
		actions::EventType* event) {
	for (auto it : callbacks) {
		if (it->isEnabled()) {
			if (it->getSupportedEventType() == event->getType()) {
				it->perform(event);
			}
		}
	}
	eraseFinishedCallbacks(callbacks);
}

inline void Entity::eraseFinishedCallbacks(
		std::vector<actions::ItemCallback*>& callbacks) {
	auto _find_finished_function =
			[](actions::ItemCallback* m) -> bool {bool finished = m->isFinished(); if (finished) delete m; return finished;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _find_finished_function);
	callbacks.erase(it, _end);
}

inline void Entity::detachCallback(
		std::vector<actions::ItemCallback*>& callbacks,
		actions::ItemCallback* callback) {
	auto _compare_function =
			[callback](const actions::ItemCallback* m) -> bool {bool found = (m == callback); if (found) delete m; return found;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	callbacks.erase(it, _end);
	FLOG_ERROR("Detachment of callback failed");
}

} /* models */
} /* fillwave */
