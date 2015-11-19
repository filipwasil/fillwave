CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Found by cmake macro
# -----------------------------------------------

# OpenMP

add_definitions("-fopenmp")
find_package(OpenMP)
if(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(OPENMP_FOUND)

# -----------------------------------------------
# Package type
# -----------------------------------------------

message("Building binary package")
project(libfillwave C CXX)

set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ext/fontgenerator)

# -----------------------------------------------
# Asset loader
# -----------------------------------------------

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
                    ${FILLWAVE_MODEL_LOADER_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# Targets
# -----------------------------------------------

add_library(fillwave SHARED ${FILLWAVE_SOURCES})

# -----------------------------------------------
# Installation
# -----------------------------------------------

if(FILLWAVE_BUILD_RPM)
    install(TARGETS fillwave DESTINATION lib64 COMPONENT fillwave)
else(FILLWAVE_BUILD_RPM)
    install(TARGETS fillwave DESTINATION lib COMPONENT fillwave)
endif(FILLWAVE_BUILD_RPM)
   
# -----------------------------------------------
# Subprojects
# -----------------------------------------------

add_subdirectory(ext)

# -----------------------------------------------
# Linker
# -----------------------------------------------

target_link_libraries(fillwave ${FILLWAVE_MODEL_LOADER} fontgenerator freetype)

if(FILLWAVE_BUILD_PACK)
    add_dependencies(fillwave GLEW)
    target_link_libraries(fillwave GLEW)
else()
    add_subdirectory(${FILLWAVE_EXT_GLEW_PATH})
    add_dependencies(fillwave glew)
    target_link_libraries(fillwave glew)
endif()

# -----------------------------------------------
# Test app
# -----------------------------------------------

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/linux)

# -----------------------------------------------
# Packaging
# -----------------------------------------------

set(CPACK_DEBIAN_PACKAGE_NAME "libfillwave")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - library package")
if (FILLWAVE_BUILD_PACK)
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "libglm-dev (>= 0.9.5.1-1), libglew1.10 (>= 1.10.0-3), libglew-dev (>= 1.10.0-3), libassimp3, libassimp-dev (>= 3.0~dfsg-2), libfreetype6 (>= 2.5.2)")
#set(CPACK_RPM_PACKAGE_REQUIRES "freetype, assimp")
#set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif()

include(CPack)
