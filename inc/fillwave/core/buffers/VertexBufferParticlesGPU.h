/*
 * VertexBufferParticlesGPU.h
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

#ifndef VertexBufferParticlesGPU_H_
#define VertexBufferParticlesGPU_H_

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

#include <fillwave/core/buffers/VertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexParticleGPU
 * \brief Stores the particle vertex data computed entirely on GPU.
 */

struct VertexParticleGPU {
   float position[3];
   float velocity[3];
   float size;
   float currentTime;
   float lifetime;
   float cameraDistance;
};

/*! \class VertexBufferParticlesGPU
 * \brief Vertex buffer specialized with VertexParticleGPU data structure.
 */

class VertexBufferParticlesGPU : public VertexBuffer<VertexParticleGPU> {
public:
   VertexBufferParticlesGPU(std::vector<VertexParticleGPU>& particles);
   virtual ~VertexBufferParticlesGPU();
   void log();
   };

} /* core */
typedef std::shared_ptr<core::VertexBufferParticlesGPU> pVertexBufferParticlesGPU;
} /* fillwave */

#endif /* VertexBufferParticlesGPU_H_ */
