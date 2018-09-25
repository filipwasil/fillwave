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

#include <flw/flf/models/base/Moveable.h>

#include <flw/flf/common/Observable.h>
#include <flw/flf/common/Easing.h>
#include <flw/flf/common/Containers.h>
#include <flw/flf/common/Aliases.h>

#include <flw/OpenGL.h>
#include <flw/Math.h>

#include <memory>
#include <vector>
#include <functional>
#include <algorithm>

namespace flw {
namespace flf {

/*! \class Moveable
 * \brief Base for every object which has a 3D position.
 */

class Moveable : public Observable {
public:
  Moveable(
    glm::vec3 translation = glm::vec3(0.0)
    , glm::quat rotation = glm::quat(1.0, 0.0, 0.0, 0.0)
    , unsigned int callbacks = 1);

  ~Moveable() override;

  Moveable &operator=(const Moveable&);

  Moveable(const Moveable&);

  Moveable& operator= (Moveable &&);

  Moveable (Moveable&&);

  void moveTo(glm::vec3 coordinates);

  void moveToX(GLfloat distance);

  void moveToY(GLfloat distance);

  void moveToZ(GLfloat distance);

  void moveBy(glm::vec3 coordinates);

  void moveByX(GLfloat distance);

  void moveByY(GLfloat distance);

  void moveByZ(GLfloat distance);

  void moveInDirection(glm::vec3 direction);

  glm::vec3 getTranslation();

  void scaleTo(GLfloat scale);

  void scaleTo(glm::vec3 scale);

  void scaleToX(GLfloat scale);

  void scaleToY(GLfloat scale);

  void scaleToZ(GLfloat scale);

  glm::vec3 getScale();

  void rotateTo(glm::quat rotation);

  void rotateTo(const glm::vec3 &axis, GLfloat angle);

  void rotateBy(const glm::vec3 &axis, GLfloat angle);

  void rotateByX(float angle);

  void rotateByY(float angle);

  void rotateByZ(float angle);

  glm::quat getRotation();

  void updateMatrixCache();

  bool isRefresh() const;

  void setRefresh(bool state);

  /* Parent */
  glm::mat4 getParentMMC() const;

  glm::quat getParentRotation() const;

  void waitInTime(float deltaTime);

  void moveBy(float deltaTime, const glm::vec3& deltaMove, Callback<float(float)> ease = LinearInterpolation);

  void moveTo(float durationInSeconds, const glm::vec3& endTranslation, Callback<float(float)> ease);

  void scaleBy(float deltaTime, const glm::vec3& aScale, Callback<float(float)> ease = LinearInterpolation);

  void scaleTo(float deltaTime, const glm::vec3& aScale, Callback<float(float)> ease = LinearInterpolation);

  void rotateBy(float deltaTime, const float aAngle, const glm::vec3& aAxis, Callback<float(float)> ease = LinearInterpolation);

  void rotateTo(float deltaTime, const float aAngle, const glm::vec3& aAxis, Callback<float(float)> ease = LinearInterpolation);

  void loop(int loops);

  void stop();

  bool isMoving();

  float stepInTime(float delta);

  void attachTimeCallback(float deltaTime, Callback<float(float)> aAction);

  template <typename ...ARGS>
  void attachTimeCallback(float deltaTime, Callback<float(float, ARGS...)> aAction, ARGS&&... args) {
    mTimeCallbacks.push_back([this, deltaTime, aAction, args...](float aDeltaTime) {
      if (mCallbackTimePassed == 0.0f) {
        aAction(0.0f, std::forward<ARGS...>(args...));
      }
      mCallbackTimePassed += aDeltaTime;
      aAction(mCallbackTimePassed/deltaTime >= 1.0f ? 1.0f : mCallbackTimePassed/deltaTime, args...);
      if (mCallbackTimePassed < deltaTime) {
        return 0.0f;
      }
      float timeLeft = mCallbackTimePassed - deltaTime;
      mCallbackTimePassed = 0;
      return timeLeft;
    });
  }

protected:
  glm::fvec3 mTranslation;
  glm::quat mRotation;
  glm::vec3 mScale;

  /* Parent */
  glm::quat mParentRotation;

  /* MMC - Model Matrix Cache */
  glm::mat4 mMMC;
  glm::mat4 mParentMMC;

  /* Refresh flag */
  bool mRefresh;

  float mCallbackTimePassed;

 private:
  unsigned int mCurrentCallbackIdx;
  unsigned int mCallbackLoops;
  vec<Callback<float(float)>> mTimeCallbacks;

  struct {
    glm::vec3 mTranslation;
    glm::vec3 mScale;
    glm::quat mRotation;
  } mBase;
};

template <class M>
bool isMoveablesRefresh(const std::vector<M>& moveables) {
  for (auto &it : moveables) {
    if (it->isRefresh()) {
      return true;
    }
  }
  return false;
}

template <class M>
void resetMoveablesRefresh(const std::vector<M>& data) {
  for (auto &it : data) {
    it->setRefresh(false);
  }
}

} /* flf */
} /* flw */
