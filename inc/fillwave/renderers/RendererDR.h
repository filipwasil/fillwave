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

#include <fillwave/renderers/IRenderer.h>
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Math.h>

#if defined(FILLWAVE_GLES_3_0)
#else

namespace flw {
namespace flf {

class ProgramLoader;

/*! \class RendererDR
 * \brief Deferred IRenderer. Not ready (Rev.4.2.1).
 */

class RendererDR : public IRenderer {
public:
  RendererDR(Engine *engine, ProgramLoader &loader);

  virtual ~RendererDR() = default;

  void update(IRenderable *renderable) override;

  void draw(ICamera &camera) override;

  void reset(GLuint width, GLuint height) override;

  void clear() override;

  /* Init */
  void initGeometryBuffer();

  void initGeometryShading();

  void initUniforms();

  void initUniformsCache();

  /* Passes */
  void drawSceneCoreDR();

  void drawGeometryPass(ICamera &camera);

  void drawDepthlessPass();

  void drawAmbientPass();

  void drawAOPass(ICamera &camera);

  void drawColorPass(ICamera &camera);

  void drawLightsSpotPass(ICamera &camera, GLint &textureUnit);

  void drawLightsDirectionalPass(ICamera &camera, GLint &textureUnit);

  void drawLightsPointPass(ICamera &camera, GLint &textureUnit);

  void drawColorPassBegin();

  void drawColorPassEnd();

  void drawDebug();

private:
  glm::ivec2 mScreenSize;

  LightSystem *mLights;
  TextureSystem *mTextures;

  flc::Program *mProgramMain, *mProgramMainAnimated, *mProgramDirecionalLight, *mProgramSpotLight, *mProgramPointLight, *mProgramDepthless, *mProgramAmbient, *mProgramAOGeometry, *mProgramAOColor;

  puTexture2DRenderable mAOGeometryBuffer;
  puTexture2DRenderable mAOColorBuffer;

  puMesh mDeferredPointLight;

  GLint mULCDRDepthlesDiffuseTexel, mULCDRDepthlessPositionTexel, mULCDRScreenSize, mULCDRAScreenSize, mULCDRADiffuseAttachment, mULCAmbient;

  GLint mULCCameraPositionDirectional, mULCAmbientIntensityDirectional, mULCScreenSizeDirectional, mULCShadowUnitDirectional, mULCIsAODirectional, mULCCameraPositionPoint, mULCAmbientIntensityPoint, mULCMVPPoint, mULCScreenSizePoint, mULCShadowUnitPoint, mULCIsAOPoint;

  /* ULC - Uniform location cache */
  GLint mULCCameraPositionSpot, mULCAmbientIntensitySpot, mULCScreenSizeSpot, mULCShadowUnitSpot, mULCIsAOSpot;

  GLboolean mIsAO;

  const GLuint mDeferredColorAttachments;
  const GLuint mDeferredDepthAttachments;

  puFramebufferGeometry mGBuffer;

  std::vector<IRenderable *> mNodes; /* true -> animated, false -> not animated */
  std::vector<IRenderable *> mAnimatedNodes; /* true -> animated, false -> not animated */
};

} /* namespace flf */
} /* namespace flw */

#endif /* defined(FILLWAVE_GLES_3_0) */
