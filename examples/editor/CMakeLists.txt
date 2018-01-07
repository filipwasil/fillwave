project(fillwaveEditor)

cmake_minimum_required(VERSION 2.8.11)

set(VERSION "1.0.1")
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")
set(EDITOR_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    set (CMAKE_PREFIX_PATH "${QTMSVC}")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)

if (${TESTSTATUS})
    enable_testing()
endif()

if (WIN32)
    include_directories(${FILLWAVE_PATH_INCLUDE})
    include_directories(${FILLWAVE_EXT_GLEW_INCLUDES})
    include_directories(${FILLWAVE_EXT_GLM_INCLUDES})
    include_directories(${FILLWAVE_MODEL_LOADER_INCLUDES})
    include_directories(${FILLWAVE_EXT_FONTGENERATOR_PATH})
endif()

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Xml_INCLUDE_DIRS})

add_subdirectory(src)
if (${TESTSTATUS})
    add_subdirectory(tests)
endif()

