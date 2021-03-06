set (FILLWAVE_EXT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set (FILLWAVE_EXT_GLM_INCLUDES ${FILLWAVE_EXT_INCLUDES}/glm)
set (FILLWAVE_EXT_FREETYPE2_INCLUDES ${FILLWAVE_EXT_INCLUDES}/freetype2/include)
set (FILLWAVE_EXT_FREETYPE2_PATH ${FILLWAVE_EXT_INCLUDES}/freetype2)
set (FILLWAVE_EXT_FONTGENERATOR_INCLUDES ${FILLWAVE_EXT_INCLUDES}/fontgenerator)
set (FILLWAVE_EXT_FONTGENERATOR_PATH ${FILLWAVE_EXT_INCLUDES}/fontgenerator)
set (FILLWAVE_EXT_FONTGENERATOR_HEADERS ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h)
set (FILLWAVE_EXT_GLFW_PATH ${FILLWAVE_EXT_INCLUDES}/glfw)
set (FILLWAVE_EXT_COTIRE_PATH ${FILLWAVE_EXT_INCLUDES}/cotire)
set (FILLWAVE_EXAMPLE_EDITOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples/editor)
set (FILLWAVE_LEVEL_EDITOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tools/level_editor)

set (FILLWAVE_LOADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders)
set (FILLWAVE_EXAMPLES_DATA ${CMAKE_CURRENT_SOURCE_DIR}/examples/data)
set (FILLWAVE_LEVEL_EDITOR_ICONS ${CMAKE_CURRENT_SOURCE_DIR}/tools/level_editor/icons)

# -----------------------------------------------
# Model loader
# -----------------------------------------------

if (FILLWAVE_MODEL_LOADER_ASSIMP)
  set (FILLWAVE_MODEL_LOADER assimp)
  set (FILLWAVE_MODEL_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/assimp/include)
  set (FILLWAVE_MODEL_LOADER_PATH ${FILLWAVE_EXT_INCLUDES}/assimp)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders/modelloader/assimp FILLWAVE_MODEL_LOADER_TRAITS)
elseif (FILLWAVE_MODEL_LOADER_TINYOBJLOADER)
  set (FILLWAVE_MODEL_LOADER tinyobjloader)
  set (FILLWAVE_MODEL_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/tinyobjloader)
  set (FILLWAVE_MODEL_LOADER_PATH ${FILLWAVE_EXT_INCLUDES}/tinyobjloader)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders/modelloader/tinyobjloader
      FILLWAVE_MODEL_LOADER_TRAITS)
  add_subdirectory (${FILLWAVE_MODEL_LOADER_PATH})
else ()
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders/modelloader/default FILLWAVE_MODEL_LOADER_TRAITS)
endif ()

# -----------------------------------------------
# Backend
# -----------------------------------------------

if (FILLWAVE_BACKEND_OPENGL_45)
  set(FILLWAVE_BACKEND opengl45)
elseif(FILLWAVE_BACKEND_OPENGL_33)
  set(FILLWAVE_BACKEND opengl33)
elseif(FILLWAVE_BACKEND_OPENGL_ES_32)
  set(FILLWAVE_BACKEND opengles32)
elseif(FILLWAVE_BACKEND_OPENGL_ES_30)
  set(FILLWAVE_BACKEND opengles30)
elseif(FILLWAVE_BACKEND_OPENGL_ES_20)
  set(FILLWAVE_BACKEND opengles20)
endif ()
set (FILLWAVE_BACKEND_PATH ${FILLWAVE_EXT_INCLUDES}/backend/${FILLWAVE_BACKEND})
add_subdirectory (${FILLWAVE_BACKEND_PATH})

set (FILLWAVE_BACKEND_INCLUDES ${FILLWAVE_BACKEND_PATH}/glad/include)

# -----------------------------------------------
# Texture loader
# -----------------------------------------------

set (FILLWAVE_TEXTURE_WRITER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/stb)

if (FILLWAVE_TEXTURE_LOADER_CUSTOM)
  message("Here, you can implement your own loader definitions")
  set (FILLWAVE_TEXTURE_LOADER "")
  set (FILLWAVE_TEXTURE_LOADER_INCLUDES)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders/textureloader/custom FILLWAVE_TEXTURE_LOADER_TRAITS)
else()
  set (FILLWAVE_TEXTURE_LOADER nv_helpers_gl)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/flf/loaders/textureloader/stb FILLWAVE_TEXTURE_LOADER_TRAITS)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/ext/nv_helpers_gl)
endif()
