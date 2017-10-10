/*
 * Entity.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/models/Entity.h>

namespace flw {
namespace flf {

Entity::Entity()
    : mChildrenPropagateEvent(GL_TRUE)
    , mParentRefresh(GL_TRUE)
    , mPSC(GL_TRUE)
    , mPSR(GL_TRUE) {
  // nothing
}

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
  if (event.getType() == eEventType::time) {
    for (auto &handler : mEventHandlers) {
      handler(event);
    }
  }

  for (auto &handler : mEventHandlers) {
    handler(event);
  }

  for (auto &child : mChildren) {
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
  std::for_each(mChildren.begin(), mChildren.end(), [color](puEntity &e) {
    e->pick(color);
  });
}

void Entity::unpick() {
  mFlagPickable = false;
  std::for_each(mChildren.begin(), mChildren.end(), [](puEntity &e) {
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

void Entity::attachHandler(EventHandler&& h) {
  mEventHandlers.push_back(h);
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
