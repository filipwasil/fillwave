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

#define FBIT(offset) (1 << offset)
#define FERROR FBIT(0)
#define FINFO FBIT(1)
#define FDEBUG FBIT(2)
#define FFATAL FBIT(3)
#define FUSER FBIT(4)
#define FWARNING FBIT(5)
#define FBIT_MAX (FERROR | FINFO | FDEBUG | FFATAL | FUSER | FWARNING)
#define FIF(mask) (::_mask_ & mask)
#define FSTR_HELPER(x) #x
#define FTO_STRING(x) FSTR_HELPER(x)

#ifdef __ANDROID__
#include <android/log.h>
#else /* __ANDROID__ */

#include <sstream>
#include <iostream>

#ifdef _WIN32
constexpr auto FLOG_BLACK = "";
constexpr auto FLOG_RED = "";
constexpr auto FLOG_GREEN = "";
constexpr auto FLOG_YELLOW = "";
constexpr auto FLOG_BLUE = "";
constexpr auto FLOG_MAGENTA = "";
constexpr auto FLOG_CYAN = "";
constexpr auto FLOG_WHITE = "";
constexpr auto FLOG_END = "";
#else
constexpr auto FLOG_BLACK = "\033[0;30m";
constexpr auto FLOG_RED = "\033[0;31m";
constexpr auto FLOG_GREEN = "\033[0;32m";
constexpr auto FLOG_YELLOW = "\033[0;33m";
constexpr auto FLOG_BLUE = "\033[0;34m";
constexpr auto FLOG_MAGENTA = "\033[0;35m";
constexpr auto FLOG_CYAN = "\033[0;36m";
constexpr auto FLOG_WHITE = "\033[0;37m";
constexpr auto FLOG_END = "\033[0m";
#endif /* _WIN32 */

#endif /* __ANDROID__ */

#define FLOGINIT_DEFAULT()                                                                            \
   static const std::string _tag_ =  (                                                                \
      std::string(__FILE__).find(FILLWAVE_OS_SEPRATOR) == std::string::npos ? std::string(__FILE__) : \
      std::string(__FILE__).substr(std::string(__FILE__).find_last_of(                                \
          FILLWAVE_OS_SEPRATOR) + 1, std::string(__FILE__).size()));                                  \
   static const char _mask_ = FBIT_MAX;

#define FLOGINIT_MASK(mask)                                             \
   static const std::string _tag_ =  (                                                                \
      std::string(__FILE__).find(FILLWAVE_OS_SEPRATOR) == std::string::npos ? std::string(__FILE__) : \
      std::string(__FILE__).substr(std::string(__FILE__).find_last_of(                                \
          FILLWAVE_OS_SEPRATOR) + 1, std::string(__FILE__).size()));                                  \
   static const char _mask_ = (mask);

#define FLOGINIT(tag, mask)                                             \
   static const std::string _tag_ = (tag);                              \
   static const char _mask_ = (mask);

#define FLOGINIT_NONE()                                                 \
   static const std::string _tag_ = "";                                 \
   static const char _mask_ = 0;

#ifdef __ANDROID__

#define GPU_FATAL ANDROID_LOG_FATAL
#define GPU_ERROR ANDROID_LOG_ERROR
#define GPU_INFO ANDROID_LOG_INFO
#define GPU_DEBUG ANDROID_LOG_DEBUG
#define GPU_WARN ANDROID_LOG_WARN
#define GPU_USER ANDROID_LOG_WARN

#else /* __ANDROID__ */

#define GPU_FATAL FLOG_MAGENTA
#define GPU_ERROR FLOG_RED
#define GPU_INFO FLOG_WHITE
#define GPU_DEBUG FLOG_GREEN
#define GPU_WARN FLOG_YELLOW
#define GPU_USER FLOG_BLUE

#endif /* __ANDROID__ */

/* Log */
#ifdef __ANDROID__

#define fLog() __android_log_print(LOG_FLAG, ::_tag_.c_str(), "")
#define fLogBase(LOG_CONDITION, LOG_FLAG, ...)\
   do { if ( FIF(LOG_CONDITION) ) (void)__android_log_print(LOG_FLAG, ::_tag_.c_str(), __VA_ARGS__); } while(0)

#else /* __ANDROID__ */

template<typename T>
static void fLogWithStream(std::stringstream& s, const T& t) {
  std::cout << s.str() << t << FLOG_END << std::endl;
}
template<typename T, typename... Args>
static void fLogWithStream(std::stringstream& s, const T& t, Args... args) {
  s << t;
  fLogWithStream(s, args...);
}

#define fLogBase(COLOR, COND, ...)\
do {\
  if ( FIF(COND) ) {\
    std::stringstream s;\
    s << COLOR;\
    fLogWithStream(s, ::_tag_,":", __LINE__, " ", __VA_ARGS__);\
  }\
} while(0)

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

#ifdef _WIN32
#define FILLWAVE_SPRINTF sprintf_s
#else
#define FILLWAVE_SPRINTF sprintf
#endif /* _WIN32 */

#define fLogC(...) do {\
    (void)_mask_;\
    GLenum errorCode = getGlError();\
    if (0 != errorCode) { /* GL_NO_ERROR */\
        char glBuffer[256];\
        int n = FILLWAVE_SPRINTF(glBuffer, "[%s 0x%04x] ", "CORE ERROR:", errorCode);\
        if (n > 0) {\
            fLogF(glBuffer);\
        }\
        if (errorCode == 0x0506) { /* GL_INVALID_FRAMEBUFFER_OPERATION */\
            GLenum status = getFramebufferStatus();\
            n = FILLWAVE_SPRINTF(glBuffer, "[%s 0x%04x] ", "FRAMEBUFFER_STATUS:", status);\
            if (n > 0) {\
                fLogF(glBuffer);\
            }\
        }\
        fLogF(__VA_ARGS__);\
        abort();\
    }\
\
} while (0)

#endif /* __ANDROID__ */

#define fLogF(...) fLogBase(FLOG_MAGENTA, FFATAL, __VA_ARGS__)
#define fLogE(...) fLogBase(FLOG_RED, FERROR, __VA_ARGS__)
#define fLogI(...) fLogBase(FLOG_WHITE, FINFO, __VA_ARGS__)
#define fLogU(...) fLogBase(FLOG_BLUE, FUSER, __VA_ARGS__)
#define fLogD(...) fLogBase(FLOG_GREEN, FDEBUG, __VA_ARGS__)
#define fLogW(...) fLogBase(FLOG_YELLOW, FWARNING, __VA_ARGS__)

#endif /* FILLWAVE_COMPILATION_RELEASE */
