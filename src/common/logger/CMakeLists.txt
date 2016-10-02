cmake_minimum_required( VERSION 2.8.8 )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} FILLWAVE_LOGGER_SOURCES)

include_directories(${FILLWAVE_PATH_INCLUDE})

add_library(logger SHARED ${FILLWAVE_LOGGER_SOURCES})

if (FILLWAVE_BUILD_DEV)
else()
	if(FILLWAVE_BUILD_RPM)
		install(TARGETS logger DESTINATION lib64)
	else(FILLWAVE_BUILD_RPM)
		install(TARGETS logger DESTINATION lib)
	endif(FILLWAVE_BUILD_RPM)
endif()

IF(ANDROID)
	target_link_libraries(logger log android GLESv3)
ENDIF(ANDROID)
