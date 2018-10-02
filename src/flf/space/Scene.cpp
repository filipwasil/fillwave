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

#include <flw/flf/space/Scene.h>
#include <flw/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FUSER)

namespace flw {
namespace flf {

Scene::Scene(flc::IRenderer* renderer)
  : mSkybox(nullptr)
  , mCursor(nullptr)
  , mHeadUpDisplay(nullptr)
  , mRenderer(renderer)
  , mCamera(nullptr)
  , mLastPicked(nullptr)
  , mCurrentPicableColor(0)
  , mAmbientGlobal(glm::vec3(1.0)) {
  // nothing
}

Scene::~Scene() = default;

void Scene::setRenderer(flc::IRenderer* renderer) {
  mRenderer = std::unique_ptr<flc::IRenderer>(renderer);
}

void Scene::setSkybox(pu<Skybox>&& skybox) {
  mSkybox = std::move(skybox);
}

void Scene::setCursor(pu<Cursor>&& cursor) {
  mCursor = std::move(cursor);
}

void Scene::setHUD(pu<HUD>&& hud) {
  mHeadUpDisplay = std::move(hud);
}

void Scene::setAmbient(glm::vec3 ambient) {
  mAmbientGlobal = ambient;
}

pp<Cursor> Scene::getCursor() {
  return pp<Cursor>(mCursor.get());
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
  glm::ivec3 nextColor(
    mCurrentPicableColor % 256
    , (mCurrentPicableColor / 256) % 256
    , (mCurrentPicableColor / ( 256 * 256) )  % 256);

  glm::vec3 color(nextColor.r / 256.0f, nextColor.g / 256.0f, nextColor.b / 256.0f);

  fLogD("Assigned Picked color: ", color.r, " ", color.g, " ", color.b);

  mPickingTable[mCurrentPicableColor] = entity;

  entity->assignColor(color);

  mCurrentPicableColor+=1;
}

void Scene::pick(glm::ivec4 color) {

  GLint name = color.r * 256 * 256 + color.g * 256 + color.b;

  fLogD("Picked color:", " ", color.r, " ", color.g, " ", color.b, " Name: ", name);

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
    fLogI("Renderer waiting for update");
    mRenderer->mFlagReload = isAttachedDetached();
    return;
  }
  fLogI("Renderer update");
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

pp<ICamera> Scene::getCamera() {
  return pp<ICamera>(mCamera.get());
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
  // nothing
}

void Scene::onHide() {
  // nothing
}

} /* flc */
} /* flw */
