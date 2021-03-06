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

#include <flw/flc/renderers/RenderItem.h>
#include <flw/cmn/scene/ICamera.h>

namespace flw {
namespace flc {

class IRenderer;

/*! \class IRenderable
 * \brief Encapsulates renderable objects. To be used with IRenderer.
 */

class IRenderable {
public:
  IRenderable();

  virtual ~IRenderable();

  IRenderable &operator=(const IRenderable&) = delete;

  IRenderable(const IRenderable&) = delete;

  IRenderable& operator=(IRenderable&&);

  IRenderable(IRenderable&&);

  virtual void drawFR(ICamera &camera) = 0;

  virtual void drawPBRP(ICamera &camera) = 0;

  virtual void drawDR(ICamera &camera) = 0;

  virtual void drawDepth(ICamera &camera) = 0;

  virtual void drawDepthColor(ICamera &camera, glm::vec3 &position) = 0;

  virtual void drawAOG(ICamera &camera) = 0;

  virtual void drawAOC(ICamera &camera) = 0;

  virtual void drawOcclusionBox(ICamera &camera) = 0;

  virtual void drawPicking(ICamera &camera) = 0;

  virtual bool getRenderItem(RenderItem& item) = 0;

  virtual void updateRenderer(IRenderer& renderer) = 0;
};

} /* flc */
} /* flw */
