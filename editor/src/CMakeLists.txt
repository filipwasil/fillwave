aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES} )

add_dependencies(fillwave_qt_example assets_${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    fillwave)
