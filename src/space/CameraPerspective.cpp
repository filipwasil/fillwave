/*
 * CameraPerspective.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
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


#include <fillwave/space/CameraPerspective.h>

namespace flw {
namespace flf {

CameraPerspective::CameraPerspective()
    : mProjectionFovy(glm::radians(90.0)), mProjectionAspectRatio(1.0), mProjectionNearPlane(0.01), mProjectionFarPlane(
    100.0) {
  updateProjection();
}

CameraPerspective::CameraPerspective(glm::vec3 position,
    glm::quat rotation,
    GLfloat fovy,
    GLfloat aspectRatio,
    GLfloat nearPlane,
    GLfloat farPlane)
    : ICamera(position, rotation), mProjectionFovy(fovy), mProjectionAspectRatio(aspectRatio), mProjectionNearPlane(
    nearPlane), mProjectionFarPlane(farPlane) {
  updateProjection();
}

void CameraPerspective::updateProjection() {
  mProjectionMatrix = glm::perspective(mProjectionFovy,
                                       mProjectionAspectRatio,
                                       mProjectionNearPlane,
                                       mProjectionFarPlane);
  mRefreshProjection = GL_FALSE;
}

GLfloat CameraPerspective::getProjectionFovy() {
  return mProjectionFovy;
}

GLfloat CameraPerspective::getProjectionAspectRatio() {
  return mProjectionAspectRatio;
}

GLfloat CameraPerspective::getProjectionNearPlane() {
  return mProjectionNearPlane;
}

GLfloat CameraPerspective::getProjectionFarPlane() {
  return mProjectionFarPlane;
}

void CameraPerspective::setProjectionFovy(GLfloat fovy) {
  mProjectionFovy = fovy;
  mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionAspectRatio(GLfloat aspect) {
  mProjectionAspectRatio = aspect;
  mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionNearPlane(GLfloat nearPlane) {
  mProjectionNearPlane = nearPlane;
  mRefreshProjection = GL_TRUE;
}

void CameraPerspective::setProjectionFarPlane(GLfloat farPlane) {
  mProjectionFarPlane = farPlane;
  mRefreshProjection = GL_TRUE;
}

} /* flf */
} /* flw */
