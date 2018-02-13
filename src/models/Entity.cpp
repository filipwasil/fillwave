/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "fillwave/models/Entity.h"
#include "fillwave/actions/EventHandler.h"

namespace flw {
namespace flf {

Entity::Entity()
    : mChildrenPropagateEvent(GL_TRUE)
    , mParentRefresh(GL_TRUE)
    , mPSC(GL_TRUE)
    , mPSR(GL_TRUE) {
  // nothing
}

Entity::~Entity() {
  // nothing
}

Entity& Entity::operator=(Entity &&) = default;

Entity::Entity(Entity&& ) = default;

bool Entity::isAnimated() const {
  return false;
}

void Entity::draw(ICamera & /*camera*/) {
  // nothing
}

void Entity::drawPBRP(ICamera & /*camera*/) {
  // nothing
}

void Entity::drawDR(ICamera & /*camera*/) {
  // nothing
}

void Entity::drawPicking(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawPicking(camera);
  }
}

void Entity::drawDepth(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawDepth(camera);
  }
}

void Entity::drawDepthColor(ICamera &camera, glm::vec3 &position) {
  for (auto &it : mChildren) {
    it->drawDepthColor(camera, position);
  }
}

void Entity::drawAOG(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawAOG(camera);
  }
}

void Entity::drawAOC(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawAOC(camera);
  }
}

void Entity::drawOcclusionBox(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawOcclusionBox(camera);
  }
}

void Entity::onPicked() {
  // nothing
}

void Entity::onUnpicked() {
  // nothing
}

void Entity::updateMatrixTree() {
  if (mRefresh) {
    updateMatrixCache();
    mParentRefresh = GL_TRUE;
    mRefresh = GL_FALSE;
  }

  if (mParentRefresh) {
    mPhysicsMMC = mParentMMC * mMMC;
    for (auto &it : mChildren) {
      it->updateParentMatrix(mPhysicsMMC);
    }
    notifyObservers();
    mParentRefresh = GL_FALSE;
  }

  for (auto &it : mChildren) {
    it->updateMatrixTree();
  }
}

void Entity::handleEvent(const Event& event) {
  for (auto& handler : mEventHandlers) {
    handler.handle(event);
  }
  for (auto& child : mChildren) {
    child->handleEvent(event);
  }
}

void Entity::setTransformation(glm::mat4 modelMatrix) {
  mMMC = modelMatrix;
  mPhysicsMMC = mParentMMC * mMMC;
  for (auto &it : mChildren) {
    it->updateParentMatrix(mPhysicsMMC);
  }
  notifyObservers();
}

glm::mat4 Entity::getPhysicsMMC() {
  return mPhysicsMMC;
}

void Entity::updateParentMatrix(glm::mat4 &parent) {
  mParentMMC = parent;
  mPhysicsMMC = mParentMMC * mMMC;
  mParentRefresh = GL_TRUE;
  notifyObservers();
}

void Entity::updateParentRotation(glm::quat &parent) {
  mParentRotation = parent;
  glm::quat localRotation(mParentRotation *mRotation);
  for (auto &it : mChildren) {
    it->updateParentRotation(localRotation);
  }
  notifyObservers();
}

void Entity::pick(glm::vec3 color) {
  mFlagPickable = true;
  mPickColor = color;
  std::for_each(mChildren.begin(), mChildren.end(), [color](pu<Entity>& e) {
    e->pick(color);
  });
}

void Entity::unpick() {
  mFlagPickable = false;
  std::for_each(mChildren.begin(), mChildren.end(), [](pu<Entity> &e) {
    e->unpick();
  });
}

bool Entity::isPSC() {
  return mPSC;
}

bool Entity::isPSR() {
  return mPSR;
}

void Entity::log() const {
  // nothing
}

void Entity::updateRenderer(IRenderer &renderer) {
  for (auto &it : mChildren) {
      it->updateRenderer(renderer);
  }
}

bool Entity::getRenderItem(RenderItem & /*item*/) {
  return false;
}

void Entity::attachHandler(std::function<void(const Event&)>&& h, EEventType eventType) {
  mEventHandlers.emplace_back(eventType, h);
}

void Entity::detachHandlers() {
  mEventHandlers.clear();
}

void Entity::stepInTime(float timeSinceLastFrameInSeconds) {
  Moveable::stepInTime(timeSinceLastFrameInSeconds);
  for (auto &it : mChildren) {
    it->stepInTime(timeSinceLastFrameInSeconds);
  }
}

} /* flf */
} /* flw */
