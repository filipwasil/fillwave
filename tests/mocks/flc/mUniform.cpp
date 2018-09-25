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

}

void Uniform::push(GLint *value, GLint size) {

}

void Uniform::push(GLfloat value) {

}

void Uniform::push(GLfloat *value, GLint size) {

}

void Uniform::push(glm::vec2 value) {

}

void Uniform::push(glm::vec3 value) {

}

void Uniform::push(glm::vec4 value) {

}

void Uniform::push(glm::mat2 value) {

}

void Uniform::push(glm::mat3 value) {

}

void Uniform::push(glm::mat4 value) {

}

void Uniform::push(glm::vec3 *value, GLuint size) {

}

void Uniform::push(glm::mat4 *value, GLuint size) {

}

/* Direct method */

void Uniform::push(GLint location, GLint data) {

}

void Uniform::push(GLint location, GLuint data) {
  push(location, static_cast<GLint>(data));
}

void Uniform::push(GLint location, bool data) {
  push(location, static_cast<GLint>(data));
}

void Uniform::push(GLint location, GLint *data, GLint count) {

}

void Uniform::push(GLint location, GLfloat data) {

}

void Uniform::push(GLint location, GLfloat *data, GLint count) {

}

void Uniform::push(GLint location, glm::vec2 data) {

}

void Uniform::push(GLint location, glm::vec3 data) {

}

void Uniform::push(GLint location, glm::vec4 data) {

}

void Uniform::push(GLint location, glm::mat2 data) {

}

void Uniform::push(GLint location, glm::mat3 data) {

}

void Uniform::push(GLint location, glm::mat4 data) {

}

void Uniform::push(GLint location, glm::mat4 *data, GLuint size) {

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

}

} /* flc */
} /* flw */
