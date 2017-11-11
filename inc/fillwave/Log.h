#pragma once

/*
* Copyright (c) 2017, Fillwave developers
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

#include <fillwave/Config.h>
#include <fillwave/PlatformSW.h>
#include <string>

#ifdef FILLWAVE_COMPILATION_RELEASE

#define FLOGINIT_DEFAULT()
#define FLOGINIT_MASK(mask)
#define FLOGINIT(tag, mask)
#define FLOGINIT_NONE()

#define fLog()
#define fLogF(...) { }
#define fLogI(...) { }
#define fLogD(...) { }
#define fLogU(...) { }
#define fLogW(...) { }
#define fLogE(...) { }
#define fLogC(...) { }

#else /* FILLWAVE_COMPILATION_RELEASE */

//#include <fillwave/common/Strings.h>

#define FERROR FBIT(0)
#define FINFO FBIT(1)
#define FDEBUG FBIT(2)
#define FFATAL FBIT(3)
#define FUSER FBIT(4)
#define FWARNING FBIT(5)
#define FBIT_MAX (FERROR | FINFO | FDEBUG | FFATAL | FUSER | FWARNING)
#define FIF(mask) (::_mask_ & mask)
#define FBIT(offset) (1 << offset)
#define FSTR_HELPER(x) #x
#define FTO_STRING(x) FSTR_HELPER(x)

#ifdef __ANDROID__
#include <android/log.h>
#else /* __ANDROID__ */

#include "spdlog/spdlog.h"

#ifdef _WIN32
#define FILLWAVE_SPRINTF sprintf_s
#else
#define FILLWAVE_SPRINTF sprintf
#endif /* _WIN32 */

#endif /* __ANDROID__ */

#ifdef __ANDROID__

#define FLOG_CREATE_STATIC_LOGGER()

#else /* __ANDROID__ */

#define FLOG_CREATE_STATIC_LOGGER()\
    constexpr unsigned int FILLWAVE_LOG_BUFFER_SIZE = 1000;\
    static const auto logs = spdlog::stdout_logger_mt(_tag_);\
    static char buffer[FILLWAVE_LOG_BUFFER_SIZE] { 0 };

#endif /* __ANDROID__ */

#define FLOGINIT_DEFAULT()                                                                            \
   static const char* _tag_ =  (                                                                \
      std::string(__FILE__).find(FILLWAVE_OS_SEPRATOR) == std::string::npos ? std::string(__FILE__) : \
      std::string(__FILE__).substr(std::string(__FILE__).find_last_of(                                \
          FILLWAVE_OS_SEPRATOR) + 1, std::string(__FILE__).size())).c_str();                                  \
   static const char _mask_ = FBIT_MAX;                                                               \
   FLOG_CREATE_STATIC_LOGGER()

#define FLOGINIT_MASK(mask)                                             \
   static const char* _tag_ = (__FILE__);                         \
   static const char _mask_ = (mask);                                   \
   FLOG_CREATE_STATIC_LOGGER()

#define FLOGINIT(tag, mask)                                             \
   static const char* _tag_ = (tag);                              \
   static const char _mask_ = (mask);                                   \
   FLOG_CREATE_STATIC_LOGGER()

#define FLOGINIT_NONE()                                                 \
   static const char* _tag_ = "";                                 \
   static const char _mask_ = 0;                                        \
   FLOG_CREATE_STATIC_LOGGER()

/* Log */
#ifdef __ANDROID__

#define GPU_FATAL ANDROID_LOG_FATAL
#define GPU_ERROR ANDROID_LOG_ERROR
#define GPU_INFO ANDROID_LOG_INFO
#define GPU_DEBUG ANDROID_LOG_DEBUG
#define GPU_WARN ANDROID_LOG_WARN
#define GPU_USER ANDROID_LOG_WARN
#define fLog() __android_log_print(LOG_FLAG, ::_tag_.c_str(), "")
#define fLogBase(LOG_CONDITION, LOG_FLAG, ...)\
   do { if ( FIF(LOG_CONDITION) ) (void)__android_log_print(LOG_FLAG, ::_tag_.c_str(), __VA_ARGS__); } while(0)

#else /* __ANDROID__ */

#define fLog() FILLWAVE_SPRINTF(buffer, "%s:%d", ::_tag_, __LINE__)
#define fLogBase(LOG_CONDITION, LOG_FLAG, ...) LOG_FLAG ## _FN(LOG_CONDITION, __VA_ARGS__)
#define GPU_FATAL_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->critical(buffer); } } while(0)
#define GPU_ERROR_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->critical(buffer); } } while(0)
#define GPU_WARNING_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->warn(buffer); } } while(0)
#define GPU_DEBUG_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->info(buffer); } } while(0)
#define GPU_INFO_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->info(buffer); } } while(0)
#define GPU_USER_FN(COND, ...) do { if ( FIF(COND) ) { fLog(); FILLWAVE_SPRINTF(buffer, __VA_ARGS__); logs->info(buffer); } } while(0)

#endif /* __ANDROID__ */

/* Check */
#ifdef __ANDROID__

#define fLogC(...)\
    do {\
      (void)_mask_;\
      GLenum errorCode = glGetError();\
      if ( errorCode != GL_NO_ERROR) {\
        (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), "[%s 0x%04x] ", "CORE ERROR:", errorCode);\
        (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), __VA_ARGS__);\
        if (errorCode == 0x0506) { /*Framebuffer error*/ \
          GLenum status = getFramebufferStatus();\
          (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
        }\
      }\
    }while(0)
#else /* __ANDROID__ */

#define fLogC(...) do {\
    (void)buffer;\
    (void)_mask_;\
    GLenum errorCode = getGlError();\
    if (0 != errorCode) { /* GL_NO_ERROR */\
        char glBuffer[256];\
        int n = FILLWAVE_SPRINTF(glBuffer, "[%s 0x%04x] ", "CORE ERROR:", errorCode);\
        if (n > 0) {\
            logs->critical(glBuffer);\
        }\
        if (errorCode == 0x0506) { /* GL_INVALID_FRAMEBUFFER_OPERATION */\
            GLenum status = getFramebufferStatus();\
            n = FILLWAVE_SPRINTF(glBuffer, "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            if (n > 0) {\
                logs->critical(glBuffer);\
            }\
        }\
        logs->critical(__VA_ARGS__);\
        abort();\
    }\
\
} while (0)

#endif /* __ANDROID__ */

#define fLogF(...) fLogBase(FFATAL, GPU_FATAL, __VA_ARGS__)
#define fLogE(...) fLogBase(FERROR, GPU_ERROR, __VA_ARGS__)
#define fLogI(...) fLogBase(FINFO, GPU_INFO, __VA_ARGS__)
#define fLogU(...) fLogBase(FUSER, GPU_USER, __VA_ARGS__)
#define fLogD(...) fLogBase(FDEBUG, GPU_DEBUG, __VA_ARGS__)
#define fLogW(...) fLogBase(FWARNING, GPU_WARN, __VA_ARGS__)

#endif /* FILLWAVE_COMPILATION_RELEASE */
