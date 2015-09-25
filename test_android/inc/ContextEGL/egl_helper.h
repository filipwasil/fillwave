/*
 * egl_utils.h
 *
 *  Created on: 18 mar 2014
 *      Author: sabus
 */

#ifndef EGL_UTILS_H_
#define EGL_UTILS_H_

#include <EGL/egl.h>

namespace EGL {

    struct EGLContextInfo {
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        int width,height;
        EGLint major,minor;
    };
    int Initialize(EGLNativeWindowType window,
                   EGLContextInfo* eglInfo,
                   const EGLint attribs[],
                   const EGLint context_attrib_list[],
                   EGLNativeDisplayType display = EGL_DEFAULT_DISPLAY);
    void Terminate(EGLContextInfo* eglInfo);
    void SwapDisplay(EGLContextInfo* eglInfo);
} /* EGL */

#endif /* EGL_UTILS_H_ */
