set (SOURCECOMMON
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NodeController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowNodeOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowFileOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/NodeModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/PrepareItemUniqueId.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/helpers/StandardItemsHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windows/basic/NewNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windows/basic/NodeNameInput.cpp
    PARENT_SCOPE
    )
set (HEADERSCOMMON
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/NodeController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/InternalConsts.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowNodeOperations.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowFileOperations.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/NodeModel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/PrepareItemUniqueId.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/helpers/StandardItemsHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ENodeType.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/windows/basic/NewNode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/windows/basic/NodeNameInput.h
    PARENT_SCOPE
    )