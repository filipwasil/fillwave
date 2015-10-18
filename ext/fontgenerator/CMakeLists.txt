cmake_minimum_required(VERSION 2.8.8)

SET(FONTGENERATOR_SOURCES fontGenerator.cpp)

if (ANDROID OR WIN32)
   INCLUDE_DIRECTORIES(${FILLWAVE_EXT_FREETYPE2_INCLUDES} ${FILLWAVE_EXT_STB_INCLUDES})
endif(ANDROID OR WIN32)

INCLUDE_DIRECTORIES (../../ext/stb)
INCLUDE_DIRECTORIES (../../ext/freetype2/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ADD_LIBRARY(fontgenerator STATIC ${FONTGENERATOR_SOURCES})

target_link_libraries(fontgenerator freetype)

if(WIN32)
   INSTALL(TARGETS fontgenerator DESTINATION bin)
   INSTALL(TARGETS fontgenerator DESTINATION lib)
endif(WIN32)

INSTALL(TARGETS fontgenerator DESTINATION lib)

if (NOT BUILD_DEV)
   if(UNIX)
      if(BUILD_RPM)
         INSTALL(TARGETS fontgenerator DESTINATION /usr/lib)
      else(BUILD_RPM)
         INSTALL(TARGETS fontgenerator DESTINATION /usr/lib)
      endif(BUILD_RPM)
   endif(UNIX)
endif(NOT BUILD_DEV)

if (ANDROID)
   INSTALL(TARGETS fontgenerator DESTINATION lib)
endif(ANDROID)
