/*
 * VertexBufferParticles.h
 *
 *  Created on: Aug 30, 2014
 *      Author: Filip Wasil
 */

#ifndef VERTEXBUFFERPARTICLES_H_
#define VERTEXBUFFERPARTICLES_H_

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

/*! \struct VertexParticle
 * \brief Stores the particle vertex data.
 */

struct VertexParticle {
   float velocity[3];
   float startPosition[3];
   float startTime;
};

/*! \class VertexBufferParticles
 * \brief Vertex buffer specialized with VertexParticle data structure.
 */

class VertexBufferParticles : public VertexBuffer<VertexParticle> {
public:
   VertexBufferParticles(std::vector<GLfloat>& velocities,
                         std::vector<GLfloat>& positions,
                         std::vector<GLfloat>& times);
   virtual ~VertexBufferParticles();
   void log();
   };

} /* core */
typedef std::shared_ptr<core::VertexBufferParticles> pVertexBufferParticles;
} /* fillwave */

#endif /* VERTEXBUFFERPARTICLES_H_ */
