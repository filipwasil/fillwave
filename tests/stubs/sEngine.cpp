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

#include <flw/Log.h>
#include <flw/Fillwave.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

FLOGINIT_DEFAULT()

namespace flw {

Engine::Engine(const std::string&, bool isEveryExtensionSuccessfullyLoaded)
  : mFileLoader("")
  , mProgramLoader(this) {
  // nothing
}

#if defined(FILLWAVE_BACKEND_OPENGL_ES_PC)
EnginePCGLES::EnginePCGLES(GLint argc, GLchar *const argv[], void (* (*getAddress)(const char*))())
  : Engine ("", true) {
  // nothing
}

EnginePCGLES::~EnginePCGLES() {
  // nothing
}
#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)

#else
EnginePC::EnginePC(GLint argc, GLchar *const argv[])
  : Engine ("", true) {
  // nothing
}

EnginePC::~EnginePC() {
  // nothing
}
#endif

Engine::~Engine() {
  // nothing
}

flc::Texture2D* Engine::storeTexture(const std::string & /*texturePath*/) {
  return nullptr;
}

} /* flw */
