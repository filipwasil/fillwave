# - Try to find FreeGLUT
# Once done this will define
#  FREEGLUT_FOUND - System has LibXml2
#  FREEGLUT_INCLUDE_DIRS - The LibXml2 include directories
#  FREEGLUT_LIBRARIES - The libraries needed to use LibXml2
#  FREEGLUT_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(FREEGLUT_PKGCONF REQUIRED freeglut>=2.6.0)
set(FREEGLUT_DEFINITIONS ${FREEGLUT_PKGCONF_CFLAGS_OTHER})

find_path(FREEGLUT_INCLUDE_DIR GL/freeglut.h
          HINTS ${FREEGLUT_PKGCONF_INCLUDEDIR} ${FREEGLUT_PKGCONF_INCLUDE_DIRS}
          )

find_library(FREEGLUT_LIBRARY NAMES freeglut
             HINTS ${FREEGLUT_PKGCONF_LIBDIR} ${FREEGLUT_PKGCONF_LIBRARY_DIRS} )

set(FREEGLUT_LIBRARIES ${FREEGLUT_LIBRARY} )
set(FREEGLUT_INCLUDE_DIRS ${FREEGLUT_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FREEGLUT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FREEGLUT DEFAULT_MSG
                                  FREEGLUT_LIBRARY FREEGLUT_INCLUDE_DIR)

mark_as_advanced(FREEGLUT_INCLUDE_DIR FREEGLUT_LIBRARY )
