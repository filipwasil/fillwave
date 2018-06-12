set (SOURCECOMMON
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/UiWindowsCreator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/UiFilesWindowsCreator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/SelectItemType.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/DockWidget.cpp
    PARENT_SCOPE
    )
set (HEADERSCOMMON
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/InternalConsts.h
    ${CMAKE_CURRENT_SOURCE_DIR}/InternalTypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/UiWindowsCreator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/UiFilesWindowsCreator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/ICreateObjectsView.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/SelectItemType.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/DockWidget.h
    PARENT_SCOPE
    )