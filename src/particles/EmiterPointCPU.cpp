/*
 * EmiterPointCPU.cpp

 *
 *  Created on: Sep 10, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/particles/EmiterPointCPU.h>
#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/Fillwave.h>

FLOGINIT("EmiterPointCPU", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace particles {

EmiterPointCPU::EmiterPointCPU(Engine* engine,
      GLfloat emitingSourceRate,
      GLuint howMany,
      glm::vec4 color,
      glm::vec3 acceleration,
      glm::vec3 startVelocity,
      glm::vec3 robustnessVelocity,
      glm::vec3 startPosition,
      glm::vec3 robustnessPosition,
      GLfloat startSize,
      GLfloat lifetime,
      pTexture texture,
      GLenum blendingSource,
      GLenum blendingDestination,
      GLboolean depthTesting,
      GLfloat alphaCutOffLevel)
:EmiterPoint(engine,
 howMany,
 startSize,
 lifetime,
 texture,
 color,
 blendingSource,
 blendingDestination,
 depthTesting,
 alphaCutOffLevel),
 mAcceleration(acceleration),
 mStartVelocity(startVelocity),
 mStartPosition(startPosition) {

   loader::ProgramLoader loader;

   mProgram = loader.getParticleCPU(engine);

   /* Fill buffers */
   GLfloat time = 0.0f; // start time
   std::vector<GLfloat> times;
   std::vector<GLfloat> positions;
   std::vector<GLfloat> velocities;
   std::vector<GLfloat> cameraDistanceTF;

   times.reserve(howMany);
   positions.reserve(3*howMany);
   velocities.reserve(3*howMany);
   cameraDistanceTF.reserve(howMany);

   for (GLint i = 0; i < howMany; i++) {

      times.push_back(time);
      time += 1.0f/lifetime;

      /* particles velocity */
      GLfloat x = (((GLfloat)rand() / (GLfloat)RAND_MAX)) * robustnessVelocity.x * 1.0f - robustnessVelocity.x * 0.5f;
      GLfloat y = (((GLfloat)rand() / (GLfloat)RAND_MAX)) * robustnessVelocity.y * 1.0f - robustnessVelocity.y * 0.5f;
      GLfloat z = (((GLfloat)rand() / (GLfloat)RAND_MAX)) * robustnessVelocity.z * 1.0f - robustnessVelocity.z * 0.5f;
      velocities.push_back(x);
      velocities.push_back(y);
      velocities.push_back(z);

      /* emiter surface shape */
      x = ((GLfloat)rand() / (GLfloat)RAND_MAX) * robustnessPosition.x * 1.0f - robustnessPosition.x * 0.5f;
      y = ((GLfloat)rand() / (GLfloat)RAND_MAX) * robustnessPosition.y * 1.0f - robustnessPosition.y * 0.5f;
      z = ((GLfloat)rand() / (GLfloat)RAND_MAX) * robustnessPosition.z * 1.0f - robustnessPosition.z * 0.5f;
      positions.push_back(x);
      positions.push_back(y);
      positions.push_back(z);

      cameraDistanceTF.push_back(0.0);
   }

   /* Initialize OpenGL stuff */
   mVBO = pVertexBufferParticles (new core::VertexBufferParticles(velocities, positions, times));//xxx todo store in engine
   mIBO = pIndexBufferParticles (new core::IndexBufferParticles(howMany));//xxx todo store in engine

   initPipeline();
   initVBO();
   initVAO();
   initUniformsCache();
}

void EmiterPointCPU::update(GLfloat timeElapsedSec) {
   mProgram->use();
   core::Uniform::push(mULCTimeElapsed, timeElapsedSec);
   core::Program::disusePrograms();
}

void EmiterPointCPU::draw(space::Camera& camera) {
   /* Parent-children transformations */
   updateMatrixTree();

   mCameraPosition = camera.getTranslation();

   mProgram->use();

   core::Uniform::push(mULCModelMatrix, mTransformation);
   core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
   core::Uniform::push(mULCCameraPosition, mCameraPosition);
   core::Uniform::push(mULCPointSize, mStartSize);
   core::Uniform::push(mULCColor, mColor);
   core::Uniform::push(mULCAcceleration, mAcceleration);
   core::Uniform::push(mULCLifeTime, mLifetime);
   core::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);
//   core::Uniform::push(mULCSourcePosition, mTranslation);

   coreDraw();

   core::Program::disusePrograms();
}

inline void EmiterPointCPU::coreDraw() {

   mVAO->bind();

   if (mTexture) {
      mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
   }

   if (not mDepthTesting) {
      glDepthMask(GL_FALSE);
   }

   glEnable (GL_BLEND);
   glBlendFunc (mBlending.mSource, mBlending.mDestination);
//   glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
//   glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
   glDrawElements(GL_POINTS, mIBO->getElements(), GL_UNSIGNED_INT, (GLvoid*) 0);
   FLOG_CHECK("Draw elements");
   glDisable(GL_BLEND);
   if (not mDepthTesting) {
      glDepthMask(GL_TRUE);
   }

   core::Texture2D::unbind2DTextures();

   mVAO->unbind();
}

EmiterPointCPU::~EmiterPointCPU() {

}

inline void EmiterPointCPU::initBuffers() {
   if (mIBO) {
      mIBO->reload();
   }
   if (mVBO) {
      mVBO->reload();
   }
}

inline void EmiterPointCPU::initPipeline() {
   mProgram->use();
   mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
   core::Program::disusePrograms();
}

inline void EmiterPointCPU::initUniformsCache() {
   mULCTimeElapsed = mProgram->getUniformLocation("uTimeElapsed");
   mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
   mULCViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
   mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
   mULCPointSize = mProgram->getUniformLocation("uPointSize");
   mULCColor = mProgram->getUniformLocation("uColor");
   mULCAcceleration = mProgram->getUniformLocation("uAcceleration");
   mULCLifeTime = mProgram->getUniformLocation("uLifeTime");
   mULCAlphaCutOff = mProgram->getUniformLocation("uAlphaCutOff");
//   mULCSourcePosition = mProgram->getUniformLocation("uSourcePosition");
   mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

inline void EmiterPointCPU::initVAO() {
   mSampler->bind();
   mVAO->bind();
   mVBO->bind();
   mVBO->setReady();
   mVBO->send();
   mVBO->attributesSetForVAO();
   mIBO->bind();
   mIBO->setReady();
   mIBO->send();
   mVAO->unbind();
}

inline void EmiterPointCPU::initVBO() {
   mVBO->getAttributes(mProgram->getHandle());
   mVBO->attributesBind(mProgram);
}

} /* particles */
} /* fillwave */
