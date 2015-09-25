/*
 * EmiterPointGPU.h
 *
 *  Created on: 22 Apr 2015
 *      Author: Filip Wasil
 */

#ifndef EMITERPOINTGPU_H_
#define EMITERPOINTGPU_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/particles/EmiterPoint.h>
#include <fillwave/core/buffers/VertexBufferParticlesGPU.h>
#include <fillwave/core/pipeline/Fence.h>

namespace fillwave {
class Engine;
namespace particles {

/*! \class EmiterPointGPU
 * \brief Polynomial particle Emiter entirely computed on GPU.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointGPU : public EmiterPoint {
public:
   EmiterPointGPU(Engine* engine,
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
              GLfloat alphaCutOffLevel = 0.0);

   virtual ~EmiterPointGPU();

   void draw(space::Camera& camera);

   void update(GLfloat timeElapsedSec);

private:
   static const GLint mPingPongBuffers = 2;
   GLfloat mEmmisingSourceRate;
   GLuint mNoiseTextureHandle;
   glm::vec3 mAcceleration;
   glm::vec3 mStartVelocity;
   glm::vec3 mRobustnessVelocity;
   glm::vec3 mStartPosition;
   glm::vec3 mRobustnessPosition;
   glm::vec3 mCameraPosition;
   GLfloat mTimeDeltaEmiter;
   pProgram mProgramEmiter;
   GLuint mSrcIndex;
   puFence mFence;
   pVertexBufferParticlesGPU mVBOGPU[mPingPongBuffers];

   GLint mULCTimeEmiter,
      mULCEmissionRateEmiter,
      mULCModelMatrixEmiter,
      mULCCameraPositionEmiter,
      mULCHowManyEmiter,
      mULCAccelerationEmiter,
      mULCStartVelocityEmiter,
      mULCStartPositionEmiter,
      mULCLifeTimeEmiter,
      mULCRobustnessVelocityEmiter,
      mULCRobustnessPositionEmiter,
      mULCNoiseSamplerEmiter;

   GLint mULCModelMatrix,
      mULCViewProjectionMatrix,
      mULCCameraPosition,
      mULCTextureUnit,
      mULCTime,
      mULCAcceleration,
      mULCColor,
      mULCAlphaCutOff,
      mULCStartSize;

   void initBuffers();

   void initPipeline();

   void initVBO();

   void initVAO();

   void initUniformsCache();

   void coreDraw();

   void sort(glm::vec3 cameraPosition);
};

} /* particles */
typedef std::shared_ptr<particles::EmiterPointGPU> pEmiterPointGPU;
} /* fillwave */

#endif /* EMITERPOINTGPU_H_ */
