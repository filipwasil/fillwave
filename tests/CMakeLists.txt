set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set (FILLWAVE_PRODUCTION_SOURCES
    ${TESTS_DIR}/../src/cmn/Strings.cpp
    ${TESTS_DIR}/../src/cmn/Observable.cpp
    ${TESTS_DIR}/mocks/flc/mProgram.cpp
    ${TESTS_DIR}/mocks/flc/mIBuffer.cpp
    ${TESTS_DIR}/mocks/flc/mFramebuffer.cpp
    ${TESTS_DIR}/mocks/flc/mIndexBuffer.cpp
    ${TESTS_DIR}/mocks/flc/mVertexArray.cpp
    ${TESTS_DIR}/mocks/flc/extended/mSampler.cpp
    ${TESTS_DIR}/mocks/flc/mTexture.cpp
    ${TESTS_DIR}/mocks/flc/mTexture2DRenderable.cpp
    ${TESTS_DIR}/mocks/flc/mShader.cpp
    ${TESTS_DIR}/mocks/flc/mTexture2D.cpp
    )

aux_source_directory (${TESTS_DIR}/framework TEST_FRAMEWORK_SOURCES)

include_directories (${TESTS_DIR})

set (FILLWAVE_TESTS_SOURCES
    ${TEST_FRAMEWORK_SOURCES}
    ${FILLWAVE_COMMON_SOURCES}
    ${FILLWAVE_MOCKS_SOURCES}
    ${FILLWAVE_PRODUCTION_SOURCES}
    )

add_library (fillwave_stubs SHARED ${FILLWAVE_STUBS_SOURCES})
add_library (fillwave_mock SHARED ${FILLWAVE_TESTS_SOURCES})

set_property (TARGET fillwave_stubs PROPERTY COMPILE_FLAGS "-w -Wno-undef")
set_property (TARGET fillwave_mock PROPERTY COMPILE_FLAGS "-w -Wno-undef")
