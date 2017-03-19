cmake_minimum_required (VERSION 2.8.8)

# -----------------------------------------------
# Policies
# -----------------------------------------------

cmake_policy (SET CMP0048 OLD)

# -----------------------------------------------
# Includes
# -----------------------------------------------

include_directories (${FILLWAVE_PATH_INCLUDES})
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../ext/googlebenchmark/include)

# -----------------------------------------------
# Sources
# -----------------------------------------------

aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR} BENCHMARK_SOURCES)

# -----------------------------------------------
# Binary
# -----------------------------------------------

add_executable (benchmarks ${BENCHMARK_SOURCES})

# -----------------------------------------------
# Dependencies
# -----------------------------------------------

add_dependencies (benchmarks benchmark fillwave)

# -----------------------------------------------
# Linked libraries
# -----------------------------------------------

target_link_libraries (benchmarks benchmark fillwave glfw)

# -----------------------------------------------
# Benchmark specific
# -----------------------------------------------

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set (CPP_14_FLAG "-std=c++14")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  if (WIN32)
    set (CPP_14_FLAG "-std=c++14")
  else ()
    set (CPP_14_FLAG "-std=gnu++14")
  endif ()
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set (CPP_14_FLAG "-std=c++14")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
  set (CPP_14_FLAG "-std=c++14")
endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__cplusplus=201402L")

set_property (TARGET benchmark PROPERTY COMPILE_FLAGS "-w -Wno-missing-declarations -w -Wno-old-style-cast ${CPP_14_FLAG}")