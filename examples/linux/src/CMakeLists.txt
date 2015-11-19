cmake_minimum_required(VERSION 2.8.8)

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Source files
# -----------------------------------------------

#PROJECT(testGameExample C CXX)

set(PROJECT_VERSION 1.0.0)

aux_source_directory (CallbacksGLFW/ SOURCE_CALLBACKS_GLFW)
aux_source_directory (TerrainConstructors/ SOURCE_CONSTRUCTORS)

set(SOURCE_FILES test.cpp
                 ContextGLFW.cpp
                 PickableModel.cpp
                 GradientBall.cpp
                 ${SOURCE_CALLBACKS_GLFW}
                 ${SOURCE_CONSTRUCTORS})

# -----------------------------------------------
# Executable/programs to build
# -----------------------------------------------
set(PROGRAM testApp)
add_executable(${PROGRAM} ${SOURCE_FILES})

include_directories(${PROJECT_INCLUDES})
include_directories(${FILLWAVE_PATH_EXT_INCLUDE})
include_directories(${FILLWAVE_PATH_INCLUDE})
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/test/inc)

# -----------------------------------------------
# ANDROID
# -----------------------------------------------

if(ANDROID)
   include_directories("${CMAKE_SOURCE_DIR}/ext/glm")
   include_directories("${CMAKE_SOURCE_DIR}/ext/glew/include")
   include_directories("${CMAKE_SOURCE_DIR}/ext/assimp/include")
   include_directories("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
   include_directories("${CMAKE_SOURCE_DIR}/ext/glfw/include")
endif(ANDROID)

# -----------------------------------------------
# APPLE
# -----------------------------------------------

if(APPLE)
   include_directories("${CMAKE_SOURCE_DIR}/ext/glm")
   include_directories("${CMAKE_SOURCE_DIR}/ext/assimp/include")
   include_directories("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
   include_directories("${CMAKE_SOURCE_DIR}/ext/glfw/include")
endif(APPLE)

# -----------------------------------------------
# WINDOWS
# -----------------------------------------------

if(WIN32)
   include_directories("${CMAKE_SOURCE_DIR}/ext/glm")
   include_directories("${CMAKE_SOURCE_DIR}/ext/glew/include")
   include_directories("${CMAKE_SOURCE_DIR}/ext/assimp/include")
   include_directories("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
   include_directories("${CMAKE_SOURCE_DIR}/ext/glfw/include")
   target_link_libraries(${PROGRAM}  glfw fillwave)
   INSTALL(TARGETS ${PROGRAM} DESTINATION bin COMPONENT fillwave)
endif(WIN32)

# -----------------------------------------------
# LINUX
# -----------------------------------------------

if(UNIX AND NOT ANDROID)
   add_dependencies(${PROGRAM} pthread glfw fillwave)
   target_link_libraries(${PROGRAM}  pthread glfw fillwave)
   COPY_RESOURCES(${PROGRAM})
endif(UNIX AND NOT ANDROID)