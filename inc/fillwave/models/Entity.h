#pragma once

/*
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

#include <fillwave/common/IPickable.h>
#include <fillwave/space/base/ICamera.h>
#include <fillwave/models/base/IRenderable.h>
#include <fillwave/models/base/Moveable.h>
#include <fillwave/models/base/TreePtr.h>
#include <fillwave/actions/Event.h>

namespace flw {
namespace flf {

class Entity;
}

namespace flc {
class Program;
}

typedef std::unique_ptr<flf::Entity> puEntity;

namespace flf {

/*! \class Entity
 * \brief Base for all Scene nodes.
 */

class Entity : public IRenderable, public IPickable, public Moveable, public TreePtr<Entity> {
public:
  Entity();

  ~Entity() override = default;

  Entity &operator=(const Entity &) = default;

  Entity(const Entity &) = default;

  Entity &operator=(Entity &&) = default;

  Entity(Entity &&obj) = default;

  /* Flags */
  bool isPSC();

  bool isPSR();

  /* Callbacks */
  void handleEvent(const Event& event);

  /* Model */
  glm::mat4 getPhysicsMMC();

  /* Physics */
  void setTransformation(glm::mat4 modelMatrix);

  /* Callbacks */
  void attachHandler(EventHandler&& h);

  void detachHandlers();

  /* Parent */
  void updateMatrixTree();

  void updateParentMatrix(glm::mat4 &parent);

  void updateParentRotation(glm::quat &rotation);

  /* IPickable */
  void pick(glm::vec3 color) override;

  void unpick() override;

  void stepInTime(float timeSinceLastFrameInSeconds);

  virtual void onPicked() override;

  virtual void onUnpicked() override;

  /* IDrawable */
  virtual void draw(ICamera &camera) override;

  virtual void drawPBRP(ICamera &camera) override;

  virtual void drawDR(ICamera &camera) override;

  virtual void drawDepth(ICamera &camera) override;

  virtual void drawDepthColor(ICamera &camera, glm::vec3 &position) override;

  virtual void drawAOG(ICamera &camera) override;

  virtual void drawAOC(ICamera &camera) override;

  virtual void drawOcclusionBox(ICamera &camera) override;

  virtual void drawPicking(ICamera &camera) override;

  /* IRenderable */
  virtual void updateRenderer(IRenderer &renderer) override;

  virtual bool getRenderItem(RenderItem &item) override;

  /* Animations */
  virtual bool isAnimated() const;

  /* Log */
  virtual void log() const;

protected:
  /* MMC - Model Matrix Cache */
  glm::mat4 mPhysicsMMC;

  GLboolean mChildrenPropagateEvent;
  GLboolean mParentRefresh;
  vec<EventHandler> mEventHandlers;

  GLboolean mPSC;
  GLboolean mPSR;
};

} /* flf */
} /* flw */
