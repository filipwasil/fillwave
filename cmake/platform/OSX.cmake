# -----------------------------------------------
# Workarounds
# -----------------------------------------------

if (NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

ADD_DEFINITIONS("-fopenmp")
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF(OPENMP_FOUND)

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

set(FILLWAVE_PATH_EXT_INCLUDE "inc")
set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_EXT_GLM_INCLUDES ext/glm)
set(FILLWAVE_EXT_INCLUDES ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES "ext/fontgenerator")
set(FILLWAVE_EXT_STB_INCLUDES "${CMAKE_SOURCE_DIR}/ext/stb")
set(FILLWAVE_EXT_ASSIMP_INCLUDES ext/assimp/include)
#set(FILLWAVE_EXT_FREETYPE2_INCLUDES "ext/freetype2/include" )
set(FILLWAVE_EXT_GLEW_INCLUDES "ext/glew/include" )

add_subdirectory(ext/assimp)
add_subdirectory(ext/freetype2)
add_subdirectory(ext/glfw)
add_subdirectory(ext)
if (BUILD_DEV)
add_subdirectory(test)
endif(BUILD_DEV)

if(BUILD_DEV)
   message("Building development package")
   PROJECT(libfillwave-dev C CXX)
endif(BUILD_DEV)

if(BUILD_LIB)
   message("Building binary package")
   PROJECT(libfillwave C CXX)
endif(BUILD_LIB)

set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(FILLWAVE_EXT_INCLUDES ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ext/fontgenerator)
set(FILLWAVE_EXT_STB_INCLUDES ext/stb)

set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_PATH_SOURCE "src")

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_ASSIMP_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# shared library to build
# -----------------------------------------------
IF(BUILD_LIB)
ADD_LIBRARY(fillwave SHARED ${FILLWAVE_SOURCES})
ENDIF(BUILD_LIB)

# -----------------------------------------------
# installation info
# -----------------------------------------------

IF (BUILD_DEV)
   INSTALL(DIRECTORY inc/fillwave DESTINATION /usr/include COMPONENT fillwave-dev)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image_write.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h DESTINATION /usr/include)
ENDIF(BUILD_DEV)

if (BUILD_LIB)
   if(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib64 COMPONENT fillwave)
   else(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib COMPONENT fillwave)
   endif(BUILD_RPM)
endif (BUILD_LIB)

set(CMAKE_PREFIX_PATH "/usr/local")
set(CMAKE_LIBRARY_PATH "/usr/local/lib/")

# -----------------------------------------------
# Link libraries
# -----------------------------------------------
find_package(GLEW REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${GLEW_INCLUDE_DIRS}")
link_libraries(${GLEW_LIBRARIES})

if(BUILD_LIB)

   add_dependencies(fillwave assimp)
   target_link_libraries(fillwave assimp)
   add_dependencies(fillwave fontgenerator)
   target_link_libraries(fillwave fontgenerator)
   add_dependencies(fillwave freetype)
   target_link_libraries(fillwave freetype)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(fillwave ${OPENGL_LIBRARIES})

endif(BUILD_LIB)



# cpack stuff
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Description.txt")
set(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
set(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")

if (BUILD_DEB)
   SET(CPACK_GENERATOR "DEB")
endif(BUILD_DEB)
if(BUILD_RPM)
   SET(CPACK_GENERATOR "RPM")
endif(BUILD_RPM)

if (BUILD_DEB)
   if(BUILD_LIB)
      SET(CPACK_PACKAGE_NAME "libfillwave")
      set(CPACK_PACKAGE_DESCRIPTION "Fillwave graphics engine library package")
      set(CPACK_PACKAGE_HOMEPAGE "filipwasil.bitbucket.org")
      set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
      set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - easy, fast, reliable:
 Fillwave graphics engine provides easy to use C++11 compliant API for:
  - graphics oriented applications
  - games
  - assets testing
 .
 Simple examples and documentation can be easily found in the web:
 .
 filipwasil.bitbucket.org")
   endif(BUILD_LIB)
      if(BUILD_DEV)
         SET(CPACK_DEBIAN_PACKAGE_NAME "libfillwave-dev")
         set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - development package
 Fillwave development package provides necessary headers for:
  - Fillwave core features
  - font generator feature")
   endif(BUILD_DEV)
endif (BUILD_DEB)

if (BUILD_PACK AND BUILD_LIB)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libglm-dev (>= 0.9.5.1-1), libglew1.10 (>= 1.10.0-3), libglew-dev (>= 1.10.0-3), libassimp3 (>= 3.0~dfsg-2), libassimp-dev (>= 3.0~dfsg-2), libfreetype6 (>= 2.5.2)")
set(CPACK_RPM_PACKAGE_REQUIRES "freetype, assimp")
#set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif(BUILD_PACK AND BUILD_LIB)

if (BUILD_PACK AND BUILD_DEV)
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libfillwave (>= ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})")
#set(CPACK_RPM_PACKAGE_REQUIRES "fillwave")

endif (BUILD_PACK AND BUILD_DEV)

set(CPACK_PACKAGE_DESCRIPTION "Fillwave is a free OpenGL 3.3+ graphics engine for Linux and OSX.")

INCLUDE(CPack)
