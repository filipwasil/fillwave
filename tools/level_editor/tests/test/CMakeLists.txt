include_directories (${LEVEL_EDITOR_SOURCE_DIR}/src)
include_directories (${LEVEL_EDITOR_SOURCE_DIR}/tests/mocks)
##############
# Unit Tests
##############
file(GLOB_RECURSE SOURCES_OBJECTS ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/*.cpp)
file(GLOB_RECURSE SOURCES_COMMON ${LEVEL_EDITOR_SOURCE_DIR}/src/common/*.cpp)
file(GLOB_RECURSE SOURCES_SCENE ${LEVEL_EDITOR_SOURCE_DIR}/src/scene/*.cpp)

add_executable (runUnitTestsLevelEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/BaseItemTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/TreeItemModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/NodeControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${SOURCES_OBJECTS}
    ${SOURCES_COMMON}
    ${SOURCES_SCENE})

# Standard linking to gtest stuff.
target_link_libraries (runUnitTestsLevelEditor gtest gtest_main gmock gmock_main pthread)

target_link_libraries (runUnitTestsLevelEditor
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Xml
    fillwave)

add_test (NodeControlerTest PrepareItemUniqueIdTest runUnitTestsLevelEditor COMMAND tests/runUnitTests)
