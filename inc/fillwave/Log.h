/*
 *  Created on: Mar 28, 2014
 *      Author: filip
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

#pragma once

/* Exceptions */
#include <fillwave/Config.h>
#include <fillwave/common/Strings.h>

#include <stdarg.h>


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

#define FBIT(offset) (1 << offset)

#define FSTR_HELPER(x)  #x
#define FTO_STRING(x)   FSTR_HELPER(x)

#ifdef __ANDROID__
#include <android/log.h>
#endif

#if !defined(FILLWAVE_BUILD_RELEASE) && !defined(__ANDROID__)
#include "spdlog/spdlog.h"

namespace spd = spdlog;

static std::shared_ptr<spd::logger> logs = spd::stdout_logger_mt("LogConsole");
static char glBuffer[256];

#define fLogF(...) do { logs->critical("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogE(...) do { logs->critical("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogI(...) do { logs->info("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogU(...) do { logs->info("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogD(...) do { logs->info("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogW(...) do { logs->warn("[%s] <%s:%d> %s", FTO_STRING(type), ::_tag_.c_str(), __LINE__, __VA_ARGS__); } while(0)
#define fLogC(...) do {\
    GLenum errorCode = getGlError();\
    if (0 != errorCode) { /* GL_NO_ERROR */\
        int n = sprintf(glBuffer, "[%s 0x%04x] ", "CORE ERROR:", errorCode);\
        if (n > 0) {\
            logs->critical(glBuffer);\
        }\
        if (errorCode == 0x0506) { /* GL_INVALID_FRAMEBUFFER_OPERATION */\
            GLenum status = getFramebufferStatus();\
            n = sprintf(glBuffer, "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            if (n > 0) {\
                logs->critical(glBuffer);\
            }\
        }\
        logs->critical(__VA_ARGS__);\
        abort();\
    }\
\
} while (0)
#endif

#ifdef FILLWAVE_BUILD_RELEASE

/* No debugs for release */

#define fLogF(...) { }
#define fLogI(...) { }
#define fLogD(...) { }
#define fLogU(...) { }
#define fLogW(...) { }
#define fLogE(...) { }
#define fLogC(...) { }

#else /* FILLWAVE_BUILD_RELEASE */

#ifdef __ANDROID__
#define fLogF(...) do { if ( FIF(FFATAL) ) (void)__android_log_print(ANDROID_LOG_FATAL, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define fLogI(...) do { if ( FIF(FINFO) ) (void)__android_log_print(ANDROID_LOG_INFO, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define fLogD(...) do { if ( FIF(FDEBUG) ) (void)__android_log_print(ANDROID_LOG_DEBUG, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define fLogU(...) do { if ( FIF(FUSER) ) (void)__android_log_print(ANDROID_LOG_WARN, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define fLogW(...) do { if ( FIF(FWARNING) ) (void)__android_log_print(ANDROID_LOG_WARN, ::_tag_.c_str(), __VA_ARGS__);} while(0)
#define fLogE(...) do { if ( FIF(FERROR) ) (void)__android_log_print(ANDROID_LOG_ERROR, ::_tag_.c_str(), __VA_ARGS__);} while(0)

#define fLogC(...)\
      do { GLenum errorCode = glGetError();\
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

#endif /* FILLWAVE_BUILD_RELEASE */

#endif /* __ANDROID__ */


