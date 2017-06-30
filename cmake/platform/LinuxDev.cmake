cmake_minimum_required (VERSION 2.8.8)

cmake_policy (SET CMP0048 NEW)

# -----------------------------------------------
# Package type
# -----------------------------------------------

message ("Building development package")
project (libfillwave-dev VERSION 7.0.0 LANGUAGES C CXX)

# -----------------------------------------------
# Asset loader
# -----------------------------------------------

include_directories (${FILLWAVE_PATH_INCLUDE}
    ${FILLWAVE_EXT_INCLUDES}
    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
    ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
    ${FILLWAVE_MODEL_LOADER_INCLUDES}
    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

# -----------------------------------------------
# Installation
# -----------------------------------------------

install (DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave-dev)
install (FILES ${FILLWAVE_TEXTURE_LOADER_HEADERS} DESTINATION include)
install (FILES ${FILLWAVE_EXT_FONTGENERATOR_HEADERS} DESTINATION include)

# -----------------------------------------------
# Subprojects
# -----------------------------------------------

add_subdirectory (ext)

# -----------------------------------------------
# Installation
# -----------------------------------------------

set (CPACK_DEBIAN_PACKAGE_NAME "libfillwave-dev")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - development package")
