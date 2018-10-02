aux_source_directory (. SRC_FILES)
aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/scene/callbacks CALLBACKS_SOURCES)
aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/scene/sceneImp SCENES_SOURCES)

include_directories (".")

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/common)
#add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/loader)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/scene)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/objects)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable (${PROJECT_NAME} ${SRC_FILES} ${SOURCECOMMON} ${HEADERSCOMMON}
    ${SOURCELOADER} ${HEADERSLOADER} ${SOURCESCENE} ${HEADERSSCENE} ${CALLBACKS_SOURCES} ${SOURCEOBJECTS}
    ${HEADERSOBJECTS})

if (WIN32)
  add_dependencies (${PROJECT_NAME} fillwave glfw)
endif ()
qt5_use_modules (${PROJECT_NAME} Widgets)

target_link_libraries (${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Xml
    fillwave)

if (NOT WIN32 AND NOT ANDROID)
  add_custom_command(
      TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${FILLWAVE_EXAMPLES_DATA}
      ${CMAKE_BINARY_DIR})
endif ()


