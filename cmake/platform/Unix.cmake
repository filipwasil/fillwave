# -----------------------------------------------
# OpenMP
# -----------------------------------------------

ADD_DEFINITIONS("-fopenmp")
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF(OPENMP_FOUND)

# -----------------------------------------------
# Package type
# -----------------------------------------------

IF(BUILD_DEV)
   MESSAGE("Building development package")
   PROJECT(libfillwave-dev C CXX)
ENDIF(BUILD_DEV)

IF(BUILD_LIB)
   MESSAGE("Building binary package")
   PROJECT(libfillwave C CXX)
ENDIF(BUILD_LIB)

SET(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
SET(FILLWAVE_EXT_INCLUDES ext)
SET(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ext/fontgenerator)
SET(FILLWAVE_EXT_STB_INCLUDES ext/stb)

# -----------------------------------------------
# Asset loader
# -----------------------------------------------

IF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_INCLUDES ext/tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_PATH ext/tinyobjloader)
ELSE(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER assimp)
ENDIF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)

INCLUDE_DIRECTORIES(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    ${FILLWAVE_EXT_ASSET_LOADER_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# Target
# -----------------------------------------------

IF(BUILD_LIB)
   ADD_LIBRARY(fillwave SHARED ${FILLWAVE_SOURCES})
ENDIF(BUILD_LIB)

# -----------------------------------------------
# Installation
# -----------------------------------------------

IF (BUILD_DEV)
   INSTALL(DIRECTORY inc/fillwave DESTINATION /usr/include COMPONENT fillwave-dev)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image_write.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h DESTINATION /usr/include)
ENDIF(BUILD_DEV)

IF(BUILD_LIB)
   IF(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib64 COMPONENT fillwave)
   ELSE(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib COMPONENT fillwave)
   ENDIF(BUILD_RPM)
ENDIF(BUILD_LIB)
   
# -----------------------------------------------
# Subprojects
# -----------------------------------------------

IF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   ADD_SUBDIRECTORY(${FILLWAVE_EXT_ASSET_LOADER_PATH})
ELSE(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER assimp)
ENDIF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)

ADD_SUBDIRECTORY(ext)
IF(BUILD_DEV)
   ADD_SUBDIRECTORY(test)
ENDIF(BUILD_DEV)

# -----------------------------------------------
# Linker
# -----------------------------------------------

if(BUILD_LIB)
   ADD_DEPENDENCIES(fillwave ${FILLWAVE_EXT_ASSET_LOADER} fontgenerator freetype)
   TARGET_LINK_LIBRARIES(fillwave ${FILLWAVE_EXT_ASSET_LOADER} fontgenerator freetype)

   if(BUILD_PACK)
      ADD_DEPENDENCIES(fillwave GLEW)
      TARGET_LINK_LIBRARIES(fillwave GLEW)
   else(BUILD_PACK)
      ADD_DEPENDENCIES(fillwave glew)
      TARGET_LINK_LIBRARIES(fillwave glew)
   endif(BUILD_PACK)
endif(BUILD_LIB)

# -----------------------------------------------
# Installation
# -----------------------------------------------

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
