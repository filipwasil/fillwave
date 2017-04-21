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

#include <googlebenchmark/include/benchmark/benchmark.h>

#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Profiler.h>
#include <fillwave/Log.h>

using namespace flw;

FLOGINIT_DEFAULT()

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

int initContext() {

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  GLfloat screenWidth = 800;
  GLfloat screenHeight = 800;
  GLFWwindow *window;
  GLFWwindow *mWindowNew;
  GLuint mCursorPositionX;
  GLuint mCursorPositionY;

  window = nullptr;
  mWindowNew = nullptr;

  mCursorPositionX = 1;
  mCursorPositionY = 1;

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  screenWidth = mode->width;
  screenHeight = mode->height;

  window = glfwCreateWindow(screenWidth, screenHeight, "Fillwave", glfwGetPrimaryMonitor(), /*NULL*/
                            NULL);

  glfwMakeContextCurrent(window);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 16);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//xxx sure ?

  if (!window) {
    FLOG_ERROR("Could not create a new rendering window.\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
}

static void BM_EngineCreationDestroy(benchmark::State &state) {
  initContext();
  char a[] = "./benchmarks";
  GLchar *const argv[] = {
      a
  };
  while (state.KeepRunning()) {
    delete (new flw::Engine(1, argv));
  }
}

// Register the function as a benchmark
BENCHMARK(BM_EngineCreationDestroy);

// Define another benchmark
static void BM_MoveableInTimeCreation(benchmark::State &state) {
  while (state.KeepRunning()) {
    flf::Moveable sut;
  }
}

// Register another function as a benchmark
BENCHMARK(BM_MoveableInTimeCreation);

BENCHMARK_MAIN()