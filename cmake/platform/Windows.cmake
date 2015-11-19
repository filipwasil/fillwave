cmake_minimum_required(VERSION 2.8.8)

CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Subprojects
# -----------------------------------------------

ADD_SUBDIRECTORY(${FILLWAVE_MODEL_LOADER_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_EXT_GLEW_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_EXT_FREETYPE2_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_EXT_GLFW_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_EXT_FONTGENERATOR_PATH})

# -----------------------------------------------
# Includes
# -----------------------------------------------

INCLUDE_DIRECTORIES(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_MODEL_LOADER_INCLUDES}
                    ${FILLWAVE_EXT_GLM_INCLUDES}
                    ${FILLWAVE_EXT_FREETYPE2_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_GLEW_INCLUDES}
                    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
                    ${FILLWAVE_PATH_SOURCE_PARTICLES}
                    )

# -----------------------------------------------
# Targets
# -----------------------------------------------

ADD_LIBRARY(fillwave SHARED ${FILLWAVE_SOURCES})

# -----------------------------------------------
# Linker
# -----------------------------------------------

if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
    set( FILLWAVE_GLEW_BUILD glew32 )
elseif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( FILLWAVE_GLEW_BUILD glew64 )
else()
    message( FATAL_ERROR "Data width could not be determined!" )
endif()

ADD_DEPENDENCIES(fillwave ${FILLWAVE_MODEL_LOADER} fontgenerator ${FILLWAVE_GLEW_BUILD})
TARGET_LINK_LIBRARIES(fillwave ${FILLWAVE_MODEL_LOADER} fontgenerator ${FILLWAVE_GLEW_BUILD})
 
# -----------------------------------------------
# Installation
# -----------------------------------------------

INSTALL(DIRECTORY examples/linux/data/shaders DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY examples/linux/data/animations DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY examples/linux/data/fonts DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY examples/linux/data/meshes DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY examples/linux/data/textures DESTINATION bin COMPONENT fillwave)
install(FILES ${FILLWAVE_TEXTURE_LOADER_HEADERS} DESTINATION include)
install(FILES ${FILLWAVE_EXT_FONTGENERATOR_HEADERS} DESTINATION include)
INSTALL(TARGETS fillwave DESTINATION bin COMPONENT fillwave)
INSTALL(DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave)
INSTALL(DIRECTORY ext/glm DESTINATION include COMPONENT fillwave)

SET(CPACK_GENERATOR "TGZ")

INCLUDE(CPack)
