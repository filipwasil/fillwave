/*
 * log.h
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
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

#ifndef LOG_H_
#define LOG_H_

/* Exceptions */
#include <fillwave/common/Strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace fillwave {

std::string getLogPath();
void setLogPath(std::string path);
bool isFileValid();
void setFileInvalid();

} /* fillwave */

#define FBIT(offset) (1 << offset)

#define FSTR_HELPER(x)	#x
#define FTO_STRING(x)	FSTR_HELPER(x)

/*
__linux__       Defined on Linux
__sun           Defined on Solaris
__FreeBSD__     Defined on FreeBSD
__NetBSD__      Defined on NetBSD
__OpenBSD__     Defined on OpenBSD
__APPLE__       Defined on Mac OS X
__hpux          Defined on HP-UX
__osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
__sgi           Defined on Irix
_AIX            Defined on AIX
*/

#if defined (__linux__) || defined(__APPLE__)
#define FCOLOR_GREEN "32m"
#define FCOLOR_BLUE "34m"
#define FCOLOR_YELLOW "33m"
#define FCOLOR_RED "31m"
#define FCOLOR_GREY "35m"
#define FOPENCOLOROUTPUT "\033["
#define FCLOSECOLOROUTPUT "\033[0m"
#elif defined(_WIN32)
#define FCOLOR_GREEN ""
#define FCOLOR_BLUE ""
#define FCOLOR_YELLOW ""
#define FCOLOR_RED ""
#define FCOLOR_GREY ""
#define FOPENCOLOROUTPUT ""
#define FCLOSECOLOROUTPUT ""
#else

#endif


#define FERROR FBIT(0)
#define FINFO FBIT(1)
#define FDEBUG FBIT(2)
#define FFATAL FBIT(3)
#define FUSER FBIT(4)
#define FWARNING FBIT(5)

#define FBIT_MAX (FERROR | FINFO | FDEBUG | FFATAL | FUSER | FWARNING)

/* Define this macro in your source file to provide access to Crater log macros */

#define FLOGINIT_DEFAULT()                                              \
   static const std::string _tag_ = fillwave::getFileNameOnly(__FILE__);\
   static const char _mask_ = FBIT_MAX;

#define FLOGINIT_MASK(mask)                                             \
   static const std::string _tag_ = (__FILE__);                         \
   static const char _mask_ = (mask);

#define FLOGINIT(tag, mask)                                             \
   static const std::string _tag_ = (tag);                              \
   static const char _mask_ = (mask);

#define FLOGINIT_NONE()                                                 \
   static const std::string _tag_ = "";                                 \
   static const char _mask_ = 0;

#define FIF(mask) (::_mask_ & mask)

#ifdef __ANDROID__
#define FLOG_FATAL(...) do { if ( FIF(FFATAL) ) (void)__android_log_print(ANDROID_LOG_FATAL, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define FLOG_INFO(...) do { if ( FIF(FINFO) ) (void)__android_log_print(ANDROID_LOG_INFO, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define FLOG_DEBUG(...) do { if ( FIF(FDEBUG) ) (void)__android_log_print(ANDROID_LOG_DEBUG, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define FLOG_USER(...) do { if ( FIF(FUSER) ) (void)__android_log_print(ANDROID_LOG_WARN, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define FLOG_WARNING(...) do { if ( FIF(FWARNING) ) (void)__android_log_print(ANDROID_LOG_WARN, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define FLOG_ERROR(...) do { if ( FIF(FERROR) ) (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), __VA_ARGS__);} while(0)

#define FLOG_CHECK(...)\
      do { GLenum error_unique_niosfoinfsd = glGetError();\
         if ( error_unique_niosfoinfsd != GL_NO_ERROR) {\
            (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), "[%s 0x%04x] ", "CORE ERROR:", error_unique_niosfoinfsd);\
            (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), __VA_ARGS__);\
            if (error_unique_niosfoinfsd == 0x0506) { /*Framebuffer error*/ \
              GLenum status = getFramebufferStatus();\
              (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            }\
        }\
      }while(0)

#else /* __ANDROID__ */

#define FLOG_BASE(color, type, flag, ...)                                          \
	do {                                                                            \
	   if ( FIF(flag) ) {                                                           \
	      FILE *unique_niosfoinfsd;                                                 \
	      if (fillwave::isFileValid()) {                                            \
	         unique_niosfoinfsd = fopen( fillwave::getLogPath().c_str(), "a" );     \
	         if (!unique_niosfoinfsd) {                                             \
	            break;                                                              \
	         }                                                                      \
	      } else {                                                                  \
	         unique_niosfoinfsd = stdout;                                           \
	      }                                                                         \
	      fprintf(unique_niosfoinfsd,"%s%s[%s] <%s:%d> %s", FOPENCOLOROUTPUT, color,\
	            FTO_STRING(type),::_tag_.c_str(),__LINE__,FCLOSECOLOROUTPUT);       \
	      (void)fprintf(unique_niosfoinfsd,__VA_ARGS__);                            \
	      fprintf(unique_niosfoinfsd,"\n");                                         \
	      if (fillwave::isFileValid()) {                                            \
	         fclose(unique_niosfoinfsd);                                            \
	      }                                                                         \
	   }                                                                            \
	} while(0)

#define FLOG_CHECK(...)\
      do { GLenum error_unique_niosfoinfsd = glGetError();                         \
         if ( error_unique_niosfoinfsd != GL_NO_ERROR) {                           \
            fprintf(stdout,"[%s 0x%04x] ","CORE ERROR:",error_unique_niosfoinfsd); \
            if (error_unique_niosfoinfsd == 0x0506) { /*Framebuffer error*/        \
               GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);           \
               fprintf(stdout,"[%s 0x%04x] ","FRAMEBUFFER_STATUS:",status);        \
            }                                                                      \
            fprintf(stdout,"<%s:%d> ",::_tag_.c_str(),__LINE__);                   \
            (void)fprintf(stdout,__VA_ARGS__);                                     \
            fprintf(stdout,"\n");                                                  \
            abort();                                                               \
         }                                                                         \
      }while(0)

#define FLOG_FATAL(...) FLOG_BASE(FCOLOR_GREY, GPU_FATAL,  FFATAL, __VA_ARGS__)
#define FLOG_INFO(...) FLOG_BASE(FCOLOR_YELLOW, GPU_INFO,  FINFO, __VA_ARGS__)
#define FLOG_DEBUG(...) FLOG_BASE(FCOLOR_GREEN, GPU_DEBUG,  FDEBUG, __VA_ARGS__)
#define FLOG_USER(...) FLOG_BASE(FCOLOR_BLUE, GPU_USER,  FUSER, __VA_ARGS__)
#define FLOG_ERROR(...) FLOG_BASE(FCOLOR_RED, GPU_ERROR,  FERROR, __VA_ARGS__)
#define FLOG_WARNING(...) FLOG_BASE(FCOLOR_YELLOW, GPU_WARNING,  FWARNING, __VA_ARGS__)

#ifndef NDEBUG
#endif /* NDEBUG */

#endif /* __ANDROID__ */

#endif /* LOG_H_ */
