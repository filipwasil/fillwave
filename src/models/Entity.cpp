/*
 * Entity.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 */

#include <fillwave/models/Entity.h>

#include <fillwave/Log.h>
#include <fillwave/common/Macros.h>
#include <fillwave/common/IFocusable.h>

FLOGINIT("Entity", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Entity::Entity(glm::vec3 translation, glm::quat rotation) :
	Moveable(translation, rotation),
	mChildrenPropagateEvent(GL_TRUE),
	mParentRefresh(GL_TRUE),
	mPSC(GL_TRUE),
	mPSR(GL_TRUE) {

}

Entity::~Entity() {
	FLOG_DEBUG("Entity destroyed");
}

bool Entity::isAnimated() const {
	return false;
}

void Entity::draw(ICamera& /*camera*/) {

}

void Entity::drawPBRP(ICamera& /*camera*/) {

}

void Entity::drawDR(ICamera& /*camera*/) {

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
		notifyObservers();
		mParentRefresh = GL_FALSE;
	}

	for (auto& it : mChildren) {
		it->updateMatrixTree();
	}
}

void Entity::handleHierarchyEvent(EventType& event) {
	Callback::handleEvent(mCallbacksHierarchy, event);
	for (auto& it : mChildren) {
		it->handleHierarchyEvent(event);
	}
}

void Entity::setTransformation(glm::mat4 modelMatrix) {
	mMMC = modelMatrix;
	mPhysicsMMC = mParentMMC * mMMC;
	for (auto& it : mChildren) {
		it->updateParentMatrix(mPhysicsMMC);
	}
	notifyObservers();
}

glm::mat4 Entity::getPhysicsMMC() {
	return mPhysicsMMC;
}

void Entity::updateParentMatrix(glm::mat4& parent) {
	mParentMMC = parent;
	mPhysicsMMC = mParentMMC * mMMC;
	mParentRefresh = GL_TRUE;
	notifyObservers();
}

void Entity::updateParentRotation(glm::quat& parent) {
	mParentRotation = parent;
	glm::quat localRotation(mParentRotation * mRotation);
	for (auto& it : mChildren) {
		it->updateParentRotation(localRotation);
	}
	notifyObservers();
}

void Entity::attachHierarchyCallback(puCallback&& callback) {
	mCallbacksHierarchy.push_back(std::move(callback));
}

void Entity::detachHierarchyCallback(Callback* callback) {
	detachCallback(mCallbacksHierarchy, callback);
}

void Entity::pick(glm::vec3 color) {
	mFlagPickable = true;
	mPickColor = color;
	std::for_each(mChildren.begin(), mChildren.end(),
	[color](puEntity & e) {
		e->pick(color);
	});
}

void Entity::unpick() {
	mFlagPickable = false;
	std::for_each(mChildren.begin(), mChildren.end(),
	[](puEntity & e) {
		e->unpick();
	});
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

void Entity::log() const {

}

inline void Entity::detachCallback(
   std::vector<puCallback>& callbacks,
   Callback* callback) {
	auto _compare_function =
	   [callback](const puCallback & m) -> bool {return m.get() == callback;};
	auto _begin = callbacks.begin();
	auto _end = callbacks.end();
	auto it = std::remove_if(_begin, _end, _compare_function);
	callbacks.erase(it, _end);
	FLOG_ERROR("Detachment of callback failed");
}

void Entity::updateRenderer(IRenderer& renderer) {
	for (auto& it : mChildren) {
		it->updateRenderer(renderer);
	}
}

bool Entity::getRenderItem(RenderItem& /*item*/) {
	return false;
}

} /* framework */
puEntity buildEntity() {
	return framework::make_unique<framework::Entity>();
}
} /* fillwave */
