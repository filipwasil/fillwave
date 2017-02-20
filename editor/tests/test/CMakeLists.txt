include_directories(${CMAKE_SOURCE_DIR}/src/loader)
##############
# Unit Tests
##############
set(SOURCESRC
        ${SOURCE}
        ${CMAKE_SOURCE_DIR}/src/loader/MenuWidgetFabric.cpp
        ${CMAKE_SOURCE_DIR}/src/loader/factory/SliderWidgetFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/loader/factory/DialWidgetFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/loader/factory/LineEditWidgetFactory.cpp
        )

add_executable(runUnitTests loader/MenuWidgetsFabricTest.cpp MainTest.cpp ${SOURCESRC})

# Standard linking to gtest stuff.
target_link_libraries(runUnitTests gtest gtest_main)

target_link_libraries(runUnitTests
        Qt5::Widgets
        Qt5::OpenGL
        Qt5::Xml
        fillwave)

add_test(MenuWidgetsFabricTest runUnitTests COMMAND tests/runUnitTests)
