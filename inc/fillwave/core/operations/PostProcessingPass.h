/*
 * PostProcessingPass.h
 *
 *  Created on: 4 mar 2015
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

#ifndef SRC_OPERATIONS_POSTPROCESSINGPASS_H_
#define SRC_OPERATIONS_POSTPROCESSINGPASS_H_

#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/rendering/Texture2DRenderableDynamic.h>
#include <fillwave/common/Finishable.h>

namespace flw {
namespace flc {

/*! \class PostProcessingPass
 * \brief Defines one post processing pass.
 */

class PostProcessingPass : public flf::Finishable {
public:
  PostProcessingPass(flc::Program *p, flc::Texture2DRenderableDynamic *t, GLfloat lifetime);

  virtual ~PostProcessingPass() = default;

  flc::Texture2DRenderableDynamic *getFrame() const;

  flc::Program *getProgram() const;

private:
  flc::Texture2DRenderableDynamic *mFrame;
  flc::Program *mProgram;
};

} /* flc */
typedef std::unique_ptr<flc::PostProcessingPass> puPostProcessingPass;
} /* flw */

#endif /* SRC_OPERATIONS_POSTPROCESSINGPASS_H_ */
