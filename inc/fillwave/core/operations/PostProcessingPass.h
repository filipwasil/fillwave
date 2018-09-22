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
  PostProcessingPass(flc::Program* p, flc::Texture2DRenderableDynamic* t, GLfloat lifetime);

  ~PostProcessingPass() override;

  PostProcessingPass(const PostProcessingPass& arg);

  PostProcessingPass& operator= (const PostProcessingPass& postProcessingPass);

  flc::Texture2DRenderableDynamic* getFrame() const;

  flc::Program* getProgram() const;

private:
  flc::Texture2DRenderableDynamic* mFrame;
  flc::Program* mProgram;
};

} /* flc */
} /* flw */
