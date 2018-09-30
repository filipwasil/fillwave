#pragma once

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

#include <flw/flf/hud/base/HUD.h>
#include <flw/flf/models/Entity.h>
#include <flw/flf/models/Skybox.h>
#include <flw/flf/models/Cursor.h>
#include <flw/flc/renderers/mRendererFR.h>
#include <flw/cmn/pointers/PointerProtected.h>

#include <unordered_map>

namespace flw {
namespace flf {

/*! \class Scene
 * \brief Entity to be a root of Entity tree.
 */

class Scene : public TreePtr<Entity> {
public:
  Scene(flc::IRenderer* renderer = new flc::RendererFR());

  ~Scene() override;

  void updateDependencies();

  void updateRenderer();

  void setRenderer(flc::IRenderer *renderer);

  void resetRenderer(GLuint screenWidth, GLuint screenHeight);

  /* Cursor */
  pp<Cursor> getCursor();

  void setCursor(pu<Cursor>&& cursor);

  void drawCursor();

  /* Camera */
  pp<ICamera> getCamera();

  void setCamera(pu<ICamera>&& camera);

  /* Scene */
  void setSkybox(pu<Skybox>&& skybox);

  void setHUD(pu<HUD>&& hud);

  void setAmbient(glm::vec3 cursor);

  /* Pickable */
  void registerPickable(Entity* entity);

  void pick(glm::ivec4 color);

  /* Events */
  void onEvent(const Event& event);

  void stepInTime(float timePassedInSeconds);

  void draw(ICamera& c);

  void drawHUD();

  void drawDepth(ICamera& camera);

  void drawDepthColor(ICamera& camera, glm::vec3& position);

  /* Draw */
  void draw();

  void drawDepthInt();

  void drawPicking();

  void drawOcclusion();

  /* Interface */
  virtual void onShow();
  virtual void onHide();

protected:
  pu<Skybox> mSkybox;
  pu<Cursor> mCursor;
  pu<HUD> mHeadUpDisplay;
  pu<flc::IRenderer> mRenderer;
  pu<ICamera> mCamera;

  std::unordered_map<GLint, Entity* > mPickingTable;
  Entity* mLastPicked;
  GLint mCurrentPicableColor;
  glm::vec3 mAmbientGlobal;
};

} /* flf */
} /* flw */

