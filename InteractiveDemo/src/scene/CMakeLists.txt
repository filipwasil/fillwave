set (SOURCESCENE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/SimpleScene.cpp
    PARENT_SCOPE
    )
set (HEADERSSCENE
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/TextScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ScensFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sceneImp/SimpleScene.h
    PARENT_SCOPE
    )