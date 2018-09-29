/*
 * Fillwave.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Fillwave developers
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

#include <benchmark/benchmark.h>
#include <flw/flf/models/Model.h>

#include <memory>

using namespace flw;

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

static void BM_ModelResourcesCaching(benchmark::State &state) {

  Engine* engine = nullptr;
  flc::Program* program = nullptr;
  const flf::Shape<flc::VertexBasic>& shape {};
  flc::Texture2D* diffuseMap = nullptr;
  flc::Texture2D* normalMap = nullptr;
  flc::Texture2D* specularMap = nullptr;
  const Material material {};

  flf::Model m(engine, program, shape, diffuseMap, normalMap, specularMap, material);
}

// Register the function as a benchmark
BENCHMARK(BM_ModelResourcesCaching);

// Define another benchmark
static void BM_EngineDrawSkyboxFrame(benchmark::State &state) {

}

// Register another function as a benchmark
BENCHMARK(BM_EngineDrawSkyboxFrame);

BENCHMARK_MAIN()