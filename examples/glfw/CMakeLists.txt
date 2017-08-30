# -----------------------------------------------
# Project cmake file
# -----------------------------------------------
project (fillwaveexample)
cmake_minimum_required (VERSION 2.8.8)

# -----------------------------------------------
# Main compilation details
# -----------------------------------------------

# -----------------------------------------------
# Compiler configuration
# -----------------------------------------------

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set (CMAKE_BUILD_TYPE Debug)
# -----------------------------------------------
# Cmake macros
# -----------------------------------------------
include ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Resources.cmake")

# -----------------------------------------------
# Include directories
# -----------------------------------------------

set (PROJECT_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/inc")

# -----------------------------------------------
# Add sub-directories to be included
# -----------------------------------------------
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory (src)
