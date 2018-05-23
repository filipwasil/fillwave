set (SOURCEOBJECTS
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/items/BaseItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TreeItemModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/NodeController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/factories/ItemFactory.cpp
    PARENT_SCOPE
    )
set (HEADERSOBJECTS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/IItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TreeItemModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/items/BaseItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/NodeController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/factories/IItemFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/factories/ItemFactory.h
    PARENT_SCOPE
    )