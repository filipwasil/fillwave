#!/bin/sh

# Android installation script assumes NDK directory:
# -DANDROID_NDK=~/Tools/android-ndk-r10e
# If this is not true -> change it.

# Remove fillwave from system if installed
sudo apt-get remove libfillwave* -y

# Prepare build directories
mkdir ../../fillwave_android_build
rm -rf ../../fillwave_android_build/*

# Enter build directory
cd ../../fillwave_android_build

# Build
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DNDEBUG=OFF -D_ECLIPSE_VERSION="4.4" -DCMAKE_TOOLCHAIN_FILE=../fillwave/cmake/android.toolchain.cmake -DANDROID_NDK=~/Tools/android-ndk-r10e -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=18 && make -j4

# Crate TGZ package
cpack