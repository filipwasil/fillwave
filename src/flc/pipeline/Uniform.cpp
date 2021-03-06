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

#include <flw/flc/pipeline/Uniform.h>

#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

Uniform::Uniform(const std::string& name, GLuint type, GLsizei size, GLint location)
  : mName(name)
  , mType(type)
  , mSize(size)
  , mLocation(location) {
  // nothing
}

bool Uniform::isName(const std::string& name) const {
  return mName == name;
}

GLint Uniform::getLocation() const {
  return mLocation;
}

/* TODO make a template here */
template <class T>
void pushToProgram(T value);

void Uniform::push(GLint value) {
  glUniform1i(mLocation, value);
  fLogC("Uniform push failed");
}

void Uniform::push(GLint *value, GLint size) {
  glUniform1iv(mLocation, size, value);
  fLogC("Uniform push failed");
}

void Uniform::push(GLfloat value) {
  glUniform1f(mLocation, value);
  fLogC("Uniform push failed");
}

void Uniform::push(GLfloat *value, GLint size) {
  glUniform1fv(mLocation, size, value);
  fLogC("Uniform push failed");
}

void Uniform::push(glm::vec2 value) {
  glUniform2fv(mLocation, 1, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::vec3 value) {
  glUniform3fv(mLocation, 1, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::vec4 value) {
  glUniform4fv(mLocation, 1, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::mat2 value) {
  glUniformMatrix2fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::mat3 value) {
  glUniformMatrix3fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::mat4 value) {
  glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
  fLogC("Uniform push failed");
}

void Uniform::push(glm::vec3 *value, GLuint size) {
  glUniform3fv(mLocation, size, (GLfloat *) value);
  fLogC("Uniform push failed");
}

void Uniform::push(glm::mat4 *value, GLuint size) {
  glUniformMatrix4fv(mLocation, size, GL_FALSE, (GLfloat *) value);
  fLogC("Uniform push failed");
}

/* Direct method */

void Uniform::push(GLint location, GLint data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform1i(location, data);
    fLogC("Uniform int push failed");
  }
}

void Uniform::push(GLint location, GLuint data) {
  push(location, static_cast<GLint>(data));
}

void Uniform::push(GLint location, bool data) {
  push(location, static_cast<GLint>(data));
}

void Uniform::push(GLint location, GLint *data, GLint count) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform1iv(location, count, data);
    fLogC("Uniform var int push failed");
  }
}

void Uniform::push(GLint location, GLfloat data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform1f(location, data);
    fLogC("Uniform float push failed");
  }
}

void Uniform::push(GLint location, GLfloat *data, GLint count) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform1fv(location, count, data);
    fLogC("Uniform var float push failed");
  }
}

void Uniform::push(GLint location, glm::vec2 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform2fv(location, 1, glm::value_ptr(data));
    fLogC("Uniform vec2 push failed");
  }
}

void Uniform::push(GLint location, glm::vec3 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform3fv(location, 1, glm::value_ptr(data));
    fLogC("Uniform vec3 push failed");
  }
}

void Uniform::push(GLint location, glm::vec4 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniform4fv(location, 1, glm::value_ptr(data));
    fLogC("Uniform vec4 push failed");
  }
}

void Uniform::push(GLint location, glm::mat2 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(data));
    fLogC("Uniform mat2 push failed");
  }
}

void Uniform::push(GLint location, glm::mat3 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
    fLogC("Uniform mat3 push failed");
  }
}

void Uniform::push(GLint location, glm::mat4 data) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No int uniform under location ", location);
  } else {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
    fLogC("Uniform mat4 push failed");
  }
}

void Uniform::push(GLint location, glm::mat4 *data, GLuint size) {
  if (location == FILLWAVE_UNIFORM_NOT_FOUND) {
    fLogE("No mat4 uniform under location ", location);
  } else {
    glUniformMatrix4fv(location, size, GL_FALSE, reinterpret_cast<GLfloat *>(data));
    fLogC("Uniform var mat4 push failed");
  }
}

void Uniform::setName(std::string name) {
  mName = name;
}

GLuint Uniform::getType() const {
  return mType;
}

void Uniform::setType(GLuint type) {
  mType = type;
}

GLsizei Uniform::getSize() const {
  return mSize;
}

void Uniform::setSize(GLsizei size) {
  mSize = size;
}

void Uniform::setLocation(GLint location) {
  mLocation = location;
}

void Uniform::setData(UniformData data) {
  mData = data;
}

void Uniform::log() const {
  fLogI("Name: ", mName.c_str());
  fLogI("Location: ", mLocation);
  fLogI("Type: ", mType);
  fLogI("Size: ", mSize);
}

} /* flc */
} /* flw */
