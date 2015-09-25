#!/bin/sh

# Prepare build directories
# ../../fillwave_android_build

sudo apt-get remove libfillwave* -y
mkdir ../../fillwave_android_build
rm -rf ../../fillwave_android_build/*

# Enter library build directory
cd ../../fillwave_android_build

# Build library TGZ
# API > 18 support openGLES 3.0
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_LIB=ON -DBUILD_DEV=ON -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" -DCMAKE_TOOLCHAIN_FILE=../fillwave/cmake/android.toolchain.cmake -DANDROID_NDK=~/Tools/android-ndk-r10e -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=19 && make -j4 && cpack

rm ../fillwave/doc/html/downloads/libfillwave-$1.$2.$(($3-1))-Linux.tar.gz
mv ./libfillwave-$1.$2.$3-Linux.tar.gz ../fillwave/doc/html/downloads/libfillwave-$1.$2.$3-Linux.tar.gz
