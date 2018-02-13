cmake_minimum_required (VERSION 2.8.8)

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Source files
# -----------------------------------------------

set (PROJECT_VERSION 1.0.0)

set (SOURCE_FILES
    example_1_scene_and_model.cpp
    ContextGLFW.cpp)

# -----------------------------------------------
# Executable/programs to build
# -----------------------------------------------
set (PROGRAM testApp)
add_executable (${PROGRAM} ${SOURCE_FILES})

include_directories (${PROJECT_INCLUDES})
include_directories (${FILLWAVE_PATH_EXT_INCLUDE})
include_directories (${FILLWAVE_PATH_INCLUDE})
include_directories (${CMAKE_SOURCE_DIR}/inc)

# -----------------------------------------------
# ANDROID
# -----------------------------------------------

if (ANDROID)
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glm")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glew/include")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/assimp/include")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glfw/include")
endif (ANDROID)

# -----------------------------------------------
# APPLE
# -----------------------------------------------

if (APPLE)
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glm")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/assimp/include")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glfw/include")
endif (APPLE)

# -----------------------------------------------
# WINDOWS
# -----------------------------------------------

if (WIN32 OR FILLWAVE_BUILD_PACK)
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glm")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glew/include")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/assimp/include")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
  include_directories ("${CMAKE_SOURCE_DIR}/ext/glfw/include")
  target_link_libraries (${PROGRAM} glfw fillwave)
  install (TARGETS ${PROGRAM} DESTINATION bin COMPONENT fillwave)
endif (WIN32 OR FILLWAVE_BUILD_PACK)

# -----------------------------------------------
# LINUX
# -----------------------------------------------

if(UNIX)
    target_link_libraries (${PROGRAM} pthread glfw fillwave)
    if (ANDROID)
    else()
        copy_resources (${PROGRAM})
    endif ()
else()
    add_dependencies (${PROGRAM} glfw fillwave)
    target_link_libraries (${PROGRAM} glfw fillwave)
endif()

# -----------------------------------------------
# APITRACE DEBUG
# -----------------------------------------------

if (FILLWAVE_DEBUG_OPENGL_APITRACE)
  add_custom_target (
      ${PROGRAM}GenerateTrace ALL
      COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM}.trace
      COMMAND apitrace trace ${CMAKE_BINARY_DIR}/${PROGRAM}
      DEPENDS ${PROGRAM}
      COMMENT "Collect OpenGL trace with apitrace"
      VERBATIM
  )

  add_custom_target (
      ${PROGRAM}ReplayTrace ALL
      COMMAND qapitrace ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM}.trace
      DEPENDS ${PROGRAM}GenerateTrace
      COMMENT "Replay OpenGL trace with qapitrace"
      VERBATIM
  )
endif ()