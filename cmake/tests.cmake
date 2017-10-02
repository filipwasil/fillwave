	# This adds another subdirectory, which has 'project(gtest)'.

  add_subdirectory (ext/gtest/googlemock)

  enable_testing ()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/inc)
  include_directories (${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/inc)

  ##############
  # Unit Tests
  ##############
  add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/tests)

  aux_source_directory (tests/common TEST_COMMON_SOURCES)
  aux_source_directory (tests/interface TEST_INTERFACE_SOURCES)
  aux_source_directory (tests/core TEST_CORE_SOURCES)
  aux_source_directory (tests/framework TEST_FRAMEWORK_SOURCES)
  set(TEST_SOURCES_PRODUCTION
      ${FILLWAVE_PATH_SOURCE}/models/base/Moveable.cpp
      ${FILLWAVE_PATH_SOURCE}/models/base/MoveableEased.cpp
      ${FILLWAVE_PATH_SOURCE}/common/Easing.cpp)


  set (TEST_SOURCES
      ${TEST_COMMON_SOURCES}
      ${TEST_API_SOURCES}
      ${TEST_CORE_SOURCES}
      ${TEST_FRAMEWORK_SOURCES}
      ${TEST_SOURCES_PRODUCTION}
      )

  add_executable (runUnitTests ${TEST_SOURCES})

  # Remove warnings from
  set_property (TARGET gtest PROPERTY COMPILE_FLAGS "-w -Wno-undef")
  set_property (TARGET gtest_main PROPERTY COMPILE_FLAGS "-w -Wno-undef")
  set_property (TARGET runUnitTests PROPERTY COMPILE_FLAGS "-w -Wno-undef")

  set_property (TARGET gmock PROPERTY COMPILE_FLAGS "-w -Wno-undef")
  # Standard linking to gtest stuff.
  target_link_libraries (runUnitTests gtest fillwave_mock)
  target_link_libraries (runUnitTests gmock)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test (NAME that-test-I-made COMMAND runUnitTests)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test (that-other-test-I-made runUnitTests)

  # -----------------------------------------------
  # Coverity
  # -----------------------------------------------

  if (FILLWAVE_TESTS_COVERALLS)
    set (CMAKE_BUILD_TYPE Debug)
    set (COVERALLS_OUTPUT_FILE test.json)
    set (COV_PATH ${CMAKE_CURRENT_BINARY_DIR})
    set (PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ext/coveralls-cmake/cmake)
    include (Coveralls)
    coveralls_turn_on_coverage ()

    # Create the coveralls target.
    coveralls_setup ("${TEST_SOURCES}" ON)
  endif ()

  add_custom_target (
      postBuildRun ALL
      COMMAND runUnitTests
      DEPENDS runUnitTests
      COMMENT "Running unit tests"
      VERBATIM
  )

  add_dependencies(fillwave postBuildRun)