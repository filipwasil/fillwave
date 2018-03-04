set (SOURCESCENE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardKeyboardEventHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardMouseEventHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/EmptyScene.cpp
    PARENT_SCOPE
    )
set (HEADERSSCENE
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/IEventHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardKeyboardEventHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks/StandardMouseEventHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/EmptyScene.h
    PARENT_SCOPE
    )