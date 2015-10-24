CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Workarounds
# -----------------------------------------------

if (NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

set(FILLWAVE_PATH_EXT_INCLUDE "inc")
set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_EXT_GLM_INCLUDES ext/glm)
set(FILLWAVE_EXT_INCLUDES ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES "ext/fontgenerator")
set(FILLWAVE_EXT_STB_INCLUDES "${CMAKE_SOURCE_DIR}/ext/stb")
set(FILLWAVE_EXT_ASSIMP_INCLUDES ext/assimp/include)

add_subdirectory(ext/assimp)
add_subdirectory(ext/freetype2)

add_subdirectory(ext/glfw)
add_subdirectory(ext)
if (BUILD_DEV)
   add_subdirectory(test)
endif(BUILD_DEV)

if(BUILD_DEV)
   message("Building development package")
   project(libfillwave-dev C CXX)
endif(BUILD_DEV)

if(BUILD_LIB)
   message("Building binary package")
   project(libfillwave C CXX)
endif(BUILD_LIB)

set(FILLWAVE_EXT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/fontgenerator)
set(FILLWAVE_EXT_GLM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)
set(FILLWAVE_EXT_STB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/stb)

set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_PATH_SOURCE "src")

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_ASSIMP_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    ${FILLWAVE_EXT_GLM_INCLUDES}
                    /usr/include/freetype2
                    /usr/local/include)

# -----------------------------------------------
# Targets
# -----------------------------------------------

IF(BUILD_LIB)
ADD_LIBRARY(fillwave SHARED ${FILLWAVE_SOURCES})
ENDIF(BUILD_LIB)

# -----------------------------------------------
# Linker
# -----------------------------------------------

if(BUILD_LIB)
   add_dependencies(fillwave assimp)
   target_link_libraries(fillwave assimp)
   add_dependencies(fillwave fontgenerator)
   target_link_libraries(fillwave fontgenerator)
   add_dependencies(fillwave freetype)
   target_link_libraries(fillwave freetype)
endif(BUILD_LIB)

# -----------------------------------------------
# Found by cmake macro
# -----------------------------------------------

# OpenGL

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(fillwave ${OPENGL_LIBRARIES})

# OpenMP

ADD_DEFINITIONS("-fopenmp")
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF(OPENMP_FOUND)

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
   INSTALL(TARGETS fillwave DESTINATION /usr/lib COMPONENT fillwave)
ENDIF(BUILD_LIB)

set(CMAKE_PREFIX_PATH "/usr/local")
set(CMAKE_LIBRARY_PATH "/usr/local/lib/")

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Description.txt")
set(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
set(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")

INCLUDE(CPack)
