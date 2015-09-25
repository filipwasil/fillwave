/*
 * UniformBuffer.h
 *
 *  Created on: May 18, 2014
 *      Author: Filip Wasil
 */

#ifndef UNIFORMBUFFER_H_
#define UNIFORMBUFFER_H_

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

#include <fillwave/core/buffers/Buffer.h>

#define FILLWAVE_LIGHTS_BINDING_POINT 0

#define FILLWAVE_LIGHTS_BINDING_POINT_NAME "uSpotLightsUBO"

namespace fillwave {
namespace core {

/*! \class UniformBuffer
 * \brief UniformBufferObject - UBO.
 */

class UniformBuffer: public Buffer {
public:
   UniformBuffer(std::string name,
		         GLuint index,
                 GLuint uniformBlockSize,
                 GLuint bindingPoint,
                 GLuint dataStoreModification = GL_STATIC_DRAW);

   virtual ~UniformBuffer();

   std::string getName();

   void bindRange(GLuint id = 0);

   void push(GLfloat* data);

private:
   std::string mName;
   GLuint mBindingPoint;
};

} /* core */
typedef std::shared_ptr<core::UniformBuffer> pUniformBuffer;
typedef std::shared_ptr<core::UniformBuffer> puUniformBuffer;
} /* fillwave */

#endif /* UNIFORMBUFFER_H_ */
