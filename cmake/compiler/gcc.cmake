execute_process (COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winvalid-pch")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-include-dirs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoexcept")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-promo")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-null-sentinel")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wtrampolines")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wundef")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunsafe-loop-optimizations")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvector-operation-performance")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
  #Flags added beacuse of externals librabry, GLM and STB.
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=misleading-indentation")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=shift-negative-value")
endif()

# STB library warnings
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion") #stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=old-style-cast")   # stb, assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=zero-as-null-pointer-constant")# stb assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=cast-qual")# stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=missing-declarations") # stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=strict-overflow") # stb

# OpenMP
add_definitions ("-fopenmp")
find_package (OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

if (FILLWAVE_BUILD_PACK)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")   # glm
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-qualifiers")   # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-double-promotion") # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")  # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter") # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic") # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-promo")   # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")  # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-logical-op")   # assimp built internally
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-nonliteral")# assimp built internally
endif ()

if (FILLWAVE_BENCHMARK_TESTS)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")   # Log mechanism
endif()

if (FILLWAVE_COMPILATION_RELEASE)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=format-nonliteral")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-variable")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unsafe-loop-optimizations")
endif()

# Sanitizer. Use when needed.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -g -Wno-error=unsafe-loop-optimizations")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
