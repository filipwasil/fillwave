# - Try to find OpenGL 3.3
# Once done, this will define
#
# GL_FOUND - system has GL
# GL_INCLUDE_DIRS - the GL include directories
# GL_LIBRARIES - link these to use GL
 
include(LibFindMacros)
 
# Use pkg-config to get hints about paths
libfind_pkg_check_modules(GL_PKGCONF gl)

# Include dir
find_path(GLES20_INCLUDE_DIR
NAMES GL/gl.h
PATHS ${GLES20_PKGCONF_INCLUDE_DIRS}
)
 
# Finally the library itself
find_library(GLES_LIBRARY
NAMES GLESv2
PATHS ${GLES20_PKGCONF_LIBRARY_DIRS}
)
 
find_library(EGL_LIBRARY
NAMES EGL
PATHS ${GLES20_PKGCONF_LIBRARY_DIRS}
)
 
# Include dir
find_path(EGL_INCLUDE_DIR
NAMES EGL/eglext.h
PATHS ${GLES20_PKGCONF_INCLUDE_DIRS}
)
 
SET(GLES20_LIBRARY
${GLES_LIBRARY}
${EGL_LIBRARY}
)
 
# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(GLES20_PROCESS_INCLUDES GLES20_INCLUDE_DIR GLES20_INCLUDE_DIRS)
set(GLES20_PROCESS_LIBS GLES20_LIBRARY GLES20_LIBRARIES)
libfind_process(GLES20)