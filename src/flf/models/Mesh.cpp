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

#include <flw/flf/loaders/ProgramLoader.h>
#include <flw/flf/models/Mesh.h>
#include <flw/flf/management/LightSystem.h>
#include <flw/Fillwave.h>
#include <flw/Log.h>

FLOGINIT("Mesh", FERROR | FFATAL | FINFO)

namespace flw {
namespace flf {

const GLint gOQVertices = 36; //todo move it from here

Mesh::Mesh(Engine* engine,
    const Material& material,
    flc::Texture2D* diffuseMap,
    flc::Texture2D* normalMap,
    flc::Texture2D* specularMap,
    flc::Program* program,
    flc::Program* programShadow,
    flc::Program* programShadowColor,
    flc::Program* programOcclusion,
    flc::Program* programAmbientOcclusionGeometry,
    flc::Program* programAmbientOcclusionColor,
    LightSystem& lights,
    flc::VertexBufferBasic* vbo,
    flc::IndexBuffer* ibo,
    ModelLoader::Animator* animator,
    GLenum renderMode,
    flc::VertexArray *vao)
    : IReloadable(engine, vao)
    , mMaterial(material)
    , mDiffuseMap(diffuseMap)
    , mNormalMap(normalMap)
    , mSpecularMap(specularMap)
    , mProgram(program)
    , mProgramShadow(programShadow)
    , mProgramShadowColor(programShadowColor)
    , mProgramOQ(programOcclusion)
    , mProgramAOGeometry(programAmbientOcclusionGeometry)
    , mProgramAOColor(programAmbientOcclusionColor)
    , mRenderMode(renderMode)
    , mIBO(ibo)
    , mVBO(vbo)
    , mLights(lights)
    , mAnimator(animator)
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30)
    , mOcclusionQuery()
#else
    , mOcclusionQuery()
    , mConditionalRendering(GL_QUERY_WAIT)
#endif
{
  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

Mesh::~Mesh() {
    /* empty */
}

void Mesh::drawPBRP(ICamera &camera) {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
  {
    flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);
    flc::Uniform::push(mULCLightAmbientIntensity, mMaterial.mAmbient);
    flc::Uniform::push(mULCLightDiffuseIntensity, mMaterial.mDiffuse);
    flc::Uniform::push(mULCLightSpecularIntensity, mMaterial.mSpecular);
    flc::Uniform::push(mULCCameraPosition, camera.getTranslation());
    flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

    coreDraw();
  }
}

void Mesh::draw(ICamera &camera) {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
  {
    mProgram->use();

    flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);
    flc::Uniform::push(mULCLightAmbientIntensity, mMaterial.mAmbient);
    flc::Uniform::push(mULCLightDiffuseIntensity, mMaterial.mDiffuse);
    flc::Uniform::push(mULCLightSpecularIntensity, mMaterial.mSpecular);
    flc::Uniform::push(mULCCameraPosition, camera.getTranslation());
    flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

    mLights.pushLightUniforms(mProgram);
    mLights.bindShadowmaps();

    coreDraw();
  }
}

void Mesh::drawDR(ICamera &camera) {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  if (mAnimator || mOcclusionQuery.getResultAsync(1))
#endif
  {
    mProgram->use();

    flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);
    flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

    mLights.pushLightUniformsDR();
    mLights.bindShadowmaps();

    coreDraw();
  }
}

void Mesh::drawFast(ICamera &) {
  mProgram->use();
  mLights.bindShadowmaps();

  coreDraw();
}

inline void Mesh::coreDraw() {
  mVAO->bind();

  bindTextures();

  //todo issue with blinking scene
  //todo (OpenGL 3.3+)consider using conditional rendering this way:
  //#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
  //#else
  //   mConditionalRendering.begin(mOcclusionQuery.getID());
  onDraw();
  //   mConditionalRendering.end();
  //
  //#endif

  flc::VertexArray::unbindVAO();

  flc::Texture2D::unbind2DTextures();
}

inline void Mesh::bindTextures() {
  if (mDiffuseMap) {
    mDiffuseMap->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used
  }

  if (mNormalMap) {
    mNormalMap->bind(FILLWAVE_NORMAL_UNIT); //xxx texture region coordinates are not used
  }

  if (mSpecularMap) {
    mSpecularMap->bind(FILLWAVE_SPECULAR_UNIT); //xxx texture region coordinates are not used
  }
}

void Mesh::drawPicking(ICamera &camera) {
  if (isPickable()) {
    mProgram->use();

    flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);

    flc::Uniform::push(mULCCameraPosition, camera.getTranslation());
    flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());

    flc::Uniform::push(mULCColorPicking, true);
    flc::Uniform::push(mULCPainterColor, glm::vec4(getPickableColor(), 1.0));

    mVAO->bind();

    onDraw();

    flc::VertexArray::unbindVAO();

    flc::Uniform::push(mULCColorPicking, false);

    flc::Program::disusePrograms();
  }
}


void Mesh::drawDepth(ICamera &camera) {
  if (isPSC()) {
    mProgramShadow->use();

    flc::Uniform::push(mULCMVPShadow, camera.getViewProjection() * mPhysicsMMC);

    mVAO->bind();

    onDraw();

    flc::VertexArray::unbindVAO();

    flc::Program::disusePrograms();
  }
}

void Mesh::drawDepthColor(ICamera &camera, glm::vec3 & /*xxx double check position*/) {
  if (isPSC()) {
    mProgramShadowColor->use();

    flc::Uniform::push(mULCMVPShadowColor, camera.getViewProjection() * mPhysicsMMC);
    flc::Uniform::push(mULCModelMatrixShadowColor, mPhysicsMMC);

    mVAO->bind();

    onDraw();

    flc::VertexArray::unbindVAO();

    flc::Program::disusePrograms();
  }
}

void Mesh::drawAOG(ICamera &camera) {
  mProgramAOGeometry->use();

  flc::Uniform::push(mULCMVPAmbientOcclusion, camera.getViewProjection() * mPhysicsMMC);
  flc::Uniform::push(mULCPositionAmbientOcclusion, camera.getEye() * mPhysicsMMC);

  mVAO->bind();

  onDraw();

  flc::VertexArray::unbindVAO();
}

void Mesh::drawAOC(ICamera &camera) {
  mProgramAOColor->use();

  flc::Uniform::push(mULCSampleRadius, FILLWAVE_AO_SAMPLE_RADIUS);
  flc::Uniform::push(mULCProjectionMatrix, camera.getProjection());

  mVAO->bind();

  onDraw();

  flc::VertexArray::unbindVAO();
}

void Mesh::onDraw() {
  if (mIBO) {
    /* Perform index drawing */
    glDrawElements(mRenderMode, mIBO->getElements(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
    fLogC("glDrawElements failed");
  } else {
    /* Perform array drawing */
    glDrawArrays(mRenderMode, 0, mVBO->getElements());
    fLogC("glDrawArrays failed");
  }
}

inline void Mesh::initPipeline() {
  if (mProgram) {
    ProgramLoader::initDefaultUniforms(mProgram);
  }
}

inline void Mesh::initUniformsCache() {
  /* Regular program */
  if (mProgram) {
    mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
    mULCLightAmbientIntensity = mProgram->getUniformLocation("uLightAmbientIntensity");
    mULCLightDiffuseIntensity = mProgram->getUniformLocation("uLightDiffuseIntensity");
    mULCLightSpecularIntensity = mProgram->getUniformLocation("uLightSpecularIntensity");
    mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
    mULCViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
    mULCColorPicking = mProgram->getUniformLocation("uColorPicking");
    mULCPainterColor = mProgram->getUniformLocation("uPainterColor");
  }
  /* Occlusion program */
  if (mProgramOQ) {
    mULCMVPOcclusion = mProgramOQ->getUniformLocation("uMVP");
  }

  /* Shadow program */
  if (mProgramShadow) {
    mULCMVPShadow = mProgramShadow->getUniformLocation("uMVP");
  }

  /* ShadowColor program */
  if (mProgramShadowColor) {
    mULCMVPShadowColor = mProgramShadowColor->getUniformLocation("uMVP");
    mULCModelMatrixShadowColor = mProgramShadowColor->getUniformLocation("uModelMatrix");
  }

  /* AmbientOcclusion programs */
  if (mProgramAOGeometry) {
    mULCMVPAmbientOcclusion = mProgramAOGeometry->getUniformLocation("uMVP");
    mULCPositionAmbientOcclusion = mProgramAOGeometry->getUniformLocation("uMVPosition");
  }

  if (mProgramAOColor) {
    mULCSampleRadius = mProgramAOColor->getUniformLocation("uSampleRadius");
    mULCProjectionMatrix = mProgramAOColor->getUniformLocation("uP");
  }
}

inline void Mesh::initBuffers() {
  if (mIBO) {
    fLogI("RELOAD IBO");
    mIBO->reload();
  }
  if (mVBO) {
    fLogI("RELOAD VBO");
    mVBO->reload();
  }
}

inline void Mesh::initVAO() {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  mSampler->bind();
#endif
  mVAO->bind();

  mVBO->bind();
  mVBO->attributesSetForVAO();
  mVBO->send();

  if (mIBO) {
    mIBO->bind();
    mIBO->send();
  }

  flc::VertexArray::unbindVAO();
}

inline void Mesh::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
  mOcclusionMatrix = glm::scale(glm::mat4(1.0f), mVBO->getOcclusionBoxSize());
}

void Mesh::log() const {
  mVBO->log();
}

void Mesh::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

bool Mesh::getRenderItem(RenderItem &item) {
  item.mCount = mIBO ? mIBO->getElements() : mVBO->getElements();
  item.mDataType = GL_UNSIGNED_INT;
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  item.mHandles[RenderItem::eRenderHandleSampler] = 0;
#else
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
#endif
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mDiffuseMap ? mDiffuseMap->mTexture.mHandles[0] : 0;
  item.mHandles[RenderItem::eRenderHandleNormal] = mNormalMap ? mNormalMap->mTexture.mHandles[0] : 0;
  item.mHandles[RenderItem::eRenderHandleSpecular] = mSpecularMap ? mSpecularMap->mTexture.mHandles[0] : 0;
  item.mIndicesPointer = 0;
  item.mMode = GL_TRIANGLES;
  item.mRenderStatus = mIBO ? 0xf8 : 0xb8; // vao, ibo, diff, norm, spec, blend, cont, anim
  return true;
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
void Mesh::drawOcclusionBox(ICamera &/*camera*/) {
 // nothing
}
#else
void Mesh::drawOcclusionBox(ICamera &camera) {
  mProgramOQ->use();

  flc::Uniform::push(mULCMVPOcclusion, camera.getViewProjection() * mPhysicsMMC * mOcclusionMatrix);

  mOcclusionQuery.begin();

  glDrawArrays(mRenderMode, 0, gOQVertices);

  fLogC("drawOcclusionBox failed");

  mOcclusionQuery.end();

  flc::Program::disusePrograms();
}
#endif

} /* flf */
} /* flw */
