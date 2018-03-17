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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/operations/ConditionalRender.h>
#include <fillwave/core/operations/TQuery.h>
#include <fillwave/models/Entity.h>
#include <fillwave/models/base/Material.h>
#include <fillwave/core/pipeline/Fence.h>
#include <fillwave/models/base/IReloadable.h>
#include <fillwave/renderers/IRenderer.h>

namespace flw {
class Engine;

namespace flf {
class Animator;
class LightSystem;
}

namespace flf {

/*! \class Mesh
 * \brief Basic drawable Entity.
 */
class Mesh : public Entity, public IReloadable {
public:
  Mesh(Engine *engine,
      const Material &material,
      flc::Texture2D* diffuseMap,
      flc::Texture2D* normalMap,
      flc::Texture2D* specularMap,
      flc::Program* program,
      flc::Program* ProgramShadow,
      flc::Program* programShadowColor,
      flc::Program* programOcclusion,
      flc::Program* programAmbientOcclusionGeometry,
      flc::Program* programAmbientOcclusionColor,
      LightSystem &lights,
      flc::VertexBufferBasic* vbo = nullptr,
      flc::IndexBuffer* ibo = nullptr,
      Animator* animator = nullptr,
      GLenum renderMode = GL_TRIANGLES,
      flc::VertexArray* vao = nullptr);

  virtual ~Mesh() override;

  /* IDrawable */
  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  void drawDR(ICamera &camera) override;

  void drawPicking(ICamera &camera) override;

  void drawDepth(ICamera &camera) override;

  void drawDepthColor(ICamera &camera, glm::vec3 &position) override;

  void drawAOG(ICamera &camera) override;

  void drawAOC(ICamera &camera) override;

  void drawOcclusionBox(ICamera &camera) override;

  /* IRenderable */
  virtual void updateRenderer(IRenderer &renderer) override;

  virtual bool getRenderItem(RenderItem &item) override;

  void log() const override;

  void drawFast(ICamera &camera);

  virtual void onDraw();

 protected:
  Material mMaterial;
  flc::Texture2D* mDiffuseMap;
  flc::Texture2D* mNormalMap;
  flc::Texture2D* mSpecularMap;
  flc::Program* mProgram;
  flc::Program* mProgramShadow;
  flc::Program* mProgramShadowColor;
  flc::Program* mProgramOQ;
  flc::Program* mProgramAOGeometry;
  flc::Program* mProgramAOColor;
  GLenum mRenderMode;

  /* Buffers */
  flc::IndexBuffer* mIBO;
  flc::VertexBufferBasic* mVBO;

  /* Light */
  LightSystem &mLights;

  /* Animations */
  Animator* mAnimator;

  /* Occlusion cut off */
  glm::mat4 mOcclusionMatrix;
  flc::QueryIfAnySamplesPassed mOcclusionQuery;
//   puFence mFence;

#ifdef FILLWAVE_GLES_3_0
#else
//   flc::QueryTimeElapsed mTimeQuery;
  flc::ConditionalRender mConditionalRendering;
#endif

private:

  /* ULC - Uniform location cache */
  GLint mULCModelMatrix, mULCViewProjectionMatrix, mULCLightAmbientIntensity, mULCLightDiffuseIntensity, mULCLightSpecularIntensity, mULCCameraPosition, mULCColorPicking, mULCPainterColor;
  GLint mULCMVPOcclusion;
  GLint mULCMVPShadow;
  GLint mULCMVPShadowColor, mULCModelMatrixShadowColor;
  GLint mULCMVPAmbientOcclusion, mULCPositionAmbientOcclusion;
  GLint mULCSampleRadius, mULCProjectionMatrix;

  void initBuffers() override;

  void initPipeline() override;

  void initUniformsCache() override;

  void initVAO() override;

  void initVBO() override;

  void bindTextures();

  void coreDraw();
};

} /* flf */
} /* flw */
