/*
 * log.h
 *
 *  Created on: Mar 28, 2014
 *      Author: filip
 */

#ifndef LOG_H_
#define LOG_H_

/* Exceptions */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <fillwave/common/string.h>

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

#define FERROR FBIT(0)
#define FINFO FBIT(1)
#define FDEBUG FBIT(2)
#define FFATAL FBIT(3)
#define FUSER FBIT(4)
#define FWARNING FBIT(5)

#define FBIT_MAX (FERROR | FINFO | FDEBUG | FFATAL | FUSER | FWARNING)

/* Define this macro in your source file to provide access to Crater log macros */

#define FLOGINIT_DEFAULT()\
   static const std::string _tag_ = fillwave::getFileNameOnly(__FILE__);     \
   static const char _mask_ = FBIT_MAX;

#define FLOGINIT_MASK(mask)\
   static const std::string _tag_ = (__FILE__);     \
   static const char _mask_ = (mask);

#define FLOGINIT(tag, mask)\
   static const std::string _tag_ = (tag);     \
   static const char _mask_ = (mask);

#define FLOGINIT_NONE()\
   static const std::string _tag_ = "";     \
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
              GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);\
              (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            }\
        }\
      }while(0)

#else /* __ANDROID__ */

#define FLOG_BASE(type, flag, ...)																		   \
	do{																												\
      if ( FIF(flag) ) {																						\
			FILE *unique_niosfoinfsd;																			\
			if (fillwave::isFileValid()) {																   \
				unique_niosfoinfsd = fopen( fillwave::getLogPath().c_str(), "a" );			   \
				if (!unique_niosfoinfsd) {                                   						\
					break;																							\
				}																										\
			} else {																									\
				unique_niosfoinfsd = stdout;																	\
			}																											\
			fprintf(unique_niosfoinfsd,"[%s] <%s:%d>",FTO_STRING(type),::_tag_.c_str(),__LINE__); 	\
			(void)fprintf(unique_niosfoinfsd,__VA_ARGS__);												\
			fprintf(unique_niosfoinfsd,"\n");																\
			if (fillwave::isFileValid()) {																   \
				fclose(unique_niosfoinfsd);																	\
			}																											\
      }																												\
	} while(0)

#define FLOG_CHECK(...)\
      do { GLenum error_unique_niosfoinfsd = glGetError();                                               \
         if ( error_unique_niosfoinfsd != GL_NO_ERROR) {                                                 \
            fprintf(stdout,"[%s 0x%04x] ","CORE ERROR:",error_unique_niosfoinfsd);                       \
            if (error_unique_niosfoinfsd == 0x0506) { /*Framebuffer error*/                              \
               GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);              \
               fprintf(stdout,"[%s 0x%04x] ","FRAMEBUFFER_STATUS:",status);           \
            }                                                                         \
            fprintf(stdout,"<%s:%d> ",::_tag_.c_str(),__LINE__);                      \
            (void)fprintf(stdout,__VA_ARGS__);                                        \
            fprintf(stdout,"\n");                                                     \
            abort();                                                                  \
         }                                                                            \
      }while(0)

#define FLOG_FATAL(...) FLOG_BASE(FILLWAVE_FATAL,  FFATAL, __VA_ARGS__)
#define FLOG_INFO(...) FLOG_BASE(FILLWAVE_INFO,  FINFO, __VA_ARGS__)
#define FLOG_DEBUG(...) FLOG_BASE(FILLWAVE_DEBUG,  FDEBUG, __VA_ARGS__)
#define FLOG_USER(...) FLOG_BASE(FILLWAVE_USER,  FUSER, __VA_ARGS__)
#define FLOG_ERROR(...) FLOG_BASE(FILLWAVE_ERROR,  FERROR, __VA_ARGS__)
#define FLOG_WARNING(...) FLOG_BASE(FILLWAVE_WARNING,  FWARNING, __VA_ARGS__)

#ifndef NDEBUG
#endif /* NDEBUG */

#endif /* __ANDROID__ */

#endif /* LOG_H_ */
