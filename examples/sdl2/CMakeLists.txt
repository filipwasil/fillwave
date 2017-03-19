project (fillwave_sdl2_example)
cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_AUTOMOC ON)

# use FindSDL2.cmake
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package (SDL2 REQUIRED)

include_directories (SYSTEM ${SDL2_INCLUDE_DIR})

aux_source_directory (. SRC_FILES)
add_executable (${PROJECT_NAME} ${SRC_FILES})

target_link_libraries (${PROJECT_NAME}
    SDL2
    fillwave)

