# -----------------------------------------------
# Main Options
# -----------------------------------------------

option (FILLWAVE_BUILD_DEV "Build development package" OFF)
option (FILLWAVE_BUILD_LIB "Build main fillwave package" ON)
option (FILLWAVE_BUILD_DEB "Build deb packages" OFF)
option (FILLWAVE_BUILD_RPM "Build rpm packages" OFF)
option (FILLWAVE_BUILD_TGZ "Build tgz packages" OFF)
option (FILLWAVE_BUILD_PACK "Do not build external packages when not needed (Linux builds)" OFF)

# -----------------------------------------------
# Compilation options
# -----------------------------------------------

option (FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS "Usable for mesa shader compiler" ON)
option (FILLWAVE_COMPILATION_OPTIMIZE_RAM_USAGE "Asset data are stored only in GPU" OFF)
option (FILLWAVE_COMPILATION_SUPPRESS_WARNINGS "Suppress warnings during compilation" OFF)
option (FILLWAVE_COMPILATION_RELEASE "Build type" OFF)

# -----------------------------------------------
# Backend options
# -----------------------------------------------

option (FILLWAVE_BACKEND_OPENGL_33 "Using OpenGL 3.3 core profile" OFF)
option (FILLWAVE_BACKEND_OPENGL_45 "Using OpenGL 4.5 core profile" ON)
option (FILLWAVE_BACKEND_OPENGL_ES_20 "Using OpenGL ES 2.0 core profile" OFF)
option (FILLWAVE_BACKEND_OPENGL_ES_30 "Using OpenGL ES 3.0 core profile" OFF)
option (FILLWAVE_BACKEND_OPENGL_ES_32 "Using OpenGL ES 3.2 core profile" OFF)
option (FILLWAVE_BACKEND_OPENGL_ES_PC "Using OpenGL ES FOR PC" OFF)

# -----------------------------------------------
# Tests related options
# -----------------------------------------------

option (FILLWAVE_TESTS "Build with gtest tests" OFF)
option (FILLWAVE_TESTS_COVERALLS "Generate coveralls data" OFF)

# -----------------------------------------------
# External libraries options
# -----------------------------------------------

option (FILLWAVE_MODEL_LOADER_ASSIMP "Use Assimp" ON)
option (FILLWAVE_MODEL_LOADER_TINYOBJLOADER "Use Tiny obj loader" OFF)
option (FILLWAVE_TEXTURE_LOADER_CUSTOM "Use custom texture loader" OFF)

# -----------------------------------------------
# Build components Options
# -----------------------------------------------

option (FILLWAVE_BUILD_ANDROID_TEST_NATIVE_APP "Build android native test app" OFF)
option (FILLWAVE_BUILD_ANDROID_JNI_LIB "Build android jni library" OFF)
option (FILLWAVE_BUILD_GLFW_EXAMPLES "Build glfw example" OFF)
option (FILLWAVE_BUILD_FREEGLUT_EXAMPLES "Build linux example" OFF)
option (FILLWAVE_BUILD_QT_EXAMPLES "Build qt example" OFF)
option (FILLWAVE_BUILD_LEVEL_EDITOR "Build qt level game editor" OFF)
option (FILLWAVE_BUILD_SDL2_EXAMPLES "Build sdl2 example" OFF)
option (FILLWAVE_BUILD_COTIRE "Build with cotire" OFF)

# -----------------------------------------------
# Benchmark options
# -----------------------------------------------

option (FILLWAVE_BENCHMARK_TESTS "Build binary to test performance" OFF)

# -----------------------------------------------
# Additional Options
# -----------------------------------------------

option (FILLWAVE_DEBUG_OPENGL_APITRACE "Use apitrace to generate OpenGL trace" OFF)

# -----------------------------------------------
# CI Options
# -----------------------------------------------
