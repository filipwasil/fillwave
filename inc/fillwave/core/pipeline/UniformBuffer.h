/*
 * UniformBuffer.h
 *
 *  Created on: May 18, 2014
 *      Author: Filip Wasil
 *
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

#ifndef UNIFORMBUFFER_H_
#define UNIFORMBUFFER_H_

#include <fillwave/core/buffers/IBuffer.h>
#include <string>

namespace flw {
namespace flc {

/*! \class UniformBuffer
 * \brief UniformBufferObject - UBO.
 */

class UniformBuffer : public IBuffer {
public:
  UniformBuffer(std::string name,
      GLuint index,
      GLuint uniformBlockSize,
      GLuint bindingPoint,
      GLuint dataStoreModification = GL_STATIC_DRAW);

  virtual ~UniformBuffer();

  std::string getName();

  void bindRange(GLuint id = 0);

  void push(GLfloat *data);

  void emptyCPU() override;

  void emptyGPU() override;

private:
  std::string mName;
  GLuint mBindingPoint;
};

} /* flc */
typedef std::shared_ptr<flc::UniformBuffer> pUniformBuffer;
typedef std::shared_ptr<flc::UniformBuffer> puUniformBuffer;
} /* flw */

#endif /* UNIFORMBUFFER_H_ */
