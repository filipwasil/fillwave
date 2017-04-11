#pragma once

/*
* Copyright (c) 2017, Fillwave developers
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

#include <fillwave/core/pipeline/Uniform.h>
#include <fillwave/core/pipeline/Shader.h>
#include <fillwave/core/pipeline/UniformBuffer.h>
#include <memory>
#include <iostream>
#include <string>

#define FILLWAVE_LIGHTS_BINDING_POINT_NAME "uSpotLightsUBO"

class Attribute;

namespace flw {
namespace flc {

/*! \class Program
 * \brief Single GLSL program object.
 */
class Program {
public:
  Program(const std::vector<flc::Shader *> &shaders, GLboolean skipLinking = GL_FALSE);

  virtual ~Program();

  void link();

  /* Shaders */
  void attach(flc::Shader *shader);

  void detach(flc::Shader *shader);

  void use() const;

  static void useProgram(GLuint handle);

  static void disusePrograms();

  /* Uniforms */
  GLboolean checkUniform(const std::string &name);

  void uniformPush(std::string name, GLint data);

  void uniformPush(std::string name, GLint *data, GLint count);

  void uniformPush(std::string name, GLfloat data);

  void uniformPush(std::string name, GLfloat *data, GLint count);

  void uniformPush(std::string name, glm::mat3 data);

  void uniformPush(std::string name, glm::mat4 data);

  void uniformPush(std::string name, glm::mat4 *data, GLuint size);

  void uniformPush(std::string name, glm::vec2 data);

  void uniformPush(std::string name, glm::vec3 data);

  void uniformPush(std::string name, glm::vec3 *data, GLuint size);

  void uniformPush(std::string name, glm::vec4 data);

  /* Uniform blocks */
  GLint getUniformLocation(std::string name);

  void getUniformBlock(std::string name, GLuint bindingPoint);

  GLuint getHandle() const;

  void uniformBlockPush(std::string name, GLfloat *data);

  void reload();

  void log() const;

private:
  GLuint mHandle;
  std::vector<Uniform> mUniforms;
  std::vector<puUniformBuffer> mUnifromBuffers;
  GLboolean mDelayedLinking;
  std::vector<flc::Shader *> mShaders;

  void getUniforms();
};

} /* flc */
typedef std::unique_ptr<flc::Program> puProgram;

flc::Program *buildProgram(const std::vector<flc::Shader *> &shaders, GLboolean skipLinking = GL_FALSE);
} /* flw */
