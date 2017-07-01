cmake_minimum_required (VERSION 2.8.8)

#CMAKE_POLICY(SET CMP0048 OLD) #Project version cmake policy
#CMAKE_POLICY(SET CMP0046 OLD) #Project dependency cmake policy

# -----------------------------------------------
# Target
# -----------------------------------------------

project (libfillwave C CXX)

# -----------------------------------------------
# Found by cmake macro
# -----------------------------------------------

# OpenMP
add_definitions ("-fopenmp")
find_package (OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif (OPENMP_FOUND)

# -----------------------------------------------
# Includes
# -----------------------------------------------

set (BUILD_SHARED_LIBS OFF)

add_subdirectory (${FILLWAVE_EXT_FREETYPE2_PATH})
add_subdirectory (${FILLWAVE_EXT_FONTGENERATOR_PATH})

add_subdirectory (${FILLWAVE_MODEL_LOADER_PATH})
if (ANDROID)
  set_property (TARGET ${FILLWAVE_MODEL_LOADER} PROPERTY COMPILE_FLAGS "-w -Wno-undef")
  set_property (TARGET ${FILLWAVE_MODEL_LOADER} PROPERTY COMPILE_FLAGS "-w -Wno-shadow")
  set_property (TARGET ${FILLWAVE_MODEL_LOADER} PROPERTY COMPILE_FLAGS "-w -Wno-ignored-qualifiers")
endif()

# -----------------------------------------------
# Macros
# -----------------------------------------------

include ("${CMAKE_CURRENT_SOURCE_DIR}/cmake/data.cmake")

set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})

# -----------------------------------------------
# Includes
# -----------------------------------------------

#include(${CMAKE_CURRENT_SOURCE_DIR}/ext/fillwave/cmake/external.cmake)

include_directories (${GLES30_PROCESS_INCLUDES}
    ${FILLWAVE_PATH_INCLUDE}
    ${FILLWAVE_EXT_GLM_INCLUDES}
    ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}
    ${FILLWAVE_TEXTURE_WRITER_INCLUDES}
    ${FILLWAVE_TEXTURE_LOADER_INCLUDES}
    ${FILLWAVE_MODEL_LOADER_INCLUDES})

# -----------------------------------------------
# Linker
# -----------------------------------------------

add_library (fillwave SHARED ${FILLWAVE_SOURCES})
add_library (fillwaveStatic STATIC ${FILLWAVE_SOURCES})
set_target_properties (fillwaveStatic PROPERTIES OUTPUT_NAME fillwave)

add_dependencies (fillwave log android GLESv3 fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} ${OPENGL_LIBRARIES})
add_dependencies (fillwaveStatic fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

target_link_libraries (fillwave log android GLESv3 fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} ${OPENGL_LIBRARIES})
target_link_libraries (fillwaveStatic fontgenerator ${FILLWAVE_MODEL_LOADER} ${FILLWAVE_TEXTURE_LOADER} log android GLESv3 ${OPENGL_LIBRARIES})

if (FILLWAVE_BUILD_ANDROID_TEST_NATIVE_APP)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/examples/android)
endif ()

if (FILLWAVE_BUILD_ANDROID_JNI_LIB)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/examples/jni-lib)
endif ()
