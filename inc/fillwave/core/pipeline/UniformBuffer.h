/*
 * UniformBuffer.h
 *
 *  Created on: May 18, 2014
 *      Author: Filip Wasil
 */

#ifndef UNIFORMBUFFER_H_
#define UNIFORMBUFFER_H_

#include <fillwave/core/buffers/IBuffer.h>

namespace fillwave {
namespace core {

/*! \class UniformBuffer
 * \brief UniformBufferObject - UBO.
 */

class UniformBuffer: public IBuffer {
 public:
	UniformBuffer(
	   std::string name,
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
