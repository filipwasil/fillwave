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

#include <flw/flc/buffers/mVertexBufferDebug.h>
#include <flw/flf/models/base/IReloadable.h>
#include <flw/cmn/scene/ICamera.h>

namespace flw {
namespace flc {
class FramebufferGeometry;
}

enum class EDebuggerState {
  lightsSpot
  , lightsSpotColor
  , lightsSpotDepth
  , lightsPoint
  , lightsPointDepth
  , lightsPointColor
  , pickingMap
  , off
  , toggleState
};

class Engine;

namespace flf {
class Camera;

/*! \class Debugger
 *
 * \brief Fillwave debugger.
 *
 * - Debugging depth maps
 * - drawing scene from certain views
 * - creating multi-windowed view
 *
 */

class Debugger : public IReloadable {
public:
  Debugger(Engine* engine, GLuint howManyDebugWindows = 6);
  ~Debugger() override;

  /* State */
  void setState(EDebuggerState state);
  EDebuggerState getState();

  /* Render */
  void prepareDebugWindow(GLint id = 0);
  void renderFromCamera(ICamera &c, GLint id = 0);
  void renderDepthPerspective(GLint id = 0);
  void renderDepthOrthographic(GLint id = 0);
  void renderPickingMap();
  void renderGeometryBuffer(GLuint width, GLuint height, GLuint attachments, flc::FramebufferGeometry *buffer);

private:
  struct DebugWindowInfo {
      glm::ivec2 size;
      glm::ivec2 offset;
  };

  std::vector<DebugWindowInfo> mDebugWindows;

  EDebuggerState mState;
  flc::Program* mProgram;
  Engine* mEngine;

  flc::VertexBufferDebug *mVBO;

  GLuint mDebugWindowsSize;
  GLuint mMiniwindowsOccupied;

  GLint mULCTextureUnit, mULCNearPlane, mULCFarPlane;

  void initBuffers() override;

  void initPipeline() override;

  void initVBO() override;

  void initVAO() override;

  void initUniformsCache() override;
};

} /* flf */
} /* flw */
