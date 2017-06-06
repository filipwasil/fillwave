include_directories (${EDITOR_SOURCE_DIR}/src)
include_directories (${EDITOR_SOURCE_DIR}/tests/mock/)
##############
# Unit Tests
##############
set (SOURCESRC
    ${SOURCE}
    ${EDITOR_SOURCE_DIR}/src/loader/MenuWidgetFabric.cpp
    ${EDITOR_SOURCE_DIR}/src/common/SceneController.cpp
    ${EDITOR_SOURCE_DIR}/src/scene/Renderer.cpp
    ${EDITOR_SOURCE_DIR}/src/scene/sceneImp/TextScene.cpp
    ${EDITOR_SOURCE_DIR}/src/loader/factory/SliderWidgetFactory.cpp
    ${EDITOR_SOURCE_DIR}/src/loader/factory/DialWidgetFactory.cpp
    ${EDITOR_SOURCE_DIR}/src/loader/factory/LineEditWidgetFactory.cpp
    ${EDITOR_SOURCE_DIR}/src/loader/factory/ColorPushButtonWidgetFactory.cpp
    ${EDITOR_SOURCE_DIR}/src/common/translators/MenuWidgetTranslatorStandardValues.cpp
    ${EDITOR_SOURCE_DIR}/src/common/translators/MenuWidgetTranslatorButtonColor.cpp
    ${EDITOR_SOURCE_DIR}/src/common/translators/MenuWidgetTranslatorLineEdit.cpp
    ${EDITOR_SOURCE_DIR}/src/common/translators/IMenuWidgetTranslator.h
    )

add_executable (runUnitTestsEditor
    ${CMAKE_CURRENT_SOURCE_DIR}/loader/MenuWidgetsFabricTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/loader/SceneControllerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${SOURCESRC})

# Standard linking to gtest stuff.
target_link_libraries (runUnitTestsEditor gtest gtest_main gmock gmock_main pthread)

target_link_libraries (runUnitTestsEditor
    Qt5::Widgets
    Qt5::OpenGL
    Qt5::Xml
    fillwave)

add_test (MenuWidgetsFabricTest runUnitTestsEditor COMMAND tests/runUnitTests)
