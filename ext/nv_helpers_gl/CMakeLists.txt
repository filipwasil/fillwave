CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

if (WIN32)
  SET (NV_HELPERS_LIBRARY_TYPE STATIC)
else()
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
  #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-declarations")
  #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")

  SET (NV_HELPERS_LIBRARY_TYPE SHARED)
endif ()

add_library(nv_helpers_gl ${NV_HELPERS_LIBRARY_TYPE} nv_dds.cpp)

include_directories(${FILLWAVE_BACKEND_INCLUDES} ${FILLWAVE_PATH_INCLUDE})