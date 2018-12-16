cmake_minimum_required(VERSION 2.8.8)

include_directories(
   ${FILLWAVE_EXT_FREETYPE2_INCLUDES}
   ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
)

add_library(fontgenerator STATIC fontGenerator.cpp)

target_link_libraries(fontgenerator freetype)

if(WIN32)
   intall(TARGETS fontgenerator DESTINATION bin)
else()
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-declarations")
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")
endif(WIN32)

INSTALL(TARGETS fontgenerator DESTINATION lib)

if(UNIX)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
   if(FILLWAVE_BUILD_RPM)
      install(TARGETS fontgenerator DESTINATION usr/lib)
   else(FILLWAVE_BUILD_RPM)
      install(TARGETS fontgenerator DESTINATION usr/lib)
   endif(FILLWAVE_BUILD_RPM)
endif(UNIX)
