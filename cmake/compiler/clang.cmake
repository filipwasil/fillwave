set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

# possible to fix
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nested-anon-types")

# TQuery
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-func-template")

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
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-packed")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shorten-64-to-32")
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
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-fallthrough")

# freetype
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")

# ok to ignore
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")

# Log mechanism declares static string for each compilation unit.
# This string will be destructed at exit, but it suppose to.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")