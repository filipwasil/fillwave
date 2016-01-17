CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# -----------------------------------------------
# Project options
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)

# -----------------------------------------------
# Externals
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/extensions.cmake)

# -----------------------------------------------
# Compiler flags
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/compiler.cmake)

# -----------------------------------------------
# Cmake macros
# -----------------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros/recursiveSearch.cmake)

# -----------------------------------------------
# Directories
# -----------------------------------------------

set(CRATER_PATH_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(CRATER_PATH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CRATER_PATH_SOURCE_CORE "core")
set(CRATER_PATH_SOURCE_CORE_IMAGES "core/images")
set(CRATER_PATH_SOURCE_CORE_VIEWS "core/views")
set(CRATER_PATH_SOURCE_CORE_SYNCHRONIZATION "core/sychronization")
set(CRATER_PATH_SOURCE_CORE_QUERIES "core/queries")

set(CRATER_PATH_SOURCE_HANDLERS "handlers")
set(CRATER_PATH_SOURCE_EXTRAS "extras")
set(CRATER_PATH_SOURCE_MANAGEMENT "managers")
set(CRATER_PATH_SOURCE_MODELS "models")
SET(CRATER_PATH_SOURCE_PARTICLES "particles")
SET(CRATER_PATH_SOURCE_SPACE "space")
SET(CRATER_PATH_SOURCE_ANIMATION "animation")
SET(CRATER_PATH_SOURCE_COMMON "common")

# -----------------------------------------------
# Sources
# -----------------------------------------------

aux_source_directory(${CRATER_PATH_SOURCE} ENGINE_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_CORE} ENGINE_CORE_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_HANDLERS} HANDLERS_SOURCES)

aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_MODELS} MODELS_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_MODELS_SHAPES} MODELS_SHAPES_SOURCES)

aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_EXTRAS} EXTRAS_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_MANAGEMENT} MANAGEMENT_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_PARTICLES} PARTICLES_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_SPACE} SPACE_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_ANIMATION} ANIMATION_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_COMMON} COMMON_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_LOADERS}/configs SHADER_GENERATOR_SOURCES)

aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_CORE_IMAGES} CORE_IMAGES_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_CORE_VIEWS} CORE_VIEWS_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_CORE_SYNCHRONIZATION} CORE_SYNCHRONIZATION_SOURCES)
aux_source_directory(${CRATER_PATH_SOURCE}/${CRATER_PATH_SOURCE_CORE_QUERIES} CORE_QUERIES_SOURCES)

set(CRATER_SOURCES
     ${ENGINE_SOURCES}
     ${ENGINE_CORE_SOURCES}
     ${HANDLERS_SOURCES}
     ${EVENTS_SOURCES}
     ${CORE_IMAGES_SOURCES}
     ${CORE_STATES_SOURCES}
     ${CORE_VIEWS_SOURCES}
     ${CORE_SYNCHRONIZATION_SOURCES}
     ${CORE_QUERIES_SOURCES}
     ${EXTRAS_SOURCES}
     ${MANAGEMENT_SOURCES}
     ${MODELS_SOURCES}
     ${MODELS_SHAPES_SOURCES}
     ${SPACE_SOURCES}
     ${PICOPNG_SOURCES}
     ${ANIMATION_SOURCES}
     ${FONTGENERATOR_SOURCES}
     ${PARTICLES_SOURCES}
     ${COMMON_SOURCES}
     ${SHADER_GENERATOR_SOURCES}
     ${CRATER_MODEL_LOADER_SOURCES}
     ${CRATER_TEXTURE_LOADER_SOURCES}
     ${CRATER_FONT_LOADER_SOURCES}
     ${CRATER_SHADER_LOADER_SOURCES}
     )

# -----------------------------------------------
# Platform
# -----------------------------------------------

if(UNIX AND NOT ANDROID AND NOT APPLE)
	if(CRATER_BUILD_DEV)
		include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/linux/LinuxDev.cmake)
	else(CRATER_BUILD_DEV)
		include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/linux/LinuxLib.cmake)
	endif(CRATER_BUILD_DEV)
endif(UNIX AND NOT ANDROID AND NOT APPLE)

if(ANDROID)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Android.cmake)
endif(ANDROID)

if(APPLE)
	if(CRATER_BUILD_DEV)
		include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/osx/OSXDev.cmake)
	else(CRATER_BUILD_DEV)
		include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/osx/OSXLib.cmake)
	endif(CRATER_BUILD_DEV)
endif(APPLE)

if(WIN32)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform/Windows.cmake)
endif(WIN32)

# -----------------------------------------------
# Tests
# -----------------------------------------------

if (NOT CRATER_BUILD_DEV)
	if(CRATER_TESTS AND NOT WIN32 AND NOT ANDROID)
		include("cmake/tests.cmake")
	endif()
endif()

CONFIGURE_FILE(
"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.h.in"
"${CMAKE_CURRENT_SOURCE_DIR}/inc/crater/Config.h"
)

set(CMAKE_EXTRA_INCLUDE_FILES)
