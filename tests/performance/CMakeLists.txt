aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/. TEST_PERFORMANCE_SOURCES)
add_executable(fillwave_performance ${TEST_PERFORMANCE_SOURCES})
target_link_libraries(fillwave_performance fillwave glfw)
