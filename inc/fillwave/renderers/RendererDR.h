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

#include <fillwave/renderers/IRenderer.h>
#include <fillwave/core/rendering/FramebufferGeometry.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/Math.h>
#include <fillwave/core/rendering/Texture2DRenderable.h>

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

  ~RendererDR() override = default;

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

  LightSystem &mLights;
  TextureSystem &mTextures;

  flc::Program* mProgramMain;
  flc::Program* mProgramMainAnimated;
  flc::Program* mProgramDirectionalLight;
  flc::Program* mProgramSpotLight;
  flc::Program* mProgramPointLight;
  flc::Program* mProgramDepthless;
  flc::Program* mProgramAmbient;
  flc::Program* mProgramAOGeometry;
  flc::Program* mProgramAOColor;

  pu<flc::Texture2DRenderable> mAOGeometryBuffer;
  pu<flc::Texture2DRenderable> mAOColorBuffer;

  pu<Mesh> mDeferredPointLight;

  GLint mULCDRDepthlesDiffuseTexel;
  GLint mULCDRDepthlessPositionTexel;
  GLint mULCDRScreenSize;
  GLint mULCDRAScreenSize;
  GLint mULCDRADiffuseAttachment;
  GLint mULCAmbient;

  GLint mULCCameraPositionDirectional;
  GLint mULCAmbientIntensityDirectional;
  GLint mULCScreenSizeDirectional;
  GLint mULCShadowUnitDirectional;
  GLint mULCIsAODirectional;
  GLint mULCCameraPositionPoint;
  GLint mULCAmbientIntensityPoint;
  GLint mULCMVPPoint;
  GLint mULCScreenSizePoint;
  GLint mULCShadowUnitPoint;
  GLint mULCIsAOPoint;

  /* ULC - Uniform location cache */
  GLint mULCCameraPositionSpot;
  GLint mULCAmbientIntensitySpot;
  GLint mULCScreenSizeSpot;
  GLint mULCShadowUnitSpot;
  GLint mULCIsAOSpot;

  GLboolean mIsAO;

  const GLuint mDeferredColorAttachments;

  pu<flc::FramebufferGeometry> mGBuffer;

  std::vector<IRenderable*> mNodes; /* true -> animated, false -> not animated */
  std::vector<IRenderable*> mAnimatedNodes; /* true -> animated, false -> not animated */
};

} /* flf */
} /* flw */

#endif /* defined(FILLWAVE_GLES_3_0) */
