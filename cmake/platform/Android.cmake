cmake_minimum_required(VERSION 2.8.8)

# -----------------------------------------------
# Target
# -----------------------------------------------

PROJECT(libfillwave C CXX)

# -----------------------------------------------
# Found by cmake macro
# -----------------------------------------------

# OpenMP

ADD_DEFINITIONS("-fopenmp")
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF(OPENMP_FOUND)

# -----------------------------------------------
# Asset loader
# -----------------------------------------------

IF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_INCLUDES ${CMAKE_SOURCE_DIR}/ext/tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_PATH ${CMAKE_SOURCE_DIR}/ext/tinyobjloader)
ELSE(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER assimp)
   SET(FILLWAVE_EXT_ASSET_LOADER_INCLUDES ${CMAKE_SOURCE_DIR}/ext/assimp/include)
   SET(FILLWAVE_EXT_ASSET_LOADER_PATH ${CMAKE_SOURCE_DIR}/ext/assimp)
ENDIF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)

# -----------------------------------------------
# Includes
# -----------------------------------------------

SET(FILLWAVE_PATH_EXT_INCLUDE ${CMAKE_SOURCE_DIR}/inc)
SET(FILLWAVE_EXT_GLM_INCLUDES ${CMAKE_SOURCE_DIR}/ext/glm)
SET(FILLWAVE_EXT_INCLUDES ${CMAKE_SOURCE_DIR}/ext)
SET(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ${CMAKE_SOURCE_DIR}/ext/fontgenerator)
SET(FILLWAVE_EXT_STB_INCLUDES ${CMAKE_SOURCE_DIR}/ext/stb)
SET(FILLWAVE_EXT_FREETYPE2_INCLUDES ${CMAKE_SOURCE_DIR}/ext/freetype2/include)

SET(BUILD_SHARED_LIBS OFF)

ADD_SUBDIRECTORY(ext/freetype2)
ADD_SUBDIRECTORY(ext/fontgenerator)
ADD_SUBDIRECTORY(${FILLWAVE_EXT_ASSET_LOADER_PATH})

# -----------------------------------------------
# Macros
# -----------------------------------------------

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
INCLUDE ("${CMAKE_SOURCE_DIR}/cmake/data.cmake")

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})

# -----------------------------------------------
# Includes
# -----------------------------------------------

INCLUDE_DIRECTORIES(${GLES30_PROCESS_INCLUDES}
                    ${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_GLM_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    ${FILLWAVE_EXT_ASSET_LOADER_INCLUDES}
                    /usr/include/freetype2)

# -----------------------------------------------
# Linker
# -----------------------------------------------

add_library(fillwave SHARED ${FILLWAVE_SOURCES})
add_library(fillwaveStatic STATIC ${FILLWAVE_SOURCES})
set_target_properties(fillwaveStatic PROPERTIES OUTPUT_NAME fillwave)

add_subdirectory(test_android)

add_dependencies(fillwave log android GLESv3 fontgenerator ${FILLWAVE_EXT_ASSET_LOADER} ${OPENGL_LIBRARIES})
add_dependencies(fillwaveStatic fontgenerator ${FILLWAVE_EXT_ASSET_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

target_link_libraries(fillwave log android GLESv3 fontgenerator ${FILLWAVE_EXT_ASSET_LOADER} ${OPENGL_LIBRARIES})
target_link_libraries(fillwaveStatic fontgenerator ${FILLWAVE_EXT_ASSET_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

# -----------------------------------------------
# Installation
# -----------------------------------------------
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/LICENSE.txt")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Description.txt")
SET(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
SET(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")

SET(CPACK_GENERATOR "TGZ")

SET(CPACK_PACKAGE_NAME "libfillwave")
set(CPACK_PACKAGE_DESCRIPTION "Fillwave graphics engine library package")
set(CPACK_PACKAGE_HOMEPAGE "filipwasil.bitbucket.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - easy, fast, reliable:
 Fillwave graphics engine provides easy to use C++11 compliant API for:
  - graphics oriented applications
  - games
  - assets testing
 .
 Simple examples and documentation can be easily found in the web:
 .
 filipwasil.bitbucket.org")

set(CPACK_PACKAGE_DESCRIPTION "Fillwave is a free OpenGL 3.3+ graphics engine for Linux, Windows, Android and OSX.")

install(DIRECTORY ext/glm DESTINATION include/glm COMPONENT fillwave-dev)
install(DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave-dev)
install(DIRECTORY ext/glm/glm DESTINATION include/glm COMPONENT fillwave-dev)
install(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image.h DESTINATION include)
install(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image_write.h DESTINATION include)
install(FILES ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h DESTINATION include)

install(TARGETS fillwave DESTINATION lib COMPONENT fillwave)
install(TARGETS fillwaveStatic DESTINATION lib COMPONENT fillwaveStatic)

INCLUDE(CPack)
