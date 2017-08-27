set (SOURCEOBJECTS
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/SceneModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NodeFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/standard/Sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/creators/SpriteCreator.cpp
    PARENT_SCOPE
    )
set (HEADERSOBJECTS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/SceneModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/NodeFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/INodeCreator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/INodeBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/standard/Sprite.h
    ${CMAKE_CURRENT_SOURCE_DIR}/creators/SpriteCreator.h
    PARENT_SCOPE
    )