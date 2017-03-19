set (FILLWAVE_REAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/Strings.cpp
    )

aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/framework TEST_FRAMEWORK_SOURCES)
aux_source_directory (${CMAKE_CURRENT_SOURCE_DIR}/stubs TEST_STUBS_SOURCES)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

set (FILLWAVE_MOCK_SOURCES
    ${TEST_FRAMEWORK_SOURCES}
    ${TEST_STUBS_SOURCES}
    ${FILLWAVE_REAL_SOURCES}
    )

add_library (fillwave_stubs SHARED ${TEST_STUBS_SOURCES})
add_library (fillwave_mock SHARED ${FILLWAVE_MOCK_SOURCES})