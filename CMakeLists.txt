CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

# -----------------------------------------------
# Workarounds
# -----------------------------------------------

add_definitions(-DASSIMP_BUILD_NO_IFC_IMPORTER)

# -----------------------------------------------
# Project options
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)

# -----------------------------------------------
# Debug or Release
# -----------------------------------------------

if(FILLWAVE_BUILD_RELEASE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# -----------------------------------------------
# Compiler options
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler.cmake)

# -----------------------------------------------
# Directories
# -----------------------------------------------

set(FILLWAVE_PATH_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(FILLWAVE_PATH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# -----------------------------------------------
# External libraries
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/external.cmake)

# -----------------------------------------------
# Sources
# -----------------------------------------------

AUX_SOURCE_DIRECTORY(${FILLWAVE_PATH_SOURCE} FILLWAVE_ROOT_SOURCES)

AUX_SOURCE_DIRECTORY("src/core" FILLWAVE_CORE_SOURCES)
AUX_SOURCE_DIRECTORY("src/core/buffers" FILLWAVE_CORE_BUFFERS_SOURCES)
AUX_SOURCE_DIRECTORY("src/core/rendering" FILLWAVE_CORE_RENDERING_SOURCES)
AUX_SOURCE_DIRECTORY("src/core/pipeline" FILLWAVE_CORE_PIPELINE_SOURCES)
AUX_SOURCE_DIRECTORY("src/core/texturing" FILLWAVE_CORE_TEXTURING_SOURCES)
AUX_SOURCE_DIRECTORY("src/core/operations" FILLWAVE_CORE_OPERATIONS_SOURCES)

AUX_SOURCE_DIRECTORY("src/models" FILLWAVE_MODELS_SOURCES)
AUX_SOURCE_DIRECTORY("src/models/base" FILLWAVE_MODELS_BASE_SOURCES)
if(FILLWAVE_MODEL_LOADER_ASSIMP)
    AUX_SOURCE_DIRECTORY("src/models/animations" FILLWAVE_MODELS_ANIMATIONS_SOURCES)
    AUX_SOURCE_DIRECTORY("src/callbacks/animations" FILLWAVE_CALLBACKS_ANIMATIONS_SOURCES)
endif()
AUX_SOURCE_DIRECTORY("src/models/effects" FILLWAVE_MODELS_EFFECTS_SOURCES)
AUX_SOURCE_DIRECTORY("src/models/builders" FILLWAVE_MODELS_BUILDERS_SOURCES)

AUX_SOURCE_DIRECTORY("src/space" FILLWAVE_SPACE_SOURCES)
AUX_SOURCE_DIRECTORY("src/space/base" FILLWAVE_SPACE_BASE_SOURCES)

AUX_SOURCE_DIRECTORY("src/hud" FILLWAVE_HUD_SOURCES)
AUX_SOURCE_DIRECTORY("src/callbacks" FILLWAVE_CALLBACKS_SOURCES)
AUX_SOURCE_DIRECTORY("src/loaders" FILLWAVE_LOADERS_SOURCES)
AUX_SOURCE_DIRECTORY("src/management" FILLWAVE_MANAGEMENT_SOURCES)
AUX_SOURCE_DIRECTORY("src/common" FILLWAVE_COMMON_SOURCES)
AUX_SOURCE_DIRECTORY("src/renderers" FILLWAVE_RENDERERS_SOURCES)

SET(FILLWAVE_SOURCES
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
        )

# -----------------------------------------------
# Packaging
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/package.cmake)

# -----------------------------------------------
# Platform
# -----------------------------------------------

IF(UNIX AND NOT ANDROID AND NOT APPLE)
    if (FILLWAVE_BUILD_DEV)
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/LinuxDev.cmake)
    else()
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Linux.cmake)
    endif()
ENDIF(UNIX AND NOT ANDROID AND NOT APPLE)

IF(ANDROID)
   include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Android.cmake)
ENDIF(ANDROID)

IF(APPLE)
    if(IOS)
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/IOS.cmake)
    else()
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/OSX.cmake)
    endif()
ENDIF(APPLE)

IF(WIN32)
   include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Windows.cmake)
ENDIF(WIN32)

# -----------------------------------------------
# Tests
# -----------------------------------------------

if (FILLWAVE_TESTS)
   include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests.cmake)
endif()

# -----------------------------------------------
# Benchmarks
# -----------------------------------------------

if (FILLWAVE_BENCHMARK_TESTS)
    set(BENCHMARK_ENABLE_TESTING OFF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/googlebenchmark)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmarks)
endif()

CONFIGURE_FILE(
"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in"
"${CMAKE_CURRENT_SOURCE_DIR}/inc/fillwave/Config.h"
)
SET(CMAKE_EXTRA_INCLUDE_FILES)
