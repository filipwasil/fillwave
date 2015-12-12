project(fillwave_freeglut_example)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

include(FindPkgConfig)
pkg_check_modules(freeglut REQUIRED freeglut-gles>=3.0.0)
if(freeglut_FOUND)
	include_directories(${freeglut_STATIC_INCLUDE_DIRS})
	link_directories(${freeglut_STATIC_LIBRARY_DIRS})
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${freeglut_STATIC_CFLAGS_OTHER}")
	add_definitions(${freeglut_STATIC_CFLAGS_OTHER})
endif()

aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES})

if (FILLWAVE_COMPILATION_PC_GLES)
    set(FILLWAVE_FREEGLUT freeglut-gles)
else()
    set(FILLWAVE_FREEGLUT freeglut)
endif()

target_link_libraries(${PROJECT_NAME}
    ${FILLWAVE_FREEGLUT}
    fillwave)

message ("Copying data ${CMAKE_CURRENT_SOURCE_DIR}/../linux/data to ${CMAKE_CURRENT_BINARY_DIR}")
add_custom_target(
        resources_${PROJECT_NAME}
        COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/../linux/data/*  ${CMAKE_CURRENT_BINARY_DIR}/
)
add_dependencies(${PROJECT_NAME} resources_${PROJECT_NAME})

