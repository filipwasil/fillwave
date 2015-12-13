cmake_minimum_required(VERSION 2.8)

execute_process(
   COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/assets
   COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}
   COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/AndroidManifest.xml ${CMAKE_BINARY_DIR}
   COMMAND ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/project.properties ${CMAKE_BINARY_DIR}
   )

# -----------------------------------------------
# ANDROID
# -----------------------------------------------

include_directories(${FREEGLUTGLES_INCLUDE_DIRS} ${GLES30_PROCESS_INCLUDES})
include_directories("${CMAKE_SOURCE_DIR}/ext/glm")
include_directories("${CMAKE_SOURCE_DIR}/ext/glew/include")
include_directories("${CMAKE_SOURCE_DIR}/ext/assimp/include")
include_directories("${CMAKE_SOURCE_DIR}/ext/fontgenerator")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/ContextEGL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/ContextOpenSL)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(fillwave-example SHARED 
            src/ContextEGL/main.cpp
            src/ContextEGL/native_app_glue.cpp
            src/ContextEGL/egl_helper.cpp
            src/ContextOpenSL/native_audio.cpp
            src/TerrainConstructors/PerlinConstructor.cpp
            src/PickableModel.cpp
#           src/example_callbacks.cpp
#           src/example_terrain.cpp
            src/example_animations_with_light.cpp
#            src/example_picking.cpp
#            src/example_particles.cpp
#            src/example_post_processing.cpp
#            src/example_dynamic_texture.cpp
            )

add_dependencies(fillwave-example fillwaveStatic log android EGL  OpenSLES assimp)
target_link_libraries(fillwave-example fillwaveStatic log android EGL  OpenSLES assimp)

