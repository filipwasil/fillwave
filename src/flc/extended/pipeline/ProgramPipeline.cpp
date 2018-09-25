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

#include <flw/flc/pipeline/ProgramPipeline.h>

namespace flw {
namespace flc {

ProgramPipeline::ProgramPipeline(GLbitfield stage, GLsizei howMany)
  : mHowMany(howMany)
  , mStage(stage) {
  glGenProgramPipelines(mHowMany, mHandles);
}

ProgramPipeline::~ProgramPipeline() {
  glDeleteProgramPipelines(mHowMany, mHandles);
}

void ProgramPipeline::bind(GLuint id) const {
  glBindProgramPipeline(mHandles[id]);
}

void ProgramPipeline::use(GLuint programHandle, GLuint id) const {
  glUseProgramStages(mHandles[id], mStage, programHandle);
}

GLuint ProgramPipeline::getHandle(GLuint id) {
  return id < FILLWAVE_GLOBJECTS_MAX ? mHandles[id] : 0;
}

} /* flc */
} /* flw  */
