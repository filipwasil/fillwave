include_directories (${LEVEL_EDITOR_SOURCE_DIR}/src)
include_directories (${LEVEL_EDITOR_SOURCE_DIR}/tests/mock/)
##############
# Unit Tests
##############
set (SOURCESRC
    ${SOURCE}
    ${LEVEL_EDITOR_SOURCE_DIR}/src/common/NodeController.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/common/operations/NodeModel.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/common/operations/PrepareItemUniqueId.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/SceneModel.cpp
    ${LEVEL_EDITOR_SOURCE_DIR}/src/objects/standard/Sprite.cpp
    )

add_executable (runUnitTestsLevelEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/common/NodeControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/opearations/PrepareItemUniqueIdTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/opearations/NodeModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/SpriteTest.cpp
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
