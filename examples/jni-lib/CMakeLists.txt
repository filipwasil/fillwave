cmake_minimum_required(VERSION 2.8)

include_directories(${GLES30_PROCESS_INCLUDES})
include_directories(${FILLWAVE_EXT_INCLUDES})
include_directories(${FILLWAVE_EXT_GLM_INCLUDES})
include_directories(${FILLWAVE_MODEL_LOADER_INCLUDES})
include_directories(${FILLWAVE_EXT_FONTGENERATOR_INCLUDES})


add_library(fillwaveJNI SHARED
            FillwaveJNI.cpp
            )

target_link_libraries(fillwaveJNI log android EGL fillwave assimp)
