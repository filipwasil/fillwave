cmake_minimum_required (VERSION 2.8.8)

cmake_policy (SET CMP0048 OLD) #Project version cmake policy
cmake_policy (SET CMP0046 OLD) #Project dependency cmake policy
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)
set(BUILD_CPU_DEMOS OFF)

# -----------------------------------------------
# Subprojects
# -----------------------------------------------

add_subdirectory (${FILLWAVE_MODEL_LOADER_PATH})
add_subdirectory (${FILLWAVE_EXT_GLEW_PATH})
add_subdirectory (${FILLWAVE_EXT_FREETYPE2_PATH})
add_subdirectory (${FILLWAVE_EXT_GLFW_PATH})
add_subdirectory (${FILLWAVE_EXT_FONTGENERATOR_PATH})

# -----------------------------------------------
# Includes
# -----------------------------------------------

set ( FILLWAVE_INCLUDE_DIRECTORIES
    ${FILLWAVE_PATH_INCLUDE}
    ${FILLWAVE_EXT_INCLUDES}
    ${FILLWAVE_MODEL_LOADER_INCLUDES}
    ${FILLWAVE_EXT_GLM_INCLUDES}
    ${FILLWAVE_EXT_FREETYPE2_INCLUDES}
    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
    ${FILLWAVE_EXT_GLEW_INCLUDES}
    ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
    ${FILLWAVE_PATH_SOURCE_PARTICLES}
    )

include_directories(${FILLWAVE_INCLUDE_DIRECTORIES})

# -----------------------------------------------
# Targets
# -----------------------------------------------

add_library (fillwave STATIC ${FILLWAVE_SOURCES})

add_custom_target (
    copy_win
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/ext/glew/Debug/glew64d.lib ${CMAKE_CURRENT_BINARY_DIR}/Debug/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/ext/glew/Debug/glew64d.dll ${CMAKE_CURRENT_BINARY_DIR}/Debug/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/examples/data/ ${CMAKE_CURRENT_BINARY_DIR}/Debug/
)

# -----------------------------------------------
# Linker
# -----------------------------------------------

add_dependencies (fillwave ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} fontgenerator ${FILLWAVE_GLEW_BUILD})
target_link_libraries (fillwave ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} fontgenerator ${FILLWAVE_GLEW_BUILD})

# -----------------------------------------------
# Installation
# -----------------------------------------------

install (DIRECTORY examples/linux/data/shaders DESTINATION bin COMPONENT fillwave)
install (DIRECTORY examples/linux/data/animations DESTINATION bin COMPONENT fillwave)
install (DIRECTORY examples/linux/data/fonts DESTINATION bin COMPONENT fillwave)
install (DIRECTORY examples/linux/data/meshes DESTINATION bin COMPONENT fillwave)
install (DIRECTORY examples/linux/data/textures DESTINATION bin COMPONENT fillwave)
install (FILES ${FILLWAVE_TEXTURE_LOADER_HEADERS} DESTINATION include)
install (FILES ${FILLWAVE_EXT_FONTGENERATOR_HEADERS} DESTINATION include)
install (TARGETS fillwave DESTINATION bin COMPONENT fillwave)
install (DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave)
install (DIRECTORY ext/glm DESTINATION include COMPONENT fillwave)
install (TARGETS fillwave DESTINATION examples/editor COMPONENT fillwave)

set (CPACK_GENERATOR "TGZ")
include (CPack)
