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

#include <flw/flc/pipeline/Uniform.h>
#include <flw/flc/pipeline/Shader.h>
#include <flw/flc/extended/buffers/UniformBuffer.h>
#include <flw/cmn/Aliases.h>

class Attribute;

namespace flw {
namespace flc {

/*! \class Program
 * \brief Single GLSL program object.
 */
class Program final {
public:

  static constexpr const char* LIGHTS_BINDING_POINT_NAME = "uSpotLightsUBO";

  Program(const std::vector<flc::Shader *> &shaders, GLboolean skipLinking = GL_FALSE);

  ~Program();

  void link();

  /* Shaders */
  void use() const;

  static void useProgram(GLuint handle);

  static void disusePrograms();

  /* Uniforms */
  void uniformPush(const std::string& name, GLint data);

  void uniformPush(const std::string& name, GLint *data, GLint count);

  void uniformPush(const std::string& name, GLfloat data);

  void uniformPush(const std::string& name, GLfloat *data, GLint count);

  void uniformPush(const std::string& name, glm::mat3 data);

  void uniformPush(const std::string& name, glm::mat4 data);

  void uniformPush(const std::string& name, glm::mat4 *data, GLuint size);

  void uniformPush(const std::string& name, glm::vec2 data);

  void uniformPush(const std::string& name, glm::vec3 data);

  void uniformPush(const std::string& name, glm::vec3 *data, GLuint size);

  void uniformPush(const std::string& name, glm::vec4 data);

  /* Uniform blocks */
  GLint getUniformLocation(const std::string& name);

  GLuint getHandle() const;

  void reload();

  void log(const std::string& programName) const;

private:
  const bool mDelayedLinking;
  GLuint mHandle;
  std::vector<Uniform> mUniforms;
  std::vector<flc::Shader*> mShaders;

  inline void getUniforms();

  inline void attach(flc::Shader* shader);

  inline void detach(flc::Shader* shader);

  inline void load();

  inline void unload();

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  public:
    void getUniformBlock(const std::string& name, GLuint bindingPoint);
    void uniformBlockPush(const std::string& name, GLfloat* data, size_t size = 0);

  private:
    std::vector<pu<flc::UniformBuffer>> mUniformBuffers;

#endif
};

} /* flc */
} /* flw */
