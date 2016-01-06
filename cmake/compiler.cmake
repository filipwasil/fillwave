
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__cplusplus=201103L")
        
if(NOT FILLWAVE_SUPPRESS_WARNINGS)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-variable-declarations")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shorten-64-to-32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-fallthrough")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-weak-vtables")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
        
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation")                 # todo freetype
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command") # todo freetype
        
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")           # todo Log.cpp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion")                    # todo stb
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")            # todo stb
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-align")                    # todo stb

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-float-equal")                   # todo CallbackLoop.cpp

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")            # todo general

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")                # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")                    # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-packed")                        # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reserved-id-macro")             # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")                   # todo assimp
                
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winvalid-pch")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-include-dirs")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoexcept")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-promo")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-null-sentinel")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wtrampolines")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wundef")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunsafe-loop-optimizations")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvector-operation-performance")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-extra-args")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-float-equal")                      # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")                   # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-zero-as-null-pointer-constant")    # todo assimp
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-include-dirs")             # general
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-qual")                        # stb
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-declarations")             # stb
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")                  # build Functions
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")               # we do want to hide them in some cases

        if(FILLWAVE_BUILD_PACK)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow")                       # glm
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-ignored-qualifiers")           # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-double-promotion")             # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")      # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")             # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic")                     # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-promo")                   # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")                  # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-logical-op")                   # assimp built internally
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-nonliteral")            # assimp built internally
        endif()
    endif()
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef")                   # todo CallbackLoop.cpp
endif()