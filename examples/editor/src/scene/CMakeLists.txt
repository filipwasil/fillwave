aux_source_directory ("sceneImp/callbacks" CALLBACKS_SOURCES)

set (SOURCESCENE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/AnimationScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/${CALLBACKS_SOURCES}
    PARENT_SCOPE
    )
set (HEADERSSCENE
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.h
    PARENT_SCOPE
    )