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

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/sources.cmake)

# -----------------------------------------------
# Platform
# -----------------------------------------------

if (UNIX AND NOT ANDROID AND NOT APPLE)
  include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Linux.cmake)
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
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/ext/googlebenchmark)
  set_property (TARGET benchmark PROPERTY COMPILE_FLAGS "-Wno-double-promotion -Wno-undef -DBENCHMARK_ENABLE_EXCEPTIONS=OFF -DBENCHMARK_ENABLE_TESTING=OFF")
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/benchmarks)
endif ()

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/flw/Config.h"
)
set (CMAKE_EXTRA_INCLUDE_FILES)
