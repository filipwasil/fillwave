
option(FILLWAVE_BUILD_DEV "Build development package" OFF)
option(FILLWAVE_BUILD_LIB "Build main fillwave package" ON)
option(FILLWAVE_BUILD_DEB "Build deb packages" OFF)
option(FILLWAVE_BUILD_RPM "Build rpm packages" OFF)
option(FILLWAVE_BUILD_TGZ "Build tgz packages" OFF)
option(FILLWAVE_BUILD_PACK "Do not build external packages when not needed (Linux builds)" ON)
option(FILLWAVE_COMPILATION_STARTUP_ANIMATION "Run startup animation before any other action" OFF)
option(FILLWAVE_COMPILATION_PC_GLES "Use GLES stub for PC" OFF)
option(NDEBUG "Build with debug logs" OFF)

option(FILLWAVE_MODEL_LOADER_ASSIMP "Use Assimp" ON)
option(FILLWAVE_MODEL_LOADER_TINYOBJLOADER "Use Tinyobjloader" OFF)
option(FILLWAVE_TEXTURE_LOADER_STB "Use STB texture loader" ON)
option(FILLWAVE_SUPPRESS_WARNINGS "Suppress warnings during compilation" ON)

option(FILLWAVE_BUILD_ANDROID_TEST_NATIVE_APP "Build android native test app" OFF)
option(FILLWAVE_BUILD_ANDROID_JNI_LIB "Build android jni library" OFF)

option(FILLWAVE_BUILD_QT_EXAMPLES "Build qt example" OFF)