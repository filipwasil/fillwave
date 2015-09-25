#!/bin/sh

cd ~/Tools
git clone https://github.com/apitrace/apitrace.git
cd apitrace
export ANDROID_NDK=~/Tools/android-ndk-r10d
cmake -H. -Bbuild -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain/android.toolchain.cmake -DANDROID_API_LEVEL=19 -DANDROID_STL=gnustl_shared -DANDROID_NDK=~/Tools/android-ndk-r10d
make -C build

