cmake_minimum_required(VERSION 2.8.8)

CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Directories
# -----------------------------------------------

SET(FILLWAVE_PATH_EXT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
SET(FILLWAVE_EXT_GLM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)
SET(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/fontgenerator)
SET(FILLWAVE_EXT_STB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/stb)
SET(FILLWAVE_EXT_FREETYPE2_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype2/include )
SET(FILLWAVE_EXT_GLEW_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/include )

# -----------------------------------------------
# Assets loader
# -----------------------------------------------

IF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_INCLUDES ${CMAKE_SOURCE_DIR}/ext/tinyobjloader)
   SET(FILLWAVE_EXT_ASSET_LOADER_PATH ${CMAKE_SOURCE_DIR}/ext/tinyobjloader)
ELSE(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)
   SET(FILLWAVE_EXT_ASSET_LOADER assimp)
   SET(FILLWAVE_EXT_ASSET_LOADER_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext/assimp/include)
   SET(FILLWAVE_EXT_ASSET_LOADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/assimp)
ENDIF(FILLWAVE_COMPILATION_TINY_ASSET_LOADER)

# -----------------------------------------------
# Subprojects
# -----------------------------------------------

ADD_SUBDIRECTORY(${FILLWAVE_EXT_ASSET_LOADER_PATH})
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/ext/glew)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype2)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/ext/fontgenerator)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test)

# -----------------------------------------------
# Includes
# -----------------------------------------------

INCLUDE_DIRECTORIES(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_ASSET_LOADER_INCLUDES}
                    ${FILLWAVE_EXT_GLM_INCLUDES}
                    ${FILLWAVE_EXT_FREETYPE2_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_GLEW_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    ${FILLWAVE_PATH_SOURCE_PARTICLES}
                    )

# -----------------------------------------------
# Targets
# -----------------------------------------------

ADD_LIBRARY(fillwave SHARED ${FILLWAVE_SOURCES})

# -----------------------------------------------
# Linker
# -----------------------------------------------

ADD_DEPENDENCIES(fillwave ${FILLWAVE_EXT_ASSET_LOADER} fontgenerator glew64)
TARGET_LINK_LIBRARIES(fillwave ${FILLWAVE_EXT_ASSET_LOADER} fontgenerator glew64)
 
# -----------------------------------------------
# Installation
# -----------------------------------------------

INSTALL(DIRECTORY test/data/shaders DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY test/data/animations DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY test/data/fonts DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY test/data/meshes DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY test/data/textures DESTINATION bin COMPONENT fillwave)
INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image.h DESTINATION include)
INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image_write.h DESTINATION include)
INSTALL(FILES ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h DESTINATION include)
INSTALL(TARGETS fillwave DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave)
INSTALL(DIRECTORY ext/glm DESTINATION include COMPONENT fillwave)

SET(CPACK_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}\\\\doc/LICENSE.txt")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}\\\\doc/Description.txt")
SET(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
SET(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")

SET(CPACK_GENERATOR "TGZ")
INCLUDE(CPack)
