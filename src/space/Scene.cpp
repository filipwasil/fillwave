/*
 * IScene.cpp
 *
 *  Created on: May 2, 2014
 *      Author: filip
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

#include <fillwave/space/Scene.h>
#include <fillwave/Log.h>

FLOGINIT("Scene", FERROR | FFATAL)

namespace flw {
namespace flf {

Scene::Scene(IRenderer* renderer)
    : mRenderer(renderer)
    , mAmbientGlobal(glm::vec3(1.0)) {
}

void Scene::setRenderer(IRenderer *renderer) {
  mRenderer = std::unique_ptr<IRenderer>(renderer);
}

void Scene::setSkybox(pu<Skybox>&& skybox) {
  mSkybox = std::move(skybox);
}

void Scene::setCursor(pu<Cursor>&& cursor) {
  mCursor = std::move(cursor);
}

void Scene::setHUD(pu<HUD> hud) {
  mHeadUpDisplay = std::move(hud);
}

void Scene::setAmbient(glm::vec3 ambient) {
  mAmbientGlobal = ambient;
}

TGetter<Cursor> Scene::getCursor() {
  return TGetter<Cursor>(mCursor.get());
}

void Scene::updateDependencies() {
  for (auto &it : mChildren) {
    it->updateMatrixTree();
  }
}

void Scene::draw(ICamera &camera) {
  camera.update();
  mRenderer->draw(camera);
}

void Scene::drawHUD() {
  if (mHeadUpDisplay) {
    mHeadUpDisplay->draw();
  }
}

void Scene::drawCursor() {
  if (mCursor) {
    mCursor->redraw();
  }
}

void Scene::drawDepth(ICamera &camera) {
  for (auto &it : mChildren) {
    it->drawDepth(camera);
  }
}

void Scene::drawDepthColor(ICamera &camera, glm::vec3 &position) {
  for (auto &it : mChildren) {
    it->drawDepthColor(camera, position);
  }
}

void Scene::registerPickable(Entity* entity) {
  GLint rand_r, rand_g, rand_b;
  glm::vec3 color;

  for (GLint i = 0; i < MAXIMUM_TRIALS_TO_PICK_COLOR; ++i) {

    rand_r = rand() % 256;
    rand_g = rand() % 256;
    rand_b = rand() % 256;

    color = glm::vec3(rand_r / 255.0, rand_g / 255.0, rand_b / 255.0);
    GLint name = (GLint) (rand_r) + (GLint) (rand_g) + (GLint) (rand_b);

    auto it = mPickingTable.find(name);
    if (it == mPickingTable.end()) {
      mPickingTable[name] = entity;
      entity->pick(color);
      return;
    }
  }
  fLogE("Failed to register pickable entity");
}

void Scene::pick(glm::ivec4 color) {
  GLint name = color.r + color.g + color.b;
  if (!mPickingTable[name]) {
    return;
  }

  mPickingTable[name]->onPicked();
  if (mLastPicked) {
    mLastPicked->onUnpicked();
  }
  mLastPicked = mPickingTable[name];
}

void Scene::updateRenderer() {
  if (!mRenderer->mFlagReload) {
    fLogD("Renderer waiting for update");
    mRenderer->mFlagReload = isAttachedDetached();
    return;
  }
  fLogD("Renderer update");
  mRenderer->clear();
  mRenderer->mSkybox = mSkybox ? mSkybox.get() : nullptr;
  for (auto &it : mChildren) {
    it->updateRenderer(*(mRenderer.get()));
  }
  mRenderer->mFlagReload = false;
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
  for (auto &it : mChildren) {
    it->drawPicking(*(mCamera.get()));
  }
}

void Scene::drawDepthInt() {
  for (auto &it : mChildren) {
    it->drawDepth(*(mCamera.get()));
  }
}

void Scene::drawOcclusion() {
  for (auto &it : mChildren) {
    it->drawOcclusionBox(*(mCamera.get()));
  }
}

void Scene::setCamera(pu<ICamera> &&camera) {
  mCamera = std::move(camera);
}

TGetter<ICamera> Scene::getCamera() {
  return TGetter<ICamera>(mCamera.get());
}

void Scene::onEvent(const Event& event) {
  for (auto &it : mChildren) {
    it->handleEvent(event);
  }
}

void Scene::stepInTime(float timePassedInSeconds) {
  for (auto& it : mChildren) {
    it->stepInTime(timePassedInSeconds);
  }
}

void Scene::onShow() {

}

void Scene::onHide() {

}

} /* models */
} /* flw */
