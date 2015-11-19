
#include "../../../android/inc/ContextEGL/egl_helper.h"

#include <fillwave/extras/Log.h>

FLOGINIT("EGL", FERROR | FFATAL)

namespace EGL {

/**
 * Initialize an EGL context for the current display.
 */
int Initialize(EGLNativeWindowType window, EGLContextInfo* eglInfo,
        const EGLint attribs[], const EGLint context_attrib_list[],
        EGLNativeDisplayType display) {

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;

    eglInfo->display = eglGetDisplay(display);

    eglInitialize(eglInfo->display, &eglInfo->major, &eglInfo->minor);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(eglInfo->display, attribs, &config, 1, &numConfigs);
//    if (!eglChooseConfig(eglInfo->display, attribs, &config, 1, &numConfigs)) {
//       FLOG_ERROR("Config not found ");
//       return -1;
//    }

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(eglInfo->display, config, EGL_NATIVE_VISUAL_ID, &format);

//  eglGetConfigAttrib(eglInfo->display, config, EGL_DEPTH_SIZE, &format);
//  FLOG_INFO("Config depth: %d ", format);
//  eglGetConfigAttrib(eglInfo->display, config, EGL_BUFFER_SIZE, &format);
//  FLOG_INFO("Config color component size: %d ", format);
//  eglGetConfigAttrib(eglInfo->display, config, EGL_ALPHA_SIZE, &format);
//  FLOG_INFO("Config alpha component size: %d ", format);
#ifdef __ANDROID__
    ANativeWindow_setBuffersGeometry((ANativeWindow*)window, 0, 0, format);
#endif
    eglInfo->surface = eglCreateWindowSurface(eglInfo->display, config, window,
            NULL);
    eglInfo->context = eglCreateContext(eglInfo->display, config, NULL,
            context_attrib_list);

    if (eglMakeCurrent(eglInfo->display, eglInfo->surface, eglInfo->surface,
            eglInfo->context) == EGL_FALSE) {
        FLOG_ERROR("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(eglInfo->display, eglInfo->surface, EGL_WIDTH,
            &eglInfo->width);
    eglQuerySurface(eglInfo->display, eglInfo->surface, EGL_HEIGHT,
            &eglInfo->height);

    return 0;
}
/**
 * Tear down the EGL context currently associated with the display.
 */
void Terminate(EGLContextInfo* eglInfo) {
    if (eglInfo->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(eglInfo->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                EGL_NO_CONTEXT);
        if (eglInfo->context != EGL_NO_CONTEXT) {
            eglDestroyContext(eglInfo->display, eglInfo->context);
        }
        if (eglInfo->surface != EGL_NO_SURFACE) {
            eglDestroySurface(eglInfo->display, eglInfo->surface);
        }
        eglTerminate(eglInfo->display);
    }
    eglInfo->display = EGL_NO_DISPLAY;
    eglInfo->context = EGL_NO_CONTEXT;
    eglInfo->surface = EGL_NO_SURFACE;
}

void SwapDisplay(EGLContextInfo* eglInfo) {
    if (eglGetCurrentContext() != EGL_NO_CONTEXT) {
        eglSwapBuffers(eglInfo->display, eglInfo->surface);
    } else {
        FLOG_ERROR("Surface destroyed");
    }
}

} /* EGL */
