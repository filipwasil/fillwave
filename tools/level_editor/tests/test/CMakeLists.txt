include_directories (${LEVEL_EDITOR_SOURCE_DIR}/src)
include_directories (${LEVEL_EDITOR_SOURCE_DIR}/tests/mocks)
##############
# Unit Tests
##############
set (SOURCESRC
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/items/BaseItem.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/TreeItemModel.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/factories/ItemFactory.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/controllers/NodeController.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/common/operations/SelectItemType.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/common/UUID.cpp
    ${SOURCE}
    )

add_executable (runUnitTestsLevelEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/BaseItemTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/TreeItemModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/NodeControllerTest.cpp
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
