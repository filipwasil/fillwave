/*
 * ProgramPipeline.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef PROGRAMPIPELINE_H_
#define PROGRAMPIPELINE_H_

#include <fillwave/core/GLObject.h>

#ifdef FILLWAVE_GLES_3_0
#else

namespace fillwave {
namespace core {

/*! \class ProgramPipeline
 * \brief Not used.
 *
 */

class ProgramPipeline : public GLObject {
public:
  ProgramPipeline(GLbitfield stage, GLsizei howMany = 1);

  virtual ~ProgramPipeline();

  void bind(GLuint id = 0) const;

  void use(GLuint programHandle, GLuint id = 0) const;

private:
  GLbitfield mStage;
  GLuint mTarget;
};

} /* core */
} /* fillwave */

#endif /* PROGRAMPIPELINE_H_ */

#endif /* FILLWAVE_GLES_3_0 */
