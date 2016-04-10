cmake_minimum_required(VERSION 2.8.8)

include_directories(${FILLWAVE_EXT_FREETYPE2_INCLUDES} ${FILLWAVE_TEXTURE_WRITER_INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library(fontgenerator STATIC fontGenerator.cpp)

target_link_libraries(fontgenerator freetype)

if(WIN32)
   INSTALL(TARGETS fontgenerator DESTINATION bin)
endif(WIN32)

INSTALL(TARGETS fontgenerator DESTINATION lib)

if (NOT FILLWAVE_BUILD_DEV)
   if(UNIX)
      if(FILLWAVE_BUILD_RPM)
         install(TARGETS fontgenerator DESTINATION usr/lib)
      else(FILLWAVE_BUILD_RPM)
         install(TARGETS fontgenerator DESTINATION usr/lib)
      endif(FILLWAVE_BUILD_RPM)
   endif(UNIX)
endif()
