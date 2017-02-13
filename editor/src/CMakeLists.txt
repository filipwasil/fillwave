aux_source_directory(. SRC_FILES)

include_directories(".")

add_subdirectory(common/)
add_subdirectory(loader/)
add_subdirectory(scene/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${SOURCECOMMON} ${HEADERSCOMMON}
               ${SOURCELOADER} ${HEADERSLOADER} ${SOURCESCENE} ${HEADERSSCENE})

add_dependencies(fillwave_qt_example assets_${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    fillwave)
