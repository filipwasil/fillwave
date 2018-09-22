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

#include "fillwave/loaders/FileLoader.h"

#include <fillwave/core/base/pipeline/Shader.h>

#include <sstream>

#include <fillwave/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FINFO | FDEBUG)

using namespace std;

namespace flw {
namespace flc {

Shader::Shader(GLuint shaderType, const std::string &shaderSource)
    : mType(shaderType)
    , mSource(shaderSource) {
  reload();
}

Shader::~Shader() {
  glDeleteShader(mHandle);
  fLogC("Shader destructor");
}

void Shader::loadSource() {
  if (!mSource.empty()) {
    const GLchar *source = (const GLchar *) mSource.c_str();
    glShaderSource(mHandle, 1, &source, nullptr);
    fLogC("Loading source code to the shader failed");
  } else {
    fLogF("Shader not found, or empty");
  }
}

void Shader::compile() {
  glCompileShader(mHandle);

  GLint status = 0;
  glGetShaderiv(mHandle, GL_COMPILE_STATUS, &status);
  fLogD("Compilation status: ", status);
  if (!status) {
    // There was an error, print it out
    GLint infoLogLength = 0;
    glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

    char *pShaderInfoLog = new char[infoLogLength];
    if (pShaderInfoLog) {
      glGetShaderInfoLog(mHandle, infoLogLength, NULL, pShaderInfoLog);
      fLogE("Compilation: ", pShaderInfoLog);
      delete []pShaderInfoLog;
    }
    glDeleteShader(mHandle);
    mHandle = 0;
    fLogF("Shader can not bee compiled");
    std::istringstream lines(mSource);
    std::string line;
    int i = 0;
    while (std::getline(lines, line)) {
      fLogE("[", i++, "] ", line.c_str());
    }
  }
}

void Shader::log(const std::string& programName) {
  int infologLength = 0;
  int maxLength;

  if (glIsShader(mHandle)) {
    glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &maxLength);
  } else {
    glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &maxLength);
  }
  std::vector<char> infoLog(maxLength);

  if (glIsShader(mHandle)) {
    glGetShaderInfoLog(mHandle, maxLength, &infologLength, infoLog.data());
  } else {
    glGetProgramInfoLog(mHandle, maxLength, &infologLength, infoLog.data());
  }

  if (infologLength > 0) {
    fLogI("%s\n", infoLog.data());
  }
  fLogI("%s\n", mSource.c_str());
  if (!programName.empty()) {
    flw::flf::WriteFile((programName + getDebugInfo().fileExtension).c_str(), mSource);
    return;
  }
}

GLuint Shader::getType() const {
  return mType;
}

GLuint Shader::getHandle() const {
  return mHandle;
}

void Shader::reload() {
  mHandle = glCreateShader(mType);
  fLogC("Shader creation failed");
  loadSource();
  compile();
}

Shader::DebugInfo Shader::getDebugInfo() const {
  switch (mType) {
    case GL_FRAGMENT_SHADER:
      return { "GL_FRAGMENT_SHADER", ".frag" };
    case GL_VERTEX_SHADER:
      return {"GL_VERTEX_SHADER", ".vert" };
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
    case GL_GEOMETRY_SHADER:
      return {"GL_GEOMETRY_SHADER", ".geom" };
    case GL_TESS_CONTROL_SHADER:
      return {"GL_TESS_CONTROL_SHADER", ".tesc" };
    case GL_TESS_EVALUATION_SHADER:
      return {"GL_TESS_EVALUATION_SHADER", ".tese" };
#endif
    default:
      fLogF("Shader type not recognized: ", mType);
      return DebugInfo();
  }
}

} /* flc */
} /* flw */

std::vector<flw::flc::Shader *>
operator+(std::vector<flw::flc::Shader*>& shaders, flw::flc::Shader* shader) {
  shaders.push_back(shader);
  return shaders;
}

