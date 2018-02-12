#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

class Uniform final {
public:
  Uniform(const std::string& name, GLuint type, GLsizei size, GLint location);

  bool isName(const std::string &name) const;

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
} /* flw */
