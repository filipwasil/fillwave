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

#include <fillwave/hud/base/IHUDNode.h>
#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Cluster
 * \brief HUD node to indicate progress.
 */

class Cluster : public IHUDNode {
public:
  Cluster(Engine *engine,
      flc::Texture2D *texture,
      const std::string &shaderPath,
      glm::vec2 position,
      glm::vec2 scale);

  virtual ~Cluster() override = default;

  void setSpeed(GLfloat progress);

  void setRPM(GLfloat progress);

  void evaluateTime(float time) override;

  void createGauge(
      int angleStep
      , int angleStart
      , int angleStop
      , int valueStart
      , int valueStop
      , glm::vec2 positionsCenter
      , float radius);

  void setShift(unsigned int shift);

private:
  std::vector<pText> mTexts;
  pText mShift;

  float mSpeed;
  float mRPM;
  float mTimePassed;
  Engine* mEngine;
};

} /* flf */
typedef std::unique_ptr<flf::Cluster> puCluster;
} /* flw */
