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

#include <fillwave/space/Scene.h>
#include <fillwave/Log.h>

FLOGINIT("Scene", FERROR | FFATAL)

namespace flw {
namespace flf {

Scene::Scene(IRenderer* renderer)
    : mRenderer(renderer)
    , mLastPicked(nullptr)
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
