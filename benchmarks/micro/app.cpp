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


#include "context.h"
#include "bSkyboxScene.h"
#include <benchmark/benchmark.h>
#include <memory>

using namespace flw;

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

static void BM_EngineDrawEmptyFrame(benchmark::State &state) {
  initContext();
  auto* engine = new flw::Engine(".");
  while (state.KeepRunning()) {
    engine->draw(0.0f);
  }
  delete engine;
}

// Register the function as a benchmark
BENCHMARK(BM_EngineDrawEmptyFrame);

// Define another benchmark
static void BM_EngineDrawSkyboxFrame(benchmark::State &state) {
  initContext();
  auto* engine = new flw::Engine(".");
  engine->setCurrentScene(std::make_unique<SkyboxScene>(engine));
  while (state.KeepRunning()) {
    engine->draw(0.0f);
  }
  delete engine;
}

// Register another function as a benchmark
BENCHMARK(BM_EngineDrawSkyboxFrame);

BENCHMARK_MAIN()