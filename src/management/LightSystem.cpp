/*
 * Copyright (c) 2018, Fillwave developers
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

#include <fillwave/Fillwave.h>
#include <fillwave/common/Strings.h>
#include <fillwave/management/LightSystem.h>


namespace flw {
namespace flf {

const glm::mat4 FILLWAVE_UV_BIAS_MATRIX(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);

LightSystem::LightSystem() {
  mLightBufferData.resize(FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER + FILLWAVE_MAXIMUM_LIGHTS_IN_MANAGER);
}

void LightSystem::clear() {
  mLightsSpot.clear();
  mLightsDirectional.clear();
  mLightsPoint.clear();
}

bool LightSystem::isLightsRefresh() {
  return isMoveablesRefresh(mLightsSpot) || isMoveablesRefresh(mLightsDirectional) || isMoveablesRefresh (mLightsPoint);
}

void LightSystem::resetLightsRefresh() {
  resetMoveablesRefresh(mLightsSpot);
  resetMoveablesRefresh(mLightsDirectional);
  resetMoveablesRefresh(mLightsPoint);
}

void LightSystem::updateLightEntities() {
  for (auto &it : mLightsSpot) {
    it->updateFromFollowed();
    it->updateShadowCamera();
  }
  for (auto &it : mLightsDirectional) {
    it->updateFromFollowed();
    it->updateShadowCamera();
  }
  for (auto &it : mLightsPoint) {
    it->updateFromFollowed();
    it->updateShadowCamera();
  }
}

void LightSystem::pushLightUniforms(flc::Program *program) {

  /* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT */

  program->uniformPush("uNumberOfSpotLights", static_cast<GLint>(mLightsSpot.size() + mLightsDirectional.size()));

#if defined(FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES)
  /* Mesa shader compiler optimizes out "uNumberOfPointLights" but it should not */
  /* This causes a false positive error indication here */
#else
  program->uniformPush("uNumberOfPointLights", static_cast<GLint>(mLightsPoint.size()));
#endif /* defined(FILLWAVE_THIRD_PARTY_WORKAROUNDS) && defined(FILLWAVE_COMPILATION_PC_GLES) */

  GLint UBOIterator = 0;

  /* Spot lights */
  for (size_t i = 0; i < mLightsSpot.size(); i++) {
    LightSpot *lightS = mLightsSpot[i].get();
    CameraPerspective camera = *(lightS->getShadowCamera());

    for (GLuint j = 0; j < 3; j++) {
      mLightBufferData[UBOIterator].position[j] = glm::value_ptr(lightS->getTranslation())[j];
    }
    mLightBufferData[UBOIterator].position[3] = 1.0;

    for (GLuint j = 0; j < 4; j++) {
      mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(lightS->getIntensity())[j];
    }

    glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
    for (GLuint j = 0; j < 16; j++) {
      mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
    }

    program->uniformPush(getNotIndexableName("uShadowMap", UBOIterator), FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
    UBOIterator++;
  }

  /* Directional lights */
  for (size_t i = 0; i < mLightsDirectional.size(); i++) {
    CameraOrthographic camera = *(mLightsDirectional[i]->getShadowCamera());

    for (GLuint j = 0; j < 3; j++) {
      mLightBufferData[UBOIterator].position[j] = glm::value_ptr(mLightsDirectional[i]->getTranslation())[j];
    }
    mLightBufferData[UBOIterator].position[3] = 1.0;

    for (GLuint j = 0; j < 4; j++) {
      mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(mLightsDirectional[i]->getIntensity())[j];
    }

    glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
    for (GLuint j = 0; j < 16; j++) {
      mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
    }

    program->uniformPush(getNotIndexableName("uShadowMap", UBOIterator), FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
    UBOIterator++;
  }

  /* Point lights */
  for (size_t i = 0; i < mLightsPoint.size(); i++) {
    /*LightPoint* l = mPointLights[i].get();*/
    program->uniformPush(getStructField("uPointLights", "position", i),
                         glm::vec4(mLightsPoint[i]->getTranslation(), 1.0));
    program->uniformPush(getStructField("uPointLights", "intensity", i), mLightsPoint[i]->getIntensity());
    program->uniformPush(getNotIndexableName("uPointShadowMap", i), FILLWAVE_SHADOW_FIRST_UNIT + UBOIterator);
    UBOIterator++;
  }

  if (isLightsRefresh()) {
    pushLightUniformBuffers(program);
    resetLightsRefresh();
  }
}

void LightSystem::pushLightUniformsDR() {

  /* KEEP THIS ORDER !!! SPOT -> DIRECTIONAL -> POINT*/

  GLint UBOIterator = 0;

  /* Spot lights */
  for (size_t i = 0; i < mLightsSpot.size(); i++) {

    CameraPerspective camera = *(mLightsSpot[i]->getShadowCamera());

    for (GLuint j = 0; j < 3; j++) {
      mLightBufferData[UBOIterator].position[j] = glm::value_ptr(mLightsSpot[i]->getTranslation())[j];
    }
    mLightBufferData[UBOIterator].position[3] = 1.0;

    for (GLuint j = 0; j < 4; j++) {
      mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(mLightsSpot[i]->getIntensity())[j];
    }

    glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
    for (GLuint j = 0; j < 16; j++) {
      mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
    }
    UBOIterator++;
  }

  /* Directional lights */
  for (size_t i = 0; i < mLightsDirectional.size(); i++) {
    CameraOrthographic camera = *(mLightsDirectional[i]->getShadowCamera());

    for (GLuint j = 0; j < 3; j++) {
      mLightBufferData[UBOIterator].position[j] = glm::value_ptr(mLightsDirectional[i]->getTranslation())[j];
    }
    mLightBufferData[UBOIterator].position[3] = 1.0;

    for (GLuint j = 0; j < 4; j++) {
      mLightBufferData[UBOIterator].intensity[j] = glm::value_ptr(mLightsDirectional[i]->getIntensity())[j];
    }

    glm::mat4 matrix = FILLWAVE_UV_BIAS_MATRIX * camera.getViewProjection();
    for (GLuint j = 0; j < 16; j++) {
      mLightBufferData[UBOIterator].mvp[j] = glm::value_ptr(matrix)[j];
    }
    UBOIterator++;
  }
}

void LightSystem::updateDeferredBufferSpot(GLuint lightID, flc::Program *program, GLint shadowUnit) {
  program->use();

  program->uniformPush("uLight.base.color", glm::vec3(mLightsSpot[lightID]->getIntensity()));
  program->uniformPush("uLight.base.ambientIntensity", 0.15f);
  program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
  program->uniformPush("uLight.attenuation.constant", 0.1f);
  program->uniformPush("uLight.attenuation.linear", 0.4f);
  program->uniformPush("uLight.attenuation.exp", 0.1f);
  program->uniformPush("uLight.position", mLightsSpot[lightID]->getTranslation());
  program->uniformPush("uLight.mvp", glm::make_mat4(mLightBufferData[shadowUnit - FILLWAVE_SHADOW_FIRST_UNIT].mvp));

  program->uniformPush("uShadowMap", shadowUnit);
  program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::updateDeferredBufferDirectional(GLuint lightID, flc::Program *program, GLint /*shadowUnit*/) {
  program->use();

  program->uniformPush("uLight.base.color", glm::vec3(mLightsDirectional[lightID]->getIntensity()));
  program->uniformPush("uLight.base.ambientIntensity", 0.15f);
  program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
  program->uniformPush("uLight.direction", -mLightsDirectional[lightID]->getTranslation());
  program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::updateDeferredBufferPoint(GLuint lightID, flc::Program *program, GLint /*shadowUnit*/) {
  program->use();

  program->uniformPush("uLight.base.color", glm::vec3(mLightsPoint[lightID]->getIntensity()));
  program->uniformPush("uLight.base.ambientIntensity", 0.15f);
  program->uniformPush("uLight.base.diffuseIntensity", 0.85f);
  program->uniformPush("uLight.attenuation.constant", 0.4f);
  program->uniformPush("uLight.attenuation.linear", 0.3f);
  program->uniformPush("uLight.attenuation.exp", 0.1f);
  program->uniformPush("uSpecularPower", 255.0f);
}

void LightSystem::pushLightUniformBuffers(flc::Program *program) {
  program->uniformBlockPush(FILLWAVE_LIGHTS_BINDING_POINT_NAME, reinterpret_cast<GLfloat *>(mLightBufferData.data()));
}

void LightSystem::bindShadowmaps() {
  GLint currentTextureUnit = FILLWAVE_SHADOW_FIRST_UNIT;
  for (size_t i = 0; i < mLightsSpot.size(); i++) {
    mLightsSpot[i]->getShadowTexture()->bind(currentTextureUnit++);
  }
  for (size_t i = 0; i < mLightsDirectional.size(); i++) {
    mLightsDirectional[i]->getShadowTexture()->bind(currentTextureUnit++);
  }
  for (size_t i = 0; i < mLightsPoint.size(); i++) {
    mLightsPoint[i]->getShadowTexture()->bind(currentTextureUnit++);
  }
}

GLfloat LightSystem::computePointLightBoundingSphere(LightPoint *light) {
  const glm::vec4 i = light->getIntensity();
  const LightAttenuationData a = light->getAttenuation();
  const GLfloat diffuse = 1.0f;
  const GLfloat maxRGB = glm::max(glm::max(i.x, i.y), i.z);
  //todo validate this equation
  return glm::sqrt(a.mLinear * a.mLinear - 4.0f * a.mExp * (a.mExp - 256.0f * maxRGB * diffuse) - a.mLinear) / 2 * a.mExp;
}

} /* flf */
} /* flw */
