cmake_minimum_required(VERSION 3.1)

if (WIN32)
  add_library(backend STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
else()
  add_library(backend SHARED ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

target_link_libraries(backend ${CMAKE_DL_LIBS})