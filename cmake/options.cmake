# -----------------------------------------------
# Compilation options
# -----------------------------------------------

option (FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS "Usable for mesa shader compiler" ON)
option (FILLWAVE_COMPILATION_SUPPRESS_WARNINGS "Suppress warnings during compilation" OFF)
option (FILLWAVE_COMPILATION_RELEASE "Build type" OFF)

# -----------------------------------------------
# Backend options
# -----------------------------------------------

option (FILLWAVE_BACKEND_OPENGL_45 "Using OpenGL 4.5 core profile" ON)
option (FILLWAVE_BACKEND_OPENGL_ES_20 "Using OpenGL ES 2.0 core profile" OFF)
option (FILLWAVE_BACKEND_OPENGL_ES_30 "Using OpenGL ES 3.0 core profile" OFF)

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

option (FILLWAVE_BUILD_GLFW_EXAMPLES "Build glfw example" OFF)
option (FILLWAVE_BUILD_LEVEL_EDITOR "Build qt level game editor" OFF)
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