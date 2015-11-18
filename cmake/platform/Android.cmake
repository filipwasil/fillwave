cmake_minimum_required(VERSION 2.8.8)

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Target
# -----------------------------------------------

PROJECT(libfillwave C CXX)

# -----------------------------------------------
# Found by cmake macro
# -----------------------------------------------

# OpenMP

ADD_DEFINITIONS("-fopenmp")
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF(OPENMP_FOUND)

# -----------------------------------------------
# Includes
# -----------------------------------------------

SET(BUILD_SHARED_LIBS OFF)

ADD_SUBDIRECTORY(${FILLWAVE_EXT_FREETYPE2_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_EXT_FONTGENERATOR_PATH})
ADD_SUBDIRECTORY(${FILLWAVE_MODEL_LOADER_PATH})

# -----------------------------------------------
# Macros
# -----------------------------------------------

INCLUDE ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/data.cmake")

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})

# -----------------------------------------------
# Includes
# -----------------------------------------------

#include(${CMAKE_CURRENT_SOURCE_DIR}/ext/fillwave/cmake/external.cmake)

INCLUDE_DIRECTORIES(${GLES30_PROCESS_INCLUDES}
                    ${FILLWAVE_PATH_INCLUDE}
                    ${FILLWAVE_EXT_GLM_INCLUDES}
                    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
                    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
                    ${FILLWAVE_MODEL_LOADER_INCLUDES})

# -----------------------------------------------
# Linker
# -----------------------------------------------

add_library(fillwave SHARED ${FILLWAVE_SOURCES})
add_library(fillwaveStatic STATIC ${FILLWAVE_SOURCES})
set_target_properties(fillwaveStatic PROPERTIES OUTPUT_NAME fillwave)

add_dependencies(fillwave log android GLESv3 fontgenerator ${FILLWAVE_MODEL_LOADER} ${OPENGL_LIBRARIES})
add_dependencies(fillwaveStatic fontgenerator ${FILLWAVE_MODEL_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

target_link_libraries(fillwave log android GLESv3 fontgenerator ${FILLWAVE_MODEL_LOADER} ${OPENGL_LIBRARIES})
target_link_libraries(fillwaveStatic fontgenerator ${FILLWAVE_MODEL_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

if(FILLWAVE_BUILD_ANDROID_TEST_NATIVE_APP)
    add_subdirectory(test_android)
endif()

if(FILLWAVE_BUILD_ANDROID_JNI_LIB)
    add_subdirectory(stubs/jni-lib)
endif()

# -----------------------------------------------
# Installation
# -----------------------------------------------

install(DIRECTORY ext/glm DESTINATION include/glm COMPONENT fillwave)
install(DIRECTORY inc/fillwave DESTINATION include COMPONENT fillwave)
install(DIRECTORY ext/glm/glm DESTINATION include/glm COMPONENT fillwave)
install(FILES ${FILLWAVE_TEXTURE_LOADER_HEADERS} DESTINATION usr/include)
install(FILES ${FILLWAVE_EXT_FONTGENERATOR_HEADERS} DESTINATION usr/include)

install(TARGETS fillwave DESTINATION lib COMPONENT fillwave)
install(TARGETS fillwaveStatic DESTINATION lib COMPONENT fillwaveStatic)

INCLUDE(CPack)
