/*
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Crater C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are not permitted.
 */

#include <googlebenchmark/include/benchmark/benchmark.h>

#include <fillwave/Framework.h>
#include <fillwave/Fillwave.h>
#include <GLFW/glfw3.h>
#include <fillwave/Profiler.h>
#include <fillwave/Log.h>

using namespace fillwave;

FLOGINIT_DEFAULT()

typedef std::pair<std::string, float> result;
std::vector<result> mResults;

int initContext() {

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    GLfloat screenWidth = 800;
    GLfloat screenHeight = 800;
    GLFWwindow* window;
    GLFWwindow* mWindowNew;
    GLuint mCursorPositionX;
    GLuint mCursorPositionY;

    window = nullptr;
    mWindowNew = nullptr;

    mCursorPositionX = 1;
    mCursorPositionY = 1;

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    screenWidth = mode->width;
    screenHeight = mode->height;

    window = glfwCreateWindow(screenWidth,
                              screenHeight,
                              "Fillwave",
                              glfwGetPrimaryMonitor(), /*NULL*/
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

    if(!window) {
        FLOG_ERROR("Could not create a new rendering window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

static void BM_EngineCreationDestroy(benchmark::State& state) {
    initContext();
    char a [] = "./benchmarks";
    GLchar* const argv[] = {
        a
    };
    while (state.KeepRunning()) {
        delete (new fillwave::Engine(1, argv));
    }
}
// Register the function as a benchmark
BENCHMARK(BM_EngineCreationDestroy);

// Define another benchmark
static void BM_MoveableInTimeCreation(benchmark::State& state) {
    while (state.KeepRunning()) {
        framework::Moveable sut;
    }
}
// Register another function as a benchmark
BENCHMARK(BM_MoveableInTimeCreation);

BENCHMARK_MAIN()