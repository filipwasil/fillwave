project(fillwaveInteractiveDemo)
cmake_minimum_required(VERSION 2.8.11)
set(VERSION "1.0.1")
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")
set(PKGSTAT ${PKGSTATUS})
set(PKGT ${PKGTYPE})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)
if (${TESTSTATUS})
    enable_testing()
endif()

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5Xml_INCLUDE_DIRS})

add_subdirectory(src/)
if (${TESTSTATUS})
    add_subdirectory(tests/)
endif()
add_custom_target(
    assets_${PROJECT_NAME}
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/assets  ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/meshes  ${CMAKE_CURRENT_BINARY_DIR}/
)


