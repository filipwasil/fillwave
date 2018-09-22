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

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/pipeline/Attribute.h>

#include <fillwave/Log.h>

FLOGINIT_MASK(FFATAL | FERROR)

namespace flw {
namespace flc {

Program::Program(const std::vector<flc::Shader*>& shaders, GLboolean skipLinking)
    : mDelayedLinking(skipLinking)
    , mShaders(shaders) {
  load();
}

Program::~Program() {
  unload();
}

void Program::attach(flc::Shader* shader) {
  if (mHandle) {
    glAttachShader(mHandle, shader->getHandle());
    fLogC("attach shader ", shader->getHandle(), "to program ", mHandle);
  }
}

void Program::detach(flc::Shader* shader) {
  if (mHandle) {
    glDetachShader(mHandle, shader->getHandle());
    fLogC("detach shader");
  }
}

GLuint Program::getHandle() const {
  return mHandle;
}

void Program::link() {
  glLinkProgram(mHandle);

  GLint status = 0;
  glGetProgramiv(mHandle, GL_LINK_STATUS, &status);

  if (!status) {
    GLint infoLogLength = 0;
    glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength) {
      if (GLchar *pInfoLog = new GLchar[infoLogLength]) {
        glGetProgramInfoLog(mHandle, infoLogLength, nullptr, pInfoLog);
        fLogF("linking : ", pInfoLog);
        delete []pInfoLog;
      }
    }
    mHandle = 0;
  }

  use();
  getUniforms();

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  getUniformBlock(FILLWAVE_LIGHTS_BINDING_POINT_NAME, FILLWAVE_LIGHTS_BINDING_POINT);
#endif
  disusePrograms();
}

void Program::disusePrograms() {
  glUseProgram(0);
  fLogC("disuse programs");
}

void Program::useProgram(GLuint handle) {
  glUseProgram(handle);
  fLogC("disuse programs");
}

void Program::use() const {
  glUseProgram(mHandle);
  fLogC("use");
}

void Program::uniformPush(const std::string& name, GLint data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"int ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, GLint *data, GLint count) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data, count);
      return;
    }
  }
  fLogE("Can not find \"int ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, GLfloat data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"float ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, GLfloat *data, GLint count) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data, count);
      return;
    }
  }
  fLogE("Can not find \"float ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::mat3 data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"glm::mat3 ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::mat4 data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"glm::mat4 ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::mat4 *data, GLuint size) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data, size);
      return;
    }
  }
  fLogE("Can not find \"glm::mat4", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::vec2 data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"glm::vec4 ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::vec3 data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"glm::vec3 ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::vec3 *data, GLuint size) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data, size);
      return;
    }
  }
  fLogE("Can not find %d \"glm::vec3 ", name, "\" uniform name in program");
}

void Program::uniformPush(const std::string& name, glm::vec4 data) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      it.push(data);
      return;
    }
  }
  fLogE("Can not find \"glm::vec4 ", name, "\" uniform name in program");
}

inline void Program::getUniforms() {
  if (mUniforms.empty()) {
    GLint howMany = -1;
    glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &howMany);
    for (GLint i = 0; i < howMany; ++i) {
      GLint name_len = -1, num = -1;
      GLenum type = GL_ZERO;
      char name[100];
      glGetActiveUniform(mHandle, GLuint(i), sizeof(name) - 1, &name_len, &num, &type, name);
      name[name_len] = 0;
      GLint location = glGetUniformLocation(mHandle, name);
      fLogD("Uniform name=", name, ", location=", location, ", type=", type, ", num=", num);
      mUniforms.push_back(Uniform(name, type, num, location));
    }
  }
}

GLint Program::getUniformLocation(const std::string& name) {
  for (auto &it : mUniforms) {
    if (it.isName(name)) {
      return it.getLocation();
    }
  }
  fLogD("Can not find uniform ", name, " in program");
  return FILLWAVE_UNIFORM_NOT_FOUND;
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
void Program::getUniformBlock(const std::string& name, GLuint bindingPoint) {
  GLint howMany = -1;
  GLint uniformBlockSize = 0;
  glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_BLOCKS, &howMany);
  for (GLint i = 0; i < howMany; ++i) {
    GLint name_len = -1;
    std::vector<char> nameFromProgram(100);
    glGetActiveUniformBlockName(mHandle, GLuint(i), sizeof(nameFromProgram) - 1, &name_len, nameFromProgram.data());
    glGetActiveUniformBlockiv(mHandle, GLuint(i), GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
    nameFromProgram[name_len] = 0;
    if (std::string(nameFromProgram.data()) == name) {
      fLogD("Uniform block name=", name, ", index=", GLuint(i), ", size=%d ", uniformBlockSize);
      GLuint blockIndex = glGetUniformBlockIndex(mHandle, nameFromProgram.data());
      glUniformBlockBinding(mHandle, blockIndex, bindingPoint);
      mUnifromBuffers.push_back(std::make_unique<UniformBuffer>(std::string(name),
                                                                blockIndex,
                                                                uniformBlockSize,
                                                                bindingPoint,
                                                                GL_DYNAMIC_DRAW));
    }
  }
}

void Program::uniformBlockPush(const std::string& name, GLfloat *data) {
  for (auto &it : mUnifromBuffers) {
    if (it->getName() == name) {
      it->push(data);
      return;
    }
  }
  fLogE("Uniform buffer ", name, " not found");
}

#endif

void Program::log(const std::string& programName) const {
  GLint infologLength = 0;
  GLint value;
  glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &value);
  std::vector<GLchar> infoLog(value);
  fLogI("Shaders\n %du", mShaders.size());
  if (glIsProgram(mHandle)) {
    fLogI("Program handle ", mHandle, " is valid");
  } else {
    fLogI("Program handle ", mHandle, " is not valid");
  }
  glGetProgramInfoLog(mHandle, value, &infologLength, infoLog.data());
  fLogI("INFOR LOG: ", infoLog.data());
  glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &value);
  fLogI("GL_INFO_LOG_LENGTH: ", value);
  glGetProgramiv(mHandle, GL_VALIDATE_STATUS, &value);
  fLogI("GL_VALIDATE_STATUS: ", value);
  glGetProgramiv(mHandle, GL_ATTACHED_SHADERS, &value);
  fLogI("GL_ATTACHED_SHADERS: ", value);
  glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, &value);
  fLogI("GL_ACTIVE_ATTRIBUTES: ", value);
  glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, &value);
  fLogI("GL_ACTIVE_UNIFORMS: ", value);
  glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &value);
  fLogI("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH: ", value);
  glGetProgramiv(mHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &value);
  fLogI("GL_ACTIVE_UNIFORM_MAX_LENGTH: ", value);

  fLogI("Uniforms:\n ", mUniforms.size());
  for (auto& it : mUniforms) {
    it.log();
  }
  for (auto& it : mShaders) {
    fLogI("Shader:\n");
    it->log(programName);
  }
}

void Program::load() {
  mHandle = glCreateProgram();
  fLogC("Program creation failed");
  for (auto& it : mShaders) {
    attach(it);
    fLogC("Failed to attach shader of type ", it->getDebugInfo().type);
  }
  if (!mDelayedLinking) {
    link();
  } else {
    fLogD("Program linking has be done manually\n");
  }
  fLogC("Program linking failed");
}

void Program::unload() {
  for (auto &it : mShaders) {
    detach(it);
  }
  glDeleteProgram(mHandle);
  fLogC("Deleted program");
}

void Program::reload() {
  unload();
  load();
}

} /* flc */
} /* flw */
