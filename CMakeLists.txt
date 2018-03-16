cmake_minimum_required (VERSION 2.8.8)

# -----------------------------------------------
# Workarounds
# -----------------------------------------------

add_definitions (-DASSIMP_BUILD_NO_IFC_IMPORTER)

# -----------------------------------------------
# Project options
# -----------------------------------------------

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)

# -----------------------------------------------
# Compiler flags
# -----------------------------------------------

if (NOT FILLWAVE_COMPILATION_SUPPRESS_WARNINGS)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler/common.cmake)
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler/clang.cmake)
  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler/gcc.cmake)
  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler/msvc.cmake)
  endif ()
endif ()

# -----------------------------------------------
# Directories
# -----------------------------------------------

set (FILLWAVE_PATH_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set (FILLWAVE_PATH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# -----------------------------------------------
# External libraries
# -----------------------------------------------

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/external.cmake)

# -----------------------------------------------
# Sources
# -----------------------------------------------

aux_source_directory (${FILLWAVE_PATH_SOURCE} FILLWAVE_ROOT_SOURCES)

aux_source_directory ("src/core" FILLWAVE_CORE_SOURCES)
aux_source_directory ("src/core/buffers" FILLWAVE_CORE_BUFFERS_SOURCES)
aux_source_directory ("src/core/rendering" FILLWAVE_CORE_RENDERING_SOURCES)
aux_source_directory ("src/core/pipeline" FILLWAVE_CORE_PIPELINE_SOURCES)
aux_source_directory ("src/core/texturing" FILLWAVE_CORE_TEXTURING_SOURCES)
aux_source_directory ("src/core/operations" FILLWAVE_CORE_OPERATIONS_SOURCES)

aux_source_directory ("src/models" FILLWAVE_MODELS_SOURCES)
aux_source_directory ("src/models/base" FILLWAVE_MODELS_BASE_SOURCES)
if (FILLWAVE_MODEL_LOADER_ASSIMP)
  aux_source_directory ("src/models/animations" FILLWAVE_MODELS_ANIMATIONS_SOURCES)
  aux_source_directory ("src/callbacks/animations" FILLWAVE_CALLBACKS_ANIMATIONS_SOURCES)
endif ()
aux_source_directory ("src/models/effects" FILLWAVE_MODELS_EFFECTS_SOURCES)
aux_source_directory ("src/models/builders" FILLWAVE_MODELS_BUILDERS_SOURCES)

aux_source_directory ("src/space" FILLWAVE_SPACE_SOURCES)
aux_source_directory ("src/space/base" FILLWAVE_SPACE_BASE_SOURCES)

aux_source_directory ("src/hud" FILLWAVE_HUD_SOURCES)
aux_source_directory ("src/callbacks" FILLWAVE_CALLBACKS_SOURCES)
aux_source_directory ("src/loaders" FILLWAVE_LOADERS_SOURCES)
aux_source_directory ("src/management" FILLWAVE_MANAGEMENT_SOURCES)
aux_source_directory ("src/common" FILLWAVE_COMMON_SOURCES)
aux_source_directory ("src/renderers" FILLWAVE_RENDERERS_SOURCES)
aux_source_directory ("src/models/shapes" FILLWAVE_SHAPES_SOURCES)

set (FILLWAVE_ENGINE_SOURCES
    ${FILLWAVE_PATH_SOURCE}/engine/Engine.cpp)

set (FILLWAVE_SOURCES
    ${FILLWAVE_ROOT_SOURCES}
    ${FILLWAVE_CORE_SOURCES}
    ${FILLWAVE_CORE_BUFFERS_SOURCES}
    ${FILLWAVE_CORE_RENDERING_SOURCES}
    ${FILLWAVE_CORE_PIPELINE_SOURCES}
    ${FILLWAVE_CORE_TEXTURING_SOURCES}
    ${FILLWAVE_CORE_OPERATIONS_SOURCES}
    ${FILLWAVE_MODELS_SOURCES}
    ${FILLWAVE_MODELS_BASE_SOURCES}
    ${FILLWAVE_MODELS_ANIMATIONS_SOURCES}
    ${FILLWAVE_MODELS_EFFECTS_SOURCES}
    ${FILLWAVE_MODELS_BUILDERS_SOURCES}
    ${FILLWAVE_SPACE_SOURCES}
    ${FILLWAVE_SPACE_BASE_SOURCES}
    ${FILLWAVE_CALLBACKS_SOURCES}
    ${FILLWAVE_CALLBACKS_ANIMATIONS_SOURCES}
    ${FILLWAVE_LOADERS_SOURCES}
    ${FILLWAVE_MANAGEMENT_SOURCES}
    ${FILLWAVE_COMMON_SOURCES}
    ${FILLWAVE_RENDERERS_SOURCES}
    ${FILLWAVE_HUD_SOURCES}
    ${FILLWAVE_MODEL_LOADER_SOURCES}
    ${FILLWAVE_SHAPES_SOURCES}
    ${FILLWAVE_ENGINE_SOURCES}
    )

# -----------------------------------------------
# Platform
# -----------------------------------------------

if (UNIX AND NOT ANDROID AND NOT APPLE)
  if (FILLWAVE_BUILD_DEV)
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/LinuxDev.cmake)
  else ()
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Linux.cmake)
  endif ()
endif ()

if (ANDROID)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Android.cmake)
endif ()

if (APPLE)
  if (IOS)
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/IOS.cmake)
  else ()
    include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/OSX.cmake)
  endif ()
endif ()

if (WIN32)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Windows.cmake)
endif ()

# -----------------------------------------------
# Packaging
# -----------------------------------------------

if (NOT WIN32 AND NOT ANDROID)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/package.cmake)
endif ()

# -----------------------------------------------
# Tests
# -----------------------------------------------

if (FILLWAVE_TESTS)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests.cmake)
endif ()

# -----------------------------------------------
# Multiplatform examples
# -----------------------------------------------

if (FILLWAVE_BUILD_GLFW_EXAMPLES)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/examples/glfw)
endif ()

# -----------------------------------------------
# Benchmarks
# -----------------------------------------------

if (FILLWAVE_BENCHMARK_TESTS)
  set (BENCHMARK_ENABLE_TESTING OFF)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/ext/googlebenchmark)
  set_property (TARGET benchmark PROPERTY COMPILE_FLAGS "-Wno-double-promotion -Wno-undef")
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/benchmarks)
endif ()

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/fillwave/Config.h"
)
set (CMAKE_EXTRA_INCLUDE_FILES)
