/*
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

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
#include <fillwave/models/animations/Animator.h>
#endif

#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/common/Strings.h>
#include <fillwave/models/Mesh.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("Mesh", FERROR | FFATAL | FINFO)

using namespace std;

namespace fillwave {
namespace framework {

const GLint gOQVertices = 36; //todo move it from here

Mesh::Mesh(Engine *engine,
    const Material &material,
    core::Texture2D *diffuseMap,
    core::Texture2D *normalMap,
    core::Texture2D *specularMap,
    core::Program *program,
    core::Program *programShadow,
    core::Program *programShadowColor,
    core::Program *programOcclusion,
    core::Program *programAmbientOcclusionGeometry,
    core::Program *programAmbientOcclusionColor,
    LightSystem *lights,
    core::VertexBufferBasic *vbo,
    core::IndexBuffer *ibo,
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
    Animator *animator,
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
    GLenum renderMode,
    core::VertexArray *vao)
    : IReloadable (engine, vao), mMaterial (material), mDiffuseMap (diffuseMap), mNormalMap (normalMap), mSpecularMap (
    specularMap), mProgram (program), mProgramShadow (programShadow), mProgramShadowColor (programShadowColor)
    , mProgramOQ (programOcclusion), mProgramAOGeometry (programAmbientOcclusionGeometry), mProgramAOColor (
        programAmbientOcclusionColor), mRenderMode (renderMode), mIBO (ibo), mVBO (vbo), mLights (lights)
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
    , mAnimator (animator)
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
#ifdef FILLWAVE_GLES_3_0
#else
    , mConditionalRendering (GL_QUERY_WAIT)
#endif
{
  initPipeline ();
  initVBO ();
  initVAO ();
  initUniformsCache ();
}

void Mesh::drawPBRP(ICamera &camera) {
#ifdef FILLWAVE_GLES_3_0
#else
  if (mAnimator || mOcclusionQuery.getResultAsync (1))
#endif
  {
    core::Uniform::push (mULCModelMatrix, mPhysicsMMC);
    core::Uniform::push (mULCLightAmbientIntensity, mMaterial.getAmbient ());
    core::Uniform::push (mULCLightDiffuseIntensity, mMaterial.getDiffuse ());
    core::Uniform::push (mULCLightSpecularIntensity, mMaterial.getSpecular ());
    core::Uniform::push (mULCCameraPosition, camera.getTranslation ());
    core::Uniform::push (mULCViewProjectionMatrix, camera.getViewProjection ());

    coreDraw ();
  }
}

void Mesh::draw(ICamera &camera) {
#ifdef FILLWAVE_GLES_3_0
#else
  if (mAnimator || mOcclusionQuery.getResultAsync (1))
#endif
  {
    mProgram->use ();

    core::Uniform::push (mULCModelMatrix, mPhysicsMMC);
    core::Uniform::push (mULCLightAmbientIntensity, mMaterial.getAmbient ());
    core::Uniform::push (mULCLightDiffuseIntensity, mMaterial.getDiffuse ());
    core::Uniform::push (mULCLightSpecularIntensity, mMaterial.getSpecular ());
    core::Uniform::push (mULCCameraPosition, camera.getTranslation ());
    core::Uniform::push (mULCViewProjectionMatrix, camera.getViewProjection ());

    mLights->pushLightUniforms (mProgram);
    mLights->bindShadowmaps ();

    coreDraw ();
  }
}

void Mesh::drawDR(ICamera &camera) {
#ifdef FILLWAVE_GLES_3_0
#else
  if (mAnimator || mOcclusionQuery.getResultAsync (1))
#endif
  {
    mProgram->use ();

    core::Uniform::push (mULCModelMatrix, mPhysicsMMC);
    core::Uniform::push (mULCViewProjectionMatrix, camera.getViewProjection ());

    //   core::Uniform::push(mULCLightAmbientIntensity, mMaterial.getAmbient());
    //   core::Uniform::push(mULCLightDiffuseIntensity, mMaterial.getDiffuse());
    //   core::Uniform::push(mULCLightSpecularIntensity, mMaterial.getSpecular());
    //   core::Uniform::push(mULCCameraPosition, camera.getTranslation());

//      mLights->pushLightUniformsShadowMaps(mProgram.get());

    mLights->pushLightUniformsDR ();
    mLights->bindShadowmaps ();

    coreDraw ();
  }
}

void Mesh::drawFast(ICamera &) {
  mProgram->use ();
  mLights->bindShadowmaps ();

  coreDraw ();
}

inline void Mesh::coreDraw() {
  mVAO->bind ();

  bindTextures ();

  //xxx blinking scene
  //xxx (OpenGL 3.3+)consider using conditional rendering this way:
  //#ifdef FILLWAVE_GLES_3_0
  //#else
  //   mConditionalRendering.begin(mOcclusionQuery.getID());
  onDraw ();
  //   mConditionalRendering.end();
  //
  //#endif

  core::VertexArray::unbindVAO ();

  core::Texture2D::unbind2DTextures ();
}

inline void Mesh::bindTextures() {
  if (mDiffuseMap) {
    mDiffuseMap->bind (FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used
  }

  if (mNormalMap) {
    mNormalMap->bind (FILLWAVE_NORMAL_UNIT); //xxx texture region coordinates are not used
  }

  if (mSpecularMap) {
    mSpecularMap->bind (FILLWAVE_SPECULAR_UNIT); //xxx texture region coordinates are not used
  }
}

void Mesh::drawPicking(ICamera &camera) {
  if (isPickable ()) {
    mProgram->use ();

    core::Uniform::push (mULCModelMatrix, mPhysicsMMC);

    core::Uniform::push (mULCCameraPosition, camera.getTranslation ());
    core::Uniform::push (mULCViewProjectionMatrix, camera.getViewProjection ());

    core::Uniform::push (mULCColorPicking, true);
    core::Uniform::push (mULCPainterColor, glm::vec4 (getPickableColor (), 1.0));

    mVAO->bind ();

    onDraw ();

    core::VertexArray::unbindVAO ();

    core::Uniform::push (mULCColorPicking, false);

    core::Program::disusePrograms ();
  }
}

void Mesh::drawOcclusionBox(ICamera &camera) {

  mProgramOQ->use ();

  core::Uniform::push (mULCMVPOcclusion, camera.getViewProjection () * mPhysicsMMC * mOcclusionMatrix);

  mOcclusionQuery.begin ();

  glDrawArrays (mRenderMode, 0, gOQVertices);

  fLogC("drawOcclusionBox failed");

  mOcclusionQuery.end ();

  core::Program::disusePrograms ();
}

void Mesh::drawDepth(ICamera &camera) {
  if (isPSC ()) {
    mProgramShadow->use ();

    core::Uniform::push (mULCMVPShadow, camera.getViewProjection () * mPhysicsMMC);

    mVAO->bind ();

    onDraw ();

    core::VertexArray::unbindVAO ();

    core::Program::disusePrograms ();
  }
}

void Mesh::drawDepthColor(ICamera &camera, glm::vec3 & /*xxx double check position*/) {
  if (isPSC ()) {
    mProgramShadowColor->use ();

    core::Uniform::push (mULCMVPShadowColor, camera.getViewProjection () * mPhysicsMMC);
    core::Uniform::push (mULCModelMatrixShadowColor, mPhysicsMMC);

    mVAO->bind ();

    onDraw ();

    core::VertexArray::unbindVAO ();

    core::Program::disusePrograms ();
  }
}

void Mesh::drawAOG(ICamera &camera) {
  mProgramAOGeometry->use ();

  core::Uniform::push (mULCMVPAmbientOcclusion, camera.getViewProjection () * mPhysicsMMC);
  core::Uniform::push (mULCPositionAmbientOcclusion, camera.getEye () * mPhysicsMMC);

  mVAO->bind ();

  onDraw ();

  core::VertexArray::unbindVAO ();
}

void Mesh::drawAOC(ICamera &camera) {
  mProgramAOColor->use ();

//      core::Uniform::push(mULCTextureMap, FILLWAVE_DIFFUSE_ATTACHMENT);
  core::Uniform::push (mULCSampleRadius, FILLWAVE_AO_SAMPLE_RADIUS);
  core::Uniform::push (mULCProjectionMatrix, camera.getProjection ());
//      core::Uniform::push(mULCRandomVectors, camera.getEye() * mPhysicsMMC);

  mVAO->bind ();

  onDraw ();

  core::VertexArray::unbindVAO ();
}

void Mesh::onDraw() {
  if (mIBO) {
    /* Perform index drawing */
    glDrawElements (mRenderMode, mIBO->getElements (), GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
    fLogC("glDrawElements failed");
  } else {
    /* Perform array drawing */
    glDrawArrays (mRenderMode, 0, mVBO->getElements ());
    fLogC("glDrawArrays failed");
  }
}

inline void Mesh::initPipeline() {
  if (mProgram) {
    ProgramLoader::initDefaultUniforms (mProgram);
  }
}

inline void Mesh::initUniformsCache() {
  /* Regular program */
  if (mProgram) {
    mULCModelMatrix = mProgram->getUniformLocation ("uModelMatrix");
    mULCLightAmbientIntensity = mProgram->getUniformLocation ("uLightAmbientIntensity");
    mULCLightDiffuseIntensity = mProgram->getUniformLocation ("uLightDiffuseIntensity");
    mULCLightSpecularIntensity = mProgram->getUniformLocation ("uLightSpecularIntensity");
    mULCCameraPosition = mProgram->getUniformLocation ("uCameraPosition");
    mULCViewProjectionMatrix = mProgram->getUniformLocation ("uViewProjectionMatrix");
    mULCColorPicking = mProgram->getUniformLocation ("uColorPicking");
    mULCPainterColor = mProgram->getUniformLocation ("uPainterColor");
  }
  /* Occlusion program */
  if (mProgramOQ) {
    mULCMVPOcclusion = mProgramOQ->getUniformLocation ("uMVP");
  }

  /* Shadow program */
  if (mProgramShadow) {
    mULCMVPShadow = mProgramShadow->getUniformLocation ("uMVP");
  }

  /* ShadowColor program */
  if (mProgramShadowColor) {
    mULCMVPShadowColor = mProgramShadowColor->getUniformLocation ("uMVP");
    mULCModelMatrixShadowColor = mProgramShadowColor->getUniformLocation ("uModelMatrix");
  }

  /* AmbientOcclusion programs */
  if (mProgramAOGeometry) {
    mULCMVPAmbientOcclusion = mProgramAOGeometry->getUniformLocation ("uMVP");
    mULCPositionAmbientOcclusion = mProgramAOGeometry->getUniformLocation ("uMVPosition");
  }

  if (mProgramAOColor) {
    mULCSampleRadius = mProgramAOColor->getUniformLocation ("uSampleRadius");
    mULCProjectionMatrix = mProgramAOColor->getUniformLocation ("uP");
  }
}

inline void Mesh::initBuffers() {
  if (mIBO) {
    fLogI("RELOAD IBO");
    mIBO->reload ();
  }
  if (mVBO) {
    fLogI("RELOAD VBO");
    mVBO->reload ();
  }
}

inline void Mesh::initVAO() {
  mSampler->bind ();

  mVAO->bind ();

  mVBO->bind ();
  mVBO->attributesSetForVAO ();
  mVBO->setLoaded (GL_FALSE);
  mVBO->send ();

  if (mIBO) {
    mIBO->bind ();
    mIBO->setLoaded (GL_FALSE);
    mIBO->send ();
  }

  core::VertexArray::unbindVAO ();
}

inline void Mesh::initVBO() {
  mVBO->initAttributes (mProgram->getHandle ());
  mOcclusionMatrix = glm::scale (glm::mat4 (1.0f), mVBO->getOcclusionBoxSize ());
}

void Mesh::log() const {
  mVBO->log ();
}

void Mesh::updateRenderer(IRenderer &renderer) {
  renderer.update (this);
}

bool Mesh::getRenderItem(RenderItem &item) {
  item.mCount = mIBO ? mIBO->getElements () : mVBO->getElements ();
  item.mDataType = GL_UNSIGNED_INT;
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle ();
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle ();
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle ();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mDiffuseMap ? mDiffuseMap->getHandle () : 0;
  item.mHandles[RenderItem::eRenderHandleNormal] = mNormalMap ? mNormalMap->getHandle () : 0;
  item.mHandles[RenderItem::eRenderHandleSpecular] = mSpecularMap ? mSpecularMap->getHandle () : 0;
  item.mIndicesPointer = 0;
  item.mMode = GL_TRIANGLES;
  item.mRenderStatus = mIBO ? 0xf8 : 0xb8; // vao, ibo, diff, norm, spec, blend, cont, anim
  return true;
}

} /* framework */
} /* fillwave */
