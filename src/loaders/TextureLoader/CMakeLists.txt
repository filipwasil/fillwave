cmake_minimum_required( VERSION 2.8.8 )

if (GCC_VERSION VERSION_GREATER 6.0)
    add_compile_options(-Wno-misleading-indentation -Wno-shift-negative-value)
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} FILLWAVE_TEXTURE_LOADER_SOURCES)

include_directories(${FILLWAVE_PATH_INCLUDE} ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
        ${FILLWAVE_TEXTURE_LOADER_INCLUDES}/external/glm ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
        )

IF(WIN32)
	include_directories(
			${FILLWAVE_EXT_GLEW_INCLUDES}
			${FILLWAVE_EXT_SPDLOG_INCLUDES}
			)
ENDIF(WIN32)

add_library(textureloader SHARED ${FILLWAVE_TEXTURE_LOADER_SOURCES})

if (FILLWAVE_BUILD_DEV)
else()
	if(FILLWAVE_BUILD_RPM)
		install(TARGETS textureloader DESTINATION lib64)
	else(FILLWAVE_BUILD_RPM)
		install(TARGETS textureloader DESTINATION lib)
	endif(FILLWAVE_BUILD_RPM)
endif()

IF(ANDROID)
	target_link_libraries(textureloader log android GLESv3)
ENDIF(ANDROID)
