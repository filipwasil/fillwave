#include <flw/OpenGL.h>

PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = [](GLuint program, GLenum pname, GLint *params){};
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = [](GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name){};
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = [](GLuint program, const GLchar *name){ return 0; };
PFNGLENABLEPROC glad_glEnable = [](GLenum target) {};
PFNGLBLENDFUNCPROC glad_glBlendFunc = [] (GLenum sfactor, GLenum dfactor) {};
PFNGLDRAWARRAYSPROC glad_glDrawArrays = [] (GLenum mode, GLint first, GLsizei count) {};
PFNGLDISABLEPROC glad_glDisable = [] (GLenum cap) {};
PFNGLDRAWELEMENTSPROC glad_glDrawElements = [] (GLenum mode, GLsizei count, GLenum type, const void *indices) {};
PFNGLGETINTEGERVPROC glad_glGetIntegerv = [] (GLenum pname, GLint *data) {};
const GLubyte *b = nullptr;
PFNGLGETSTRINGIPROC glad_glGetStringi = [] (GLenum name, GLuint index) { return b; };
PFNGLFRONTFACEPROC glad_glFrontFace = [] (GLenum mode) { };
PFNGLGETERRORPROC glad_glGetError = [] () { return GLenum(GL_NO_ERROR); };
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = [] (GLuint program, const GLchar *name) { return -1; };
PFNGLCOMPRESSEDTEXIMAGE1DPROC glad_glCompressedTexImage1D = [](GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data){};
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = [](GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels){};
PFNGLPIXELSTOREIPROC glad_glPixelStorei = [](GLenum pname, GLint param){};
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D = [](GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data){};
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = [](GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data){};
PFNGLTEXIMAGE1DPROC glad_glTexImage1D = [](GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels){};
PFNGLCOLORMASKPROC glad_glColorMask = [](GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){};
PFNGLDEPTHMASKPROC glad_glDepthMask = [](GLboolean flag){};