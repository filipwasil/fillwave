set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
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
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unreachable-code-loop-increment") # todo CLANG compiler error

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation") # todo freetype
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command") # todo freetype

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")   # todo Log.cpp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion")# todo stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")# todo stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")# todo stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-double-promotion")   # todo stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-disabled-macro-expansion")   # todo stb
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-source-uses-openmp")   # todo stb

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")# todo assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")# todo assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-packed")# todo assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reserved-id-macro") # todo assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")   # todo assimp
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-covered-switch-default") # todo assimp

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef")   # todo glm
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-reinterpret-cast")   # todo glm
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow-field-in-constructor")   # todo glm
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comma")   # stb


# possible to fix
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-float-equal")   # todo CallbackLoop.cpp
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")# todo general
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-private-field")# todo general
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nested-anon-types")# todo general
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")# todo general

# TQuery
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-func-template")# todo general
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-weak-template-vtables")# todo general
