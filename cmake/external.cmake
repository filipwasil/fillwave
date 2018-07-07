set (FILLWAVE_EXT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set (FILLWAVE_EXT_GLM_INCLUDES ${FILLWAVE_EXT_INCLUDES}/glm)
set (FILLWAVE_EXT_FREETYPE2_INCLUDES ${FILLWAVE_EXT_INCLUDES}/freetype2/include)
set (FILLWAVE_EXT_FREETYPE2_PATH ${FILLWAVE_EXT_INCLUDES}/freetype2)
set (FILLWAVE_EXT_FONTGENERATOR_INCLUDES ${FILLWAVE_EXT_INCLUDES}/fontgenerator)
set (FILLWAVE_EXT_FONTGENERATOR_PATH ${FILLWAVE_EXT_INCLUDES}/fontgenerator)
set (FILLWAVE_EXT_FONTGENERATOR_HEADERS ${FILLWAVE_EXT_FONTGENERATOR_INCLUDES}/fontGenerator.h)
set (FILLWAVE_EXT_GLEW_PATH ${FILLWAVE_EXT_INCLUDES}/glew)
set (FILLWAVE_EXT_GLEW_INCLUDES ${FILLWAVE_EXT_INCLUDES}/glew/include)
set (FILLWAVE_EXT_GLFW_PATH ${FILLWAVE_EXT_INCLUDES}/glfw)
set (FILLWAVE_EXT_COTIRE_PATH ${FILLWAVE_EXT_INCLUDES}/cotire)
set (FILLWAVE_EXAMPLE_EDITOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/examples/editor)
set (FILLWAVE_LEVEL_EDITOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tools/level_editor)

set (FILLWAVE_LOADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/loaders)
set (FILLWAVE_EXAMPLES_DATA ${CMAKE_CURRENT_SOURCE_DIR}/examples/data)
set (FILLWAVE_LEVEL_EDITOR_ICONS ${CMAKE_CURRENT_SOURCE_DIR}/tools/level_editor/icons)

if (FILLWAVE_MODEL_LOADER_ASSIMP)
  set (FILLWAVE_MODEL_LOADER assimp)
  set (FILLWAVE_MODEL_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/assimp/include)
  set (FILLWAVE_MODEL_LOADER_PATH ${FILLWAVE_EXT_INCLUDES}/assimp)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/modelloader/assimp FILLWAVE_MODEL_LOADER_TRAITS)
elseif (FILLWAVE_MODEL_LOADER_TINYOBJLOADER)
  set (FILLWAVE_MODEL_LOADER tinyobjloader)
  set (FILLWAVE_MODEL_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/tinyobjloader)
  set (FILLWAVE_MODEL_LOADER_PATH ${FILLWAVE_EXT_INCLUDES}/tinyobjloader)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/modelloader/tinyobjloader FILLWAVE_MODEL_LOADER_TRAITS)
  add_subdirectory (${FILLWAVE_MODEL_LOADER_PATH})
else ()
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/modelloader/default FILLWAVE_MODEL_LOADER_TRAITS)
endif ()

set (FILLWAVE_TEXTURE_WRITER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/stb)

if (FILLWAVE_TEXTURE_LOADER_GLI)
  set (FILLWAVE_TEXTURE_LOADER gli)
  set (FILLWAVE_TEXTURE_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/gli)
  set (FILLWAVE_TEXTURE_LOADER ${FILLWAVE_EXT_INCLUDES}/gli)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/textureloader/gli FILLWAVE_TEXTURE_LOADER_TRAITS)
elseif(FILLWAVE_TEXTURE_LOADER_SQUISH)
  set (FILLWAVE_TEXTURE_LOADER squish)
  set (FILLWAVE_TEXTURE_LOADER_INCLUDES ${FILLWAVE_EXT_INCLUDES}/gli)
  set (FILLWAVE_TEXTURE_LOADER ${FILLWAVE_EXT_INCLUDES}/gli)
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/textureloader/squish FILLWAVE_TEXTURE_LOADER_TRAITS)
  add_subdirectory(${FILLWAVE_EXT_INCLUDES}/squish)
else()
  set (FILLWAVE_TEXTURE_LOADER "")
  aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/textureloader/stb FILLWAVE_TEXTURE_LOADER_TRAITS)
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/ext/nv_helpers_gl)
endif()

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set (FILLWAVE_GLEW_BUILD glew32)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set (FILLWAVE_GLEW_BUILD glew64)
else ()
  message (FATAL_ERROR "Data width could not be determined!")
endif ()
