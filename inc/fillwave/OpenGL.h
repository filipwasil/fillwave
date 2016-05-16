/*
 * OpenGL.h
 *
 *  Created on: Sep 28, 2014
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

#ifndef GLCORE_H_
#define GLCORE_H_

#include <fillwave/Config.h>

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#else /* defined(__APPLE__) || defined(_WIN32) || defined(_WIN64) */

void glesInitExtensions();

#if defined(__ANDROID__) || defined(FILLWAVE_COMPILATION_PC_GLES)

#define FILLWAVE_GLES_3_0
#define GL_GLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define glClearDepth glClearDepthf
#define GL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE
#define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32F
#define GLulong GLuint

#else /* defined(__ANDROID__) || defined(FILLWAVE_COMPILATION_PC_GLES) */
#include <GL/glew.h>
#endif /* defined(__ANDROID__) || defined(FILLWAVE_COMPILATION_PC_GLES) */

#endif /* defined(__APPLE__) || defined(_WIN32) || defined(_WIN64) */

#if defined(GL_TEXTURE31)
constexpr GLint MAX_TEXTURE_UNITS = 32;
#elif defined(GL_TEXTURE16)
constexpr GLint MAX_TEXTURE_UNITS = 16;
#elif defined(GL_TEXTURE8)
constexpr GLint MAX_TEXTURE_UNITS = 8;
#elif defined(GL_TEXTURE4)
constexpr GLint MAX_TEXTURE_UNITS = 4;
#else
constexpr GLint MAX_TEXTURE_UNITS = 1;
#endif

/* Textures */
constexpr GLint FILLWAVE_POSITION_ATTACHMENT = 0;
constexpr GLint FILLWAVE_DIFFUSE_ATTACHMENT = 1;
constexpr GLint FILLWAVE_NORMAL_ATTACHMENT = 2;
constexpr GLint FILLWAVE_SPECULAR_ATTACHMENT = 3;
constexpr GLint FILLWAVE_FINAL_ATTACHMENT = 4;
constexpr GLint FILLWAVE_DIFFUSE_UNIT = 5;
constexpr GLint FILLWAVE_NORMAL_UNIT = 6;
constexpr GLint FILLWAVE_SPECULAR_UNIT = 7;
constexpr GLint FILLWAVE_NOISE_UNIT = 8;
constexpr GLint FILLWAVE_AO_UNIT = 9;
constexpr GLint FILLWAVE_SHADOW_FIRST_UNIT = 10;

/* Uniforms */
constexpr unsigned int FILLWAVE_LIGHTS_BINDING_POINT = 0;
constexpr int FILLWAVE_UNIFORM_NOT_FOUND = -1;

constexpr unsigned int FILLWAVE_AO_SAMPLE_RADIUS = 1.6f;
constexpr unsigned int FILLWAVE_OQ_VERTICES = 36;

#endif /* GLCORE_H_ */
