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

add_executable (benchmarks_engine ${BENCHMARK_SOURCES})

# -----------------------------------------------
# Dependencies
# -----------------------------------------------

add_dependencies (benchmarks_engine benchmark fillwave)

# -----------------------------------------------
# Linked libraries
# -----------------------------------------------

target_link_libraries (benchmarks_engine benchmark fillwave glfw)

# -----------------------------------------------
# Benchmark specific
# -----------------------------------------------

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set_property (TARGET benchmarks_engine PROPERTY COMPILE_FLAGS "-w -Wno-missing-declarations -w -Wno-old-style-cast")