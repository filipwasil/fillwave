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

#include <fillwave/core/buffers/VertexBufferDebug.h>

namespace flw {
namespace flc {
class FramebufferGeometry;
}

enum class eDebuggerState {
  eLightsSpot
  , eLightsSpotColor
  , eLightsSpotDepth
  , eLightsPoint
  , eLightsPointDepth
  , eLightsPointColor
  , ePickingMap
  , eOff
  , eToggleState
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
  Debugger(Engine *engine, GLsizei howManyDebugWindows = 6);
  virtual ~Debugger() = default;

  /* State */
  void setState(eDebuggerState state);
  eDebuggerState getState();

  /* Render */
  void prepareDebugWindow(GLint id = 0);
  void renderFromCamera(ICamera &c, GLint id = 0);
  void renderDepthPerspective(GLint id = 0);
  void renderDepthOrthographic(GLint id = 0);
  void renderPickingMap();
  void renderGeometryBuffer(GLuint width, GLuint height, GLuint attachments, flc::FramebufferGeometry *buffer);

private:
  struct DebugWindowInfo
  {
      glm::ivec2 size;
      glm::ivec2 offset;
  };

  std::vector<DebugWindowInfo> mDebugWindows;

  eDebuggerState mState;
  flc::Program *mProgram;
  Engine *mEngine;

  flc::VertexBufferDebug *mVBO;

  GLuint mDebugWindowsSize;
  GLuint mMiniwindowsOccupied;

  GLint mULCTextureUnit, mULCNearPlane, mULCFarPlane;

  void initBuffers();

  void initPipeline();

  void initVBO();

  void initVAO();

  void initUniformsCache();
};

} /* flf */
typedef std::unique_ptr<flf::Debugger> puDebugger;
} /* flw */
