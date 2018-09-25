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

#include <flw/core/pipeline/Shader.h>

using namespace std;

namespace flw {
namespace flc {

Shader::Shader(GLuint shaderType, const std::string &shaderSource)
  : mType(shaderType)
  , mSource(shaderSource) {
  reload();
}

Shader::~Shader() {

}

void Shader::loadSource() {

}

void Shader::compile() {

}

void Shader::log(const std::string& programName) {
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
  mHandle = 1;
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

