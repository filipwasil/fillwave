cmake_minimum_required(VERSION 3.1)

add_library(backend ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

target_link_libraries(backend ${CMAKE_DL_LIBS})