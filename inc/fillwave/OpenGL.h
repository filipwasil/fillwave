/*
 * OpenGL.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Filip Wasil
 */

#ifndef GLCORE_H_
#define GLCORE_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/Config.h>

#if defined(__APPLE__)
   #include <GL/glew.h>
#elif defined(_WIN32) || defined(_WIN64)
    //#define GLEW_STATIC
    //#define GLEW_BUILD
    #include <GL/glew.h>
    //#include <GL/Regal.h>
#else
   #if (__ANDROID__)
      #define GL_GLEXT_PROTOTYPES
      #include <GLES3/gl3.h>
      #include <GLES3/gl3ext.h>

      #define glClearDepth glClearDepthf
      #define GL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE
      #define GL_DEPTH_COMPONENT32 GL_DEPTH_COMPONENT32F

      void glesInitExtensions();
   #else
      #ifdef FILLWAVE_COMPILATION_PC_GLES
         #include <GLES3/gl3.h>
         #include <GLES3/gl3ext.h>
      #else
         #include <GL/glew.h>
      #endif
   #endif
#endif

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

//#define FILLWAVE_DIFFUSE_UNIT MAX_TEXTURE_UNITS - 1
//#define FILLWAVE_NORMAL_UNIT MAX_TEXTURE_UNITS - 2
//#define FILLWAVE_SPECULAR_UNIT MAX_TEXTURE_UNITS - 3

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
