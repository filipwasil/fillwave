set (SOURCESCENE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardKeyboardEventHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardMouseEventHandler.cpp
    ${SCENES_SOURCES}
    ${OBJECTS_SOURCES}
    ${TERRAIN_SOURCES}
    PARENT_SCOPE
    )
set (HEADERSSCENE
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/IEventHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardKeyboardEventHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardMouseEventHandler.h
    PARENT_SCOPE
    )