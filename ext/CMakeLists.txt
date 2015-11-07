CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

if(NOT FILLWAVE_BUILD_DEV OR WIN32 OR ANDROID)
   add_subdirectory(fontgenerator)
endif()