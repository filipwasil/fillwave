add_subdirectory(../../ext/gtest [EXCLUDE_FROM_ALL])

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(test/)