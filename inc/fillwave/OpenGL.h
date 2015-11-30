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

#ifdef FILLWAVE_COMPILATION_GLES_2_0
#define FILLWAVE_GLES_2_0
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define glClearDepth glClearDepthf /* xxx doublecheck */
#define GL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE /* xxx doublecheck */
#define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32F /* xxx doublecheck */

#else /* FILLWAVE_COMPILATION_GLES_2_0 */
#define FILLWAVE_GLES_3_0
#define GL_GLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define glClearDepth glClearDepthf
#define GL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE
#define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32F
#endif /* FILLWAVE_COMPILATION_GLES_2_0 */

#else /* defined(__ANDROID__) || defined(FILLWAVE_COMPILATION_PC_GLES) */
#include <GL/glew.h>
#endif /* defined(__ANDROID__) || defined(FILLWAVE_COMPILATION_PC_GLES) */

#endif /* defined(__APPLE__) || defined(_WIN32) || defined(_WIN64) */

#if defined(GL_TEXTURE31)
#define MAX_TEXTURE_UNITS 32
#elif defined(GL_TEXTURE16)
#define MAX_TEXTURE_UNITS 16
#elif defined(GL_TEXTURE8)
#define MAX_TEXTURE_UNITS 8
#elif defined(GL_TEXTURE4)
#define MAX_TEXTURE_UNITS 4
#else
#define MAX_TEXTURE_UNITS 1
#endif

#define FILLWAVE_POSITION_ATTACHMENT 0
#define FILLWAVE_DIFFUSE_ATTACHMENT 1
#define FILLWAVE_NORMAL_ATTACHMENT 2
#define FILLWAVE_SPECULAR_ATTACHMENT 3
#define FILLWAVE_FINAL_ATTACHMENT 4
#define FILLWAVE_DIFFUSE_UNIT 5
#define FILLWAVE_NORMAL_UNIT 6
#define FILLWAVE_SPECULAR_UNIT 7
#define FILLWAVE_NOISE_UNIT 8
#define FILLWAVE_AO_UNIT 9
#define FILLWAVE_SHADOW_FIRST_UNIT 10

#endif /* GLCORE_H_ */
