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
#include <flw/Fillwave.h>

#include <memory>


using namespace flw;

struct Reloadable : public flf::IReloadable {
  Reloadable(Engine* engine, flc::VertexArray* vao)
    : flf::IReloadable(engine, engine->storeVAO(this, vao)) {

  }
  void initBuffers() override {};
  void initPipeline() override {};
  void initUniformsCache() override {};
  void initVAO() override {};
  void initVBO() override {};
};

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

static void BM_CachedIntegersByInstance(benchmark::State &state) {
  flf::TCache <flw::flf::MAX_CACHE_SIZE, int, int> integers;
  int i = 0;
  while(state.KeepRunning()) {
    integers.store(new int(i), i);
    i+=1;
  }
}

static void BM_CachedLargeTupleByInstance(benchmark::State &state) {
  flf::TCache <flw::flf::MAX_CACHE_SIZE
    , std::tuple<float, int, std::pair<std::string, std::vector<char>>>
    , int
    , float, int, std::pair<std::string, std::vector<char>>>
    tuples;
  int i = 0;
  while(state.KeepRunning()) {
    tuples.store(new std::tuple<float, int, std::pair<std::string, std::vector<char>>>(1.0f, 1.0, {}), i);
    i+=1;
  }
}

static void BM_CachedSamplersByInstance(benchmark::State &state) {
  flf::CacheSampler samplers;
  int i = 0;
  while(state.KeepRunning()) {
    samplers.store(new flc::Sampler(i), i);
    i++;
  }
}

static void BM_CachedVertexArraysByInstance(benchmark::State &state) {
  Engine* engine = new Engine(".", true);
  std::vector<Reloadable>  reloadables;

  while(state.KeepRunning()) {
    reloadables.emplace_back(engine, nullptr);
    reloadables.back().initBuffers();
  }
}

BENCHMARK(BM_CachedIntegersByInstance);
BENCHMARK(BM_CachedLargeTupleByInstance);
BENCHMARK(BM_CachedVertexArraysByInstance);
BENCHMARK(BM_CachedSamplersByInstance);

BENCHMARK_MAIN()