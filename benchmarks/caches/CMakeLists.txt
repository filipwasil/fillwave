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

add_executable (benchmarks_caches
    ${BENCHMARK_SOURCES}
    ${FILLWAVE_MOCKS_CORE_SOURCES}
    ${FILLWAVE_MOCKS_CORE_EXTENDED_SOURCES}
    ${FILLWAVE_COMMON_SOURCES}
    ${FILLWAVE_FRAMEWORK_SOURCES}
    ${FILLWAVE_COMMON_SCENE_SOURCES}
    ${FILLWAVE_COMMON_RESOURCES_SOURCES}
    ${FILLWAVE_FRAMEWORK_SOURCES}
    ${FILLWAVE_STUBS_SOURCES}
    ${FILLWAVE_MANAGEMENT_SOURCES}
    ${FILLWAVE_HUD_SOURCES}
    ${FILLWAVE_MODEL_LOADER_SOURCES}
    ${FILLWAVE_MODEL_LOADER_TRAITS}
    ${FILLWAVE_TEXTURE_LOADER_BASE_SOURCES}
    ${FILLWAVE_TEXTURE_LOADER_SOURCES}
    ${FILLWAVE_TEXTURE_LOADER_TRAITS})

# -----------------------------------------------
# Dependencies
# -----------------------------------------------

add_dependencies (benchmarks_caches benchmark fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER})

# -----------------------------------------------
# Linked libraries
# -----------------------------------------------

target_link_libraries (benchmarks_caches benchmark fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER})

# -----------------------------------------------
# Benchmark specific
# -----------------------------------------------

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set_property (TARGET benchmarks_caches PROPERTY COMPILE_FLAGS "-w -Wno-missing-declarations -w -Wno-old-style-cast")