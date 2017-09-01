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

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/loaders/ProgramLoaderTypes.h>
#include <fillwave/loaders/ShaderLoader.h>
#include <fillwave/loaders/FileLoader.h>

namespace flw {
class Engine;
namespace flf {

/*! \class ProgramLoader
 * \brief Loads programs.
 */

class ProgramLoader : public ShaderLoader {
public:
  ProgramLoader(Engine *engine);

  virtual ~ProgramLoader() = default;

  flc::Program* getProgram(EProgram program);

  flc::Program* getQuadCustomFragmentShader(const std::string &shaderPath);

  flc::Program* getHUDCustomFragmentShader(const std::string &shaderPath);

  static void initDefaultUniforms(flc::Program *program);

private:
  flc::Shader* storeShader(const std::string& shaderPath, GLuint type);

  const std::vector<flc::Shader*> getCustomShader(GLuint type, const std::string& shaderPath) {
    std::string code;
    ReadFile(shaderPath.c_str(), code);
    return { storeShader(shaderPath, type) };
  }

  template <typename ...Args>
  const std::vector<flc::Shader*> getCustomShader(GLuint type, const std::string& shaderPath, Args ...args) {
    auto shaders = getCustomShader(args...);
    std::string code;
    ReadFile(shaderPath.c_str(), code);
    shaders.push_back( { storeShader(shaderPath, type) } );
    return shaders;
  }

  flc::Program* storeProgram(const std::string& name, const std::vector<flc::Shader*>& shaders);

public:
  template <typename ...Args>
  flc::Program* storeCustomProgram(const std::string& name, Args ...args) {
    return storeProgram(name, getCustomShader(args...));
  }

  Engine* mEngine;

  const char *mFeedbackVaryingsGPUEmiter[6];
};

} /* flf */
} /* flw */
