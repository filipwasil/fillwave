set(FILLWAVE_REAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/string.cpp
    )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/mocks TEST_MOCKS_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/stubs TEST_STUBS_SOURCES)
set(FILLWAVE_MOCK_SOURCES
    ${TEST_MOCKS_SOURCES}
    ${TEST_STUBS_SOURCES}
    ${FILLWAVE_REAL_SOURCES}
    )
add_library(fillwave_mock SHARED ${FILLWAVE_MOCK_SOURCES})