aux_source_directory (. SRC_FILES)
aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/scene/callbacks CALLBACKS_SOURCES)
aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/scene/sceneImp SCENES_SOURCES)

include_directories (".")

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/common)
#add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/loader)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/scene)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable (${PROJECT_NAME} ${SRC_FILES} ${SOURCECOMMON} ${HEADERSCOMMON}
    ${SOURCELOADER} ${HEADERSLOADER} ${SOURCESCENE} ${HEADERSSCENE} ${CALLBACKS_SOURCES})

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
      ${FILLWAVE_LEVEL_EDITOR_ICONS}
      ${CMAKE_BINARY_DIR}/icons)

 #[[ set (CPACK_PACKAGE_VERSION ${VERSION})

  install (TARGETS ${PROJECT_NAME} DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/assets DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/animations DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/buttons DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/fonts DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/meshes DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/other DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/shaders DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/skybox DESTINATION /opt/fillwave)
  install (DIRECTORY ${FILLWAVE_EXAMPLES_DATA}/textures DESTINATION /opt/fillwave)
  install (FILES ${FILLWAVE_EXAMPLES_DATA}/assets/fonts/FreeSans.meta DESTINATION /opt/fillwave)
  install (FILES ${FILLWAVE_EXAMPLES_DATA}/assets/fonts/FreeSans.png DESTINATION /opt/fillwave)

  if (FILLWAVE_BUILD_DEB)
    set (CPACK_GENERATOR "DEB")
  elseif (FILLWAVE_BUILD_RPM)
    set (CPACK_GENERATOR "RPM")
  elseif (FILLWAVE_BUILD_TGZ)
    set (CPACK_GENERATOR "TGZ")
  endif ()

  set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
  set (CPACK_PACKAGE_RELEASE 1)
  set (CPACK_PACKAGE_CONTACT "Anonymus")
  set (CPACK_PACKAGING_INSTALL_PREFIX "/opt/fillwave")
  set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}
.${CMAKE_SYSTEM_PROCESSOR}")]]
endif ()


