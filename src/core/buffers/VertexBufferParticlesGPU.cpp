/*
 * VertexBufferParticlesGPU.cpp
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) [2012] - [2015] Filip Wasil
 *  All Rights Reserved.
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *
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

#include <fillwave/core/buffers/VertexBufferParticlesGPU.h>
#include <fillwave/extras/Log.h>

FLOGINIT("VertexBufferParticlesGPU", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexBufferParticlesGPU::VertexBufferParticlesGPU(
		std::vector<VertexParticleGPU>& particles)
		: VertexBuffer<VertexParticleGPU>(particles, GL_DYNAMIC_COPY) {

}

VertexBufferParticlesGPU::~VertexBufferParticlesGPU() {

}

void VertexBufferParticlesGPU::log() {

}

} /* core */
} /* fillwave */
