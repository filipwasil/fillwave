# -----------------------------------------------
# Workarounds
# -----------------------------------------------

if (NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

set(FILLWAVE_PATH_EXT_INCLUDE "inc")
set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_EXT_GLM_INCLUDES ext/glm)
set(FILLWAVE_EXT_INCLUDES ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ext/fontgenerator)
set(FILLWAVE_EXT_STB_INCLUDES ext/stb)
set(FILLWAVE_EXT_ASSIMP_INCLUDES ext/assimp/include)
SET(FILLWAVE_EXT_FREETYPE2_INCLUDES "ext/freetype2/include" )
SET(FILLWAVE_EXT_GLEW_INCLUDES "ext/glew/include" )

add_subdirectory(ext/assimp)
add_subdirectory(ext/glew)
add_subdirectory(ext/freetype2)
add_subdirectory(ext/glfw)
add_subdirectory(ext)
if (BUILD_DEV)
add_subdirectory(test)
endif(BUILD_DEV)

if(BUILD_DEV)
   message("Building development package")
   PROJECT(libfillwave-dev C CXX)
endif(BUILD_DEV)

if(BUILD_LIB)
   message("Building binary package")
   PROJECT(libfillwave C CXX)
endif(BUILD_LIB)

set(PROJECT_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(FILLWAVE_EXT_INCLUDES ext)
set(FILLWAVE_EXT_FONTGENERATOR_INCLUDES ext/fontgenerator)
set(FILLWAVE_EXT_STB_INCLUDES ext/stb)

set(FILLWAVE_PATH_INCLUDE "inc")
set(FILLWAVE_PATH_SOURCE "src")

set(FILLWAVE_PATH_SOURCE_ENGINE_CALLBACKS "actions/engine_callbacks")
set(FILLWAVE_PATH_SOURCE_ITEM_CALLBACKS "actions/item_callbacks")
set(FILLWAVE_PATH_SOURCE_EVENTS "actions/events")
set(FILLWAVE_PATH_SOURCE_CORE "core")
set(FILLWAVE_PATH_SOURCE_EXTRAS "extras")
set(FILLWAVE_PATH_SOURCE_LOADERS "loaders")
set(FILLWAVE_PATH_SOURCE_MANAGEMENT "management")
set(FILLWAVE_PATH_SOURCE_MODELS "models")
set(FILLWAVE_PATH_SOURCE_PARTICLES "particles")
set(FILLWAVE_PATH_SOURCE_SPACE "space")
set(FILLWAVE_PATH_SOURCE_OPERATIONS "operations")
set(FILLWAVE_PATH_SOURCE_ANIMATION "animation")
set(FILLWAVE_PATH_SOURCE_EFFECTS "effects")
set(FILLWAVE_PATH_SOURCE_COMMON "common")
set(FILLWAVE_PATH_SOURCE_TERRAIN "terrain")

aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_ENGINE_CALLBACKS} GL_ENGINE_CALLBACKS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_ITEM_CALLBACKS} GL_ITEM_CALLBACKS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_EVENTS} GL_EVENTS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_CORE} GL_CORE_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_EXTRAS} GL_EXTRAS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_LOADERS} GL_LOADERS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_MANAGEMENT} GL_MANAGEMENT_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_MODELS} GL_MODELS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_PARTICLES} GL_PARTICLES_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_SPACE} GL_SPACE_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_OPERATIONS} GL_OPERATIONS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_ANIMATION} GL_ANIMATION_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_EFFECTS} GL_EFFECTS_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_COMMON} GL_COMMON_SOURCES)
aux_source_directory(${FILLWAVE_PATH_SOURCE}/${FILLWAVE_PATH_SOURCE_TERRAIN} GL_TERRAIN_SOURCES)

set(FILLWAVE_PATH_SOURCE_EXT_FONT_METADATA_DENERATOR "ext/fontGenerator/src/generator_main.cpp.c")

set (FILLWAVE_SOURCES 
     ${FILLWAVE_PATH_SOURCE}/Fillwave.cpp
     ${GL_ENGINE_CALLBACKS_SOURCES}
     ${GL_ITEM_CALLBACKS_SOURCES}
     ${GL_EVENTS_SOURCES}
     ${GL_CORE_SOURCES}
     ${GL_EXTRAS_SOURCES}
     ${GL_LOADERS_SOURCES}
     ${GL_MANAGEMENT_SOURCES}
     ${GL_MODELS_SOURCES}
     ${GL_SPACE_SOURCES}
     ${GL_OPERATIONS_SOURCES}
     ${GL_PICOPNG_SOURCES}
     ${GL_ANIMATION_SOURCES}
     ${GL_EFFECTS_SOURCES}
     ${GL_FONTGENERATOR_SOURCES}
     ${GL_PARTICLES_SOURCES}
     ${GL_COMMON_SOURCES}
     ${GL_TERRAIN_SOURCES}
     )

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_EXT_STB_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# shared library to build
# -----------------------------------------------
if(BUILD_LIB)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
   add_library(fillwave SHARED ${FILLWAVE_SOURCES})
endif(BUILD_LIB)

# -----------------------------------------------
# installation info
# -----------------------------------------------

IF (BUILD_DEV)
   INSTALL(DIRECTORY inc/fillwave DESTINATION /usr/include COMPONENT fillwave-dev)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_STB_INCLUDES}/stb_image_write.h DESTINATION /usr/include)
   INSTALL(FILES ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h DESTINATION /usr/include)
ENDIF(BUILD_DEV)

if (BUILD_LIB)
   if(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib64 COMPONENT fillwave)
   else(BUILD_RPM)
      INSTALL(TARGETS fillwave DESTINATION /usr/lib COMPONENT fillwave)
   endif(BUILD_RPM)
endif (BUILD_LIB)

# -----------------------------------------------
# Link libraries
# -----------------------------------------------
if(BUILD_LIB)
   add_dependencies(fillwave assimp)
   target_link_libraries(fillwave assimp)
   add_dependencies(fillwave fontgenerator)
   target_link_libraries(fillwave fontgenerator)
   add_dependencies(fillwave freetype)
   target_link_libraries(fillwave freetype)
   if(BUILD_PACK)
      add_dependencies(fillwave GLEW)
      target_link_libraries(fillwave GLEW)
   else(BUILD_PACK)
      add_dependencies(fillwave glew)
      target_link_libraries(fillwave glew)
   endif(BUILD_PACK)
endif(BUILD_LIB)

# cpack stuff
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Filip Wasil <fillwave@gmail.com>")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Description.txt")
set(CPACK_PACKAGE_VERSION                 "${PROJECT_VERSION}" )
set(CPACK_PACKAGE_VERSION_MAJOR           "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR           "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH           "${VERSION_PATCH}")

if (BUILD_DEB)
   SET(CPACK_GENERATOR "DEB")
endif(BUILD_DEB)
if(BUILD_RPM)
   SET(CPACK_GENERATOR "RPM")
endif(BUILD_RPM)

if (BUILD_DEB)
   if(BUILD_LIB)
      SET(CPACK_PACKAGE_NAME "libfillwave")
      set(CPACK_PACKAGE_DESCRIPTION "Fillwave graphics engine library package")
      set(CPACK_PACKAGE_HOMEPAGE "filipwasil.bitbucket.org")
      set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
      set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - easy, fast, reliable:
 Fillwave graphics engine provides easy to use C++11 compliant API for:
  - graphics oriented applications
  - games
  - assets testing
 .
 Simple examples and documentation can be easily found in the web:
 .
 filipwasil.bitbucket.org")
   endif(BUILD_LIB)
      if(BUILD_DEV)
         SET(CPACK_DEBIAN_PACKAGE_NAME "libfillwave-dev")
         set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - development package
 Fillwave development package provides necessary headers for:
  - Fillwave core features
  - font generator feature")
   endif(BUILD_DEV)
endif (BUILD_DEB)

if (BUILD_PACK AND BUILD_LIB)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libglm-dev (>= 0.9.5.1-1), libglew1.10 (>= 1.10.0-3), libglew-dev (>= 1.10.0-3), libassimp3 (>= 3.0~dfsg-2), libassimp-dev (>= 3.0~dfsg-2), libfreetype6 (>= 2.5.2)")
set(CPACK_RPM_PACKAGE_REQUIRES "freetype, assimp")
#set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
endif(BUILD_PACK AND BUILD_LIB)

if (BUILD_PACK AND BUILD_DEV)
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libfillwave (>= ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})")
#set(CPACK_RPM_PACKAGE_REQUIRES "fillwave")

endif (BUILD_PACK AND BUILD_DEV)

set(CPACK_PACKAGE_DESCRIPTION "Fillwave is a free OpenGL 3.3+ graphics engine for Linux and OSX.")

INCLUDE(CPack)
