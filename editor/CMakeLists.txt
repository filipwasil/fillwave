project(fillwave_qt_example)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET (CMAKE_CXX_FLAGS "-fPIC")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})

add_subdirectory(src/)

add_subdirectory(tests/)

add_custom_target(
        assets_${PROJECT_NAME}
        COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/assets  ${CMAKE_CURRENT_BINARY_DIR}/
)

