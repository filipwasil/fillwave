/*
 * log.h
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 */

#ifndef LOG_H_
#define LOG_H_

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

/* Exceptions */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <fillwave/extras/string.h>

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

#define FERROR FBIT(0)
#define FINFO FBIT(1)
#define FDEBUG FBIT(2)
#define FFATAL FBIT(3)
#define FUSER FBIT(4)

#define FBITMAX ( FERROR | FINFO | FDEBUG | FFATAL | FUSER )

/* Define this macro in Your source file to provide access to Fillwave log macros*/

#define FLOGINIT(name, mask)\
   static const char* _tag_ = (name);     \
   static const char _mask_ = (mask);

#define FIF(mask) (::_mask_ & mask & FBITMAX | FBITMAX)

//#define PLOG(str) std::cout << str << std::endl

#ifdef __ANDROID__
   #define FLOG_FATAL(...) do { if ( FIF(FFATAL) ) (void)__android_log_print(ANDROID_LOG_FATAL, ::_tag_, __VA_ARGS__);} while(0)
   #define FLOG_INFO(...) do { if ( FIF(FINFO) ) (void)__android_log_print(ANDROID_LOG_INFO, ::_tag_, __VA_ARGS__);} while(0)
   #define FLOG_DEBUG(...) do { if ( FIF(FDEBUG) ) (void)__android_log_print(ANDROID_LOG_DEBUG, ::_tag_, __VA_ARGS__);} while(0)
   #define FLOG_USER(...) do { if ( FIF(FUSER) ) (void)__android_log_print(ANDROID_LOG_WARN, ::_tag_, __VA_ARGS__);} while(0)
   #define FLOG_ERROR(...) do { if ( FIF(FERROR) ) (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_, __VA_ARGS__);} while(0)

   #define FLOG_CHECK(...)\
      do { GLenum error = glGetError();\
         if ( error != GL_NO_ERROR) {\
            (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_, "[%s 0x%04x] ", "CORE ERROR:", error);\
            (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_, __VA_ARGS__);\
            if (error == 0x0506) { /*Framebuffer error*/ \
              GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);\
              (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_, "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            }\
        }\
      }while(0)
   #ifndef NDEBUG
   #endif

#else

   #define FLOG_ERROR(...)\
      do {                                                                      \
         if ( FIF(FERROR) ) {                                                   \
            fprintf(stdout,"%s[%s] <%s:%d> ","\e[31m","ERROR",::_tag_,__LINE__);\
            (void)fprintf(stdout,__VA_ARGS__);                                  \
            fprintf(stdout,"\e[0m\n");                                          \
         }                                                                      \
      }while(0)

   #define FLOG_CHECK(...)\
      do { GLenum error = glGetError();                                               \
         if ( error != GL_NO_ERROR) {                                                 \
            fprintf(stdout,"%s[%s 0x%04x] ","\e[35m","CORE ERROR:",error);            \
            if (error == 0x0506) { /*Framebuffer error*/                              \
               GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);              \
               fprintf(stdout,"%s[%s 0x%04x] ","\e[35m","FRAMEBUFFER_STATUS:",status);\
            }                                                                         \
            fprintf(stdout,"<%s:%d> ",::_tag_,__LINE__);                              \
            (void)fprintf(stdout,__VA_ARGS__);                                        \
            fprintf(stdout,"\e[0m\n");                                                \
            abort();                                                                  \
         }                                                                            \
      }while(0)

   #define FLOG_USER(...)\
      do {                                                                     \
         if ( FIF(FUSER) ) {                                                   \
            fprintf(stdout,"%s[%s] <%s:%d> ","\e[34m","USER",::_tag_,__LINE__);\
            (void)fprintf(stdout,__VA_ARGS__);                                 \
            fprintf(stdout,"\e[0m\n");                                         \
         }                                                                     \
      }while(0)

#ifdef NDEBUG
   #define FLOG_DEBUG(...)\
      do {                                                                      \
         if ( FIF(FDEBUG) ) {                                                   \
            fprintf(stdout,"%s[%s] <%s:%d> ","\e[33m","DEBUG",::_tag_,__LINE__);\
            (void)fprintf(stdout,__VA_ARGS__);                                  \
            fprintf(stdout,"\e[0m\n");                                          \
         }                                                                      \
      }while(0)
#else
   #define FLOG_DEBUG(...)\
      if (isFileValid()) {\
         if ( FIF(FDEBUG) ) {                                         \
            do { FILE *fp = fopen( getLogPath().c_str(), "a" );       \
               if (fp) {                                              \
                  fprintf(fp,"[%s] <%s:%d>","DEBUG",::_tag_,__LINE__);\
                  (void)fprintf(fp,__VA_ARGS__);                      \
                  fprintf(fp,"\n");                                   \
                  fclose(fp);                                         \
               }                                                      \
            }while(0);                                                \
         }                                                            \
      }
#endif
   #define FLOG_INFO(...) \
      do {                                                                    \
         if ( FIF(FINFO) ) {                                                  \
            fprintf(stdout,"%s[%s] <%s:%d> ","\e[36m","LOG",::_tag_,__LINE__);\
            (void)fprintf(stdout,__VA_ARGS__);                                \
            fprintf(stdout,"\e[0m\n");                                        \
         }                                                                    \
      }while(0)

   #define FLOG_FATAL(...) \
      do {                                                                                 \
         if ( FIF(FFATAL) ) {                                                              \
            fprintf(stdout,"%s[%s] <%s:%d> ","\e[35m","FATAL CORE ERROR",::_tag_,__LINE__);\
            (void)fprintf(stdout,__VA_ARGS__);                                             \
            fprintf(stdout,"\e[0m\n");                                                     \
            exit(1);                                                                       \
         }                                                                                 \
      }while(0)
#endif

#endif /* LOG_H_ */
