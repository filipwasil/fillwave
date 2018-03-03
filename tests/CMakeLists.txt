set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (FILLWAVE_PRODUCTION_SOURCES
    ${TESTS_DIR}/../src/common/Strings.cpp
    ${TESTS_DIR}/../src/common/Observable.cpp
    )

aux_source_directory (${TESTS_DIR}/framework TEST_FRAMEWORK_SOURCES)
aux_source_directory (${TESTS_DIR}/stubs TEST_STUBS_SOURCES)
aux_source_directory (${TESTS_DIR}/mocks TEST_MOCK_SOURCES)

include_directories (${TESTS_DIR})

set (FILLWAVE_MOCK_SOURCES
    ${TEST_FRAMEWORK_SOURCES}
    ${TEST_STUBS_SOURCES}
    ${FILLWAVE_PRODUCTION_SOURCES}
    )

add_library (fillwave_stubs SHARED ${TEST_STUBS_SOURCES})
add_library (fillwave_mock SHARED ${FILLWAVE_MOCK_SOURCES})

set_property (TARGET fillwave_stubs PROPERTY COMPILE_FLAGS "-w -Wno-undef")
set_property (TARGET fillwave_mock PROPERTY COMPILE_FLAGS "-w -Wno-undef")
