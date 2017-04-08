/*
 * Quad.h
 *
 *  Created on: May 25, 2015
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

#ifndef SRC_MODELS_SHAPES_QUAD_H_
#define SRC_MODELS_SHAPES_QUAD_H_

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/models/shapes/Shape.h>

namespace flw {
namespace flf {

/*! \class Quad
 * \brief Shape encapsulating vertices and indices for triangle drawn quad.
 */

class Quad : public Shape<flc::VertexBasic> {
public:
  Quad(GLfloat size = 1.0f) {

    mVertices.resize(6);

    flc::VertexBasic position[6] = {{{-size, -size, 0.0, 1.0}, {
                                                                    0.0, 0.0, 0.0, 1.0
                                                                },                       {0.0, 0.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0}, {0}, {
                                                                                                                                                 0.0
                                                                                                                                             }},
                                     {{size,  -size, 0.0, 1.0}, {   0.0, 0.0, 0.0, 1.0}, {
                                                                                          0.0, 0.0, -1.0
                                                                                         },                {1.0, 0.0, 0.0}, {1.0, 0.0}, {0}, {   0.0}},
                                     {{size,  size,  0.0, 1.0}, {   0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {1.0, 0.0, 0.0}, {1.0, 1.0}, {0}, {   0.0}},
                                     {{size,  size,  0.0, 1.0}, {   0.0, 0.0, 0.0, 1.0}, {
                                                                                          0.0, 0.0, -1.0
                                                                                         },                {1.0, 0.0, 0.0}, {1.0, 1.0}, {0}, {   0.0}},
                                     {{-size, size,  0.0, 1.0}, {   0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0}, {0}, {   0.0}},
                                     {{-size, -size, 0.0, 1.0}, {   0.0, 0.0, 0.0, 1.0}, {
                                                                                          0.0, 0.0, -1.0
                                                                                         },                {1.0, 0.0, 0.0}, {0.0, 0.0}, {0}, {   0.0}},
    };

    for (size_t i = 0; i < mVertices.size(); i++) {
      mVertices[i] = position[i];
      mIndices.push_back(i);
    }
  }

  virtual ~Quad() = default;
};

} /* flf */
} /* flw */

#endif /* SRC_MODELS_SHAPES_QUAD_H_ */
