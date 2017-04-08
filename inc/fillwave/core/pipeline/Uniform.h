/*
 * Uniform.h
 *
 *  Created on: May 11, 2014
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

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <fillwave/OpenGL.h>

#include <fillwave/Math.h>

#include <string>
#include <memory>

namespace flw {
namespace flc {

/*! \type UniformData
 * \brief Uniform data structure.
 */

typedef union UniformData {
  GLenum glEnum;
  GLbitfield glBitfield;
  GLuint glUint;
  GLint glInt;
  GLsizei glSizei;
  GLboolean glBoolean;
  GLbyte glByte;
  GLshort glShort;
  GLubyte glUbyte;
  GLushort glUshort;
  //GLulong glUlong;
  GLfloat glFloat;
  GLfloat glVec2[2];
  GLfloat glVec3[3];
  GLfloat glVec4[4];
  GLfloat glMat2[4];
  GLfloat glMat3[9];
  GLfloat glMat4[16];
} UniformData;

/*! \class Uniform
 * \brief Uniform.
 */

class Uniform {
public:
  Uniform(std::string name, GLuint type, GLsizei size, GLint location);

  virtual ~Uniform() = default;

  GLboolean isName(std::string &name) const;

  GLuint getType() const;

  GLsizei getSize() const;

  GLint getLocation() const;

  void setName(std::string name);

  void setType(GLuint size);

  void setSize(GLsizei size);

  void setLocation(GLint location);

  void setData(UniformData data);

  /* Slow push with O(n) where n is uniform vector size */

  void push(GLint value);

  void push(GLint *value, GLint size);

  void push(GLfloat value);

  void push(GLfloat *value, GLint size);

  void push(glm::mat4 value);

  void push(glm::mat4 *value, GLuint size);

  void push(glm::mat3 value);

  void push(glm::mat2 value);

  void push(glm::vec2 value);

  void push(glm::vec3 value);

  void push(glm::vec3 *value, GLuint size);

  void push(glm::vec4 value);

  /* Fast push with O(1) */

  static void push(GLint location, GLint data);

  static void push(GLint location, GLuint data);

  static void push(GLint location, bool data);

  static void push(GLint location, GLint *data, GLint count);

  static void push(GLint location, GLfloat data);

  static void push(GLint location, GLfloat *data, GLint count);

  static void push(GLint location, glm::mat2 data);

  static void push(GLint location, glm::mat3 data);

  static void push(GLint location, glm::mat4 data);

  static void push(GLint location, glm::mat4 *data, GLuint size);

  static void push(GLint location, glm::vec2 data);

  static void push(GLint location, glm::vec3 data);

  static void push(GLint location, glm::vec4 data);

  void log() const;

private:
  std::string mName;
  GLenum mType;
  GLsizei mSize;
  GLint mLocation;
  UniformData mData;
};

} /* flc */
typedef std::unique_ptr<flc::Uniform> puUniform;
} /* flw */

#endif /* UNIFORM_H_ */
