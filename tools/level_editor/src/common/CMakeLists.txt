set (SOURCECOMMON
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowNodeOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowFileOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/DockWidget.cpp
    PARENT_SCOPE
    )
set (HEADERSCOMMON
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/InternalConsts.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowNodeOperations.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operations/MainWindowFileOperations.h
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets/DockWidget.h
    PARENT_SCOPE
    )