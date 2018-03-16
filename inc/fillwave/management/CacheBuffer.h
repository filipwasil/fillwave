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

#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/core/buffers/VertexBufferFloat.h>
#include <fillwave/core/buffers/VertexBufferDebug.h>
#include <fillwave/core/buffers/VertexBufferParticlesGPU.h>
#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/models/base/IReloadable.h>

namespace flw {
namespace flf {

/*! \class CacheBuffer
 * \brief Connects VAO pointer and VAO's user pointer in single class.
 */
struct CacheBuffer {
  TCache<MAX_CACHE_SIZE, flc::VertexArray, IReloadable *> mVertexArrays;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferBasic, flc::VertexArray *, flf::TerrainConstructor *, GLint, GLfloat, std::vector<GLuint> &> mVertices;
  TCache<MAX_CACHE_SIZE, flc::IndexBuffer, flc::VertexArray *, std::vector<GLuint> &> mIndices;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferText, flc::VertexArray *, const std::vector<GLfloat> &, const std::vector<GLfloat> &> mVerticesText;
  TCache<MAX_CACHE_SIZE, std::vector<flc::VertexBufferParticlesGPU *>, flc::VertexArray *, std::vector<flc::VertexParticleGPU> &> mVerticesParticlesGPU;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferParticles, flc::VertexArray *, std::vector<GLfloat> &, std::vector<GLfloat> &, std::vector<GLfloat> &> mVerticesParticles;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferDebug, flc::VertexArray *, GLfloat> mVerticesDebugger;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferFloat, flc::VertexArray *, std::vector<flc::VertexFloat> &> mVerticesFloat;
  TCache<MAX_CACHE_SIZE, flc::VertexBufferPosition, flc::VertexArray *, std::vector<flc::VertexPosition> &> mVerticesPosition;
};

} /* flf */
} /* flw */
