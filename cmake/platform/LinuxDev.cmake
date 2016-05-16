CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Package type
# -----------------------------------------------

message("Building development package")
project(libfillwave-dev C CXX)

# -----------------------------------------------
# Asset loader
# -----------------------------------------------

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
                    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
                    ${FILLWAVE_MODEL_LOADER_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# Installation
# -----------------------------------------------

install(DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave-dev)
install(FILES ${FILLWAVE_TEXTURE_LOADER_HEADERS} DESTINATION include)
install(FILES ${FILLWAVE_EXT_FONTGENERATOR_HEADERS} DESTINATION include)

# -----------------------------------------------
# Subprojects
# -----------------------------------------------

ADD_SUBDIRECTORY(ext)

# -----------------------------------------------
# Installation
# -----------------------------------------------

set(CPACK_DEBIAN_PACKAGE_NAME "libfillwave-dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - development package")

if(FILLWAVE_BUILD_PACK)
    set (CPACK_DEBIAN_PACKAGE_DEPENDS "libfillwave (>= ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})")
endif()

include(CPack)
