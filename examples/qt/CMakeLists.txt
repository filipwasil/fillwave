project(fillwave_qt_example)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})

aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    fillwave)