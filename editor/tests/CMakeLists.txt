#This should be change later when script for bulding from main fillwave directory will be ready
add_subdirectory(../../ext/gtest [EXCLUDE_FROM_ALL])

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(test/)