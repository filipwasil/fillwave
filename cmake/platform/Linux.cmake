CMAKE_MINIMUM_REQUIRED( VERSION 2.8.8 )

CMAKE_POLICY(SET CMP0048 NEW)

# -----------------------------------------------
# Package type
# -----------------------------------------------

message("Building binary package")
project(libfillwave VERSION 6.3.0 LANGUAGES C CXX)

# -----------------------------------------------
# Includes
# -----------------------------------------------

include_directories(${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
                    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
                    ${FILLWAVE_EXT_SPDLOG_INCLUDES}
                    /usr/include/freetype2) #uglt freetype2 needs /usr/local/include/freetype2/ft2build.h

if(FILLWAVE_BUILD_PACK)
    include_directories(${FILLWAVE_MODEL_LOADER_INCLUDES})
endif()

if(FILLWAVE_BUILD_PACK)
	include_directories(${FILLWAVE_EXT_GLM_INCLUDES})
endif()

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

if(FILLWAVE_BUILD_PACK)
	add_subdirectory(${FILLWAVE_EXT_GLEW_PATH})
	add_subdirectory(${FILLWAVE_MODEL_LOADER_PATH})
	add_subdirectory(${FILLWAVE_EXT_FREETYPE2_PATH})
	add_subdirectory(${FILLWAVE_EXT_GLFW_PATH}) # needs randr libraries
endif()

# -----------------------------------------------
# Linker
# -----------------------------------------------

if(FILLWAVE_COMPILATION_PC_GLES)
else()
    if(FILLWAVE_BUILD_PACK)
        add_dependencies(fillwave ${FILLWAVE_GLEW_BUILD})
        target_link_libraries(fillwave ${FILLWAVE_GLEW_BUILD})
		include_directories(${FILLWAVE_EXT_GLEW_INCLUDES})
    else()
        target_link_libraries(fillwave GLEW)
    endif()
endif()

target_link_libraries(fillwave ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} fontgenerator freetype)

# -----------------------------------------------
# Test app
# -----------------------------------------------

if(FILLWAVE_BUILD_FREEGLUT_EXAMPLES)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/freeglut)
endif()

if(FILLWAVE_BUILD_LINUX_EXAMPLES)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/linux)
endif()

if(FILLWAVE_BUILD_QT_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/qt)
endif()

if(FILLWAVE_BUILD_SDL2_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/sdl2)
endif()

# -----------------------------------------------
# Packaging
# -----------------------------------------------

set(CPACK_DEBIAN_PACKAGE_NAME "libfillwave")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fillwave graphics engine - library package")

include(CPack)
