aux_source_directory(. SRC_FILES)

include_directories(".")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/loader)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/scene)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${SOURCECOMMON} ${HEADERSCOMMON}
    ${SOURCELOADER} ${HEADERSLOADER} ${SOURCESCENE} ${HEADERSSCENE})

message(${PROJECT_NAME})
message(${SRC_FILES})
message(${SOURCECOMMON})
message(${HEADERSCOMMON})
message(${SOURCELOADER})

qt5_use_modules(${PROJECT_NAME} Widgets)

add_dependencies(${PROJECT_NAME} assets_${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Xml
    fillwave)
set(CPACK_PACKAGE_VERSION ${VERSION})

#install(TARGETS ${PROJECT_NAME} DESTINATION /opt/fillwave)
#install(DIRECTORY ../assets DESTINATION /opt/fillwave)
#install(FILES ../assets/fonts/FreeSans.meta DESTINATION /opt/fillwave)
#install(FILES ../assets/fonts/FreeSans.png DESTINATION /opt/fillwave)

#CPack rpm/deb files generation
#if(${PKGSTAT} STREQUAL "ON")
#if(${PKGT} STREQUAL "RPM")
#  set(CPACK_GENERATOR "RPM")
#elseif(${PKGT} STREQUAL "DEB")
#  set(CPACK_GENERATOR "DEB")
#endif()
#set(CPACK_PACKAGE_NAME "FillwaveInteractiveDemo")
#set(CPACK_PACKAGE_RELEASE 1)
#set(CPACK_PACKAGE_CONTACT "Anonymus")
#set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/fillwave")
#set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}
#.${CMAKE_SYSTEM_PROCESSOR}")
#include(CPack)
#endif()

