/*
 * Entity.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/models/Entity.h>

#include <fillwave/Log.h>

#include <algorithm>

FLOGINIT("Entity", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Entity::Entity(glm::vec3 translation, glm::quat rotation)
		:
				Moveable(translation, rotation),
				mChildrenPropagateEvent(GL_TRUE),
				mParentRefresh(GL_TRUE),
				mPSC(GL_TRUE),
				mPSR(GL_TRUE),
				mFlagUpdateRenderPass(GL_TRUE),
				mPickable(GL_FALSE) {

}

Entity::~Entity() {
	FLOG_DEBUG("Entity destroyed");
}

void Entity::draw(ICamera& camera) {
	for (auto& it : mChildren) {
		it->draw(camera);
	}
}

void Entity::drawPBRP(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}
}

void Entity::drawDR(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawDR(camera);
	}
}

void Entity::drawPicking(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawPicking(camera);
	}
}

void Entity::drawDepth(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawDepth(camera);
	}
}

void Entity::drawDepthColor(ICamera& camera, glm::vec3& position) {
	for (auto& it : mChildren) {
		it->drawDepthColor(camera, position);
	}
}

void Entity::drawAOG(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawAOG(camera);
	}
}

void Entity::drawAOC(ICamera& camera) {
	for (auto& it : mChildren) {
		it->drawAOC(camera);
	}
}

void Entity::drawOcclusionBox(ICamera& camera) {
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
		mPhysicsMMC = mParentMMC * mMMC;
		for (auto& it : mChildren) {
			it->updateParentMatrix(mPhysicsMMC);
		}
		mRefreshExternal = GL_TRUE;
		mParentRefresh = GL_FALSE;
	}

	for (auto& it : mChildren) {
		it->updateMatrixTree();
	}
}

void Entity::handleHierarchyEvent(EventType& event) {
	handleEvent(mCallbacksHierarchy, event);
	for (auto& it : mChildren) {
		it->handleHierarchyEvent(event);
	}
}

void Entity::handlePrivateEvent(EventType& event) {
	handleEvent(mCallbacksPrivate, event);
}

void Entity::setTransformation(glm::mat4 modelMatrix) {
	mMMC = modelMatrix;
	mPhysicsMMC = mParentMMC * mMMC;
	for (auto& it : mChildren) {
		it->updateParentMatrix(mPhysicsMMC);
	}
	mRefreshExternal = GL_TRUE;
}

glm::mat4 Entity::getPhysicsMMC() {
	return mPhysicsMMC;
}

void Entity::updateParentMatrix(glm::mat4& parent) {
	mParentMMC = parent;
	mPhysicsMMC = mParentMMC * mMMC;
	mParentRefresh = GL_TRUE;
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

void Entity::updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpass) {
	for (auto& it : mChildren) {
		it->updateRenderpass(renderpass);
	}
}

void Entity::attachHierarchyCallback(Callback* callback) {
	mCallbacksHierarchy.push_back(callback);
}

void Entity::attachPrivateCallback(Callback* callback) {
	mCallbacksPrivate.push_back(callback);
}

void Entity::detachHierarchyCallback(Callback* callback) {
	detachCallback(mCallbacksHierarchy, callback);
}

void Entity::detachPrivateCallback(Callback* callback) {
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

void Entity::log() const {

}

inline void Entity::handleEvent( /* xxx refactor */
		std::vector<Callback*>& callbacks,
		EventType& event) {
	for (auto it : callbacks) {
		if (it->isEnabled()) {
			if (it->getEventType() == event.getType()) {
				it->perform(event);
			}
		}
	}
	eraseFinishedCallbacks(callbacks);
}

inline void Entity::eraseFinishedCallbacks(
		std::vector<Callback*>& callbacks) {
	auto _find_finished_function =
			[](Callback* m) -> bool {bool finished = m->isFinished(); if (finished) delete m; return finished;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _find_finished_function);
	callbacks.erase(it, _end);
}

inline void Entity::detachCallback(
		std::vector<Callback*>& callbacks,
		Callback* callback) {
	auto _compare_function =
			[callback](const Callback* m) -> bool {bool found = (m == callback); if (found) delete m; return found;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	callbacks.erase(it, _end);
	FLOG_ERROR("Detachment of callback failed");
}

} /* framework */
} /* fillwave */
