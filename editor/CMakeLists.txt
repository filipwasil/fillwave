project(fillwave_qt_example)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})

aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES} )

add_custom_target(
        assets_${PROJECT_NAME}
        COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/assets  ${CMAKE_CURRENT_BINARY_DIR}/
)

add_dependencies(fillwave_qt_example assets_${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    fillwave)
