/*
 * OpenGL.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Filip Wasil
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

#endif /* GLCORE_H_ */
