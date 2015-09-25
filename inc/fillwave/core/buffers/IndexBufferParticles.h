/*
 * IndexBufferParticles.h
 *
 *  Created on: 16 Apr 2015
 *      Author: filip
 */

#ifndef INDEXBUFFERPARTICLES_H_
#define INDEXBUFFERPARTICLES_H_

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

#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/Math.h>

namespace fillwave {
namespace core {

/*! \class IndexBufferParticles
 * \brief IBO to use with particles.
 */

class IndexBufferParticles: public IndexBuffer {
public:
   IndexBufferParticles(GLuint elements);
   virtual ~IndexBufferParticles();
   GLuint* getDataInternal();
};

} /* core */
typedef std::shared_ptr<core::IndexBufferParticles> pIndexBufferParticles;
} /* fillwave */

#endif /* INDEXBUFFERPARTICLES_H_ */
