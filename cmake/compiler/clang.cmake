set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unreachable-code-loop-increment") # todo CLANG compiler error

# possible to fix
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nested-anon-types")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-variable-declarations")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shorten-64-to-32")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-fallthrough")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-weak-vtables")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")# todo assimp
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")# todo assimp


# TQuery
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-func-template")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-weak-template-vtables")

if (FILLWAVE_BUILD_PACK)
  # assimp
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-qualifiers")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-double-promotion")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-promo")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-logical-op")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-nonliteral")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-packed")# todo assimp
endif ()

# external 3d noise generation
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-float-equal")

# stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comma")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-double-promotion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-disabled-macro-expansion")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-source-uses-openmp")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reserved-id-macro")

# freetype
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation")
