include_directories (${LEVEL_EDITOR_SOURCE_DIR}/src)
include_directories (${LEVEL_EDITOR_SOURCE_DIR}/tests/mock/)
##############
# Unit Tests
##############
set (SOURCESRC
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/items/BaseItem.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/TreeItemModel.cpp
    ${SOURCE}
    )

add_executable (runUnitTestsLevelEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/BaseItemTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/TreeItemModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${SOURCESRC})

# Standard linking to gtest stuff.
target_link_libraries (runUnitTestsLevelEditor gtest gtest_main gmock gmock_main pthread)

target_link_libraries (runUnitTestsLevelEditor
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Xml
    fillwave)

add_test (NodeControlerTest PrepareItemUniqueIdTest runUnitTestsLevelEditor COMMAND tests/runUnitTests)
