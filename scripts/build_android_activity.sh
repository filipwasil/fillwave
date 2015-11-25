#!/bin/sh

# This scipt buils android JNI lib
# and copies all Android 
# Build jni lib
./build_android_jni_lib.sh

E_BADARGS=85

# Note that this is hardcoded
# You may want to use different ABI

ANDROID_NDK_ABI_NAME=armeabi-v7a

# Android installation script assumes NDK directory:
# -DANDROID_NDK=~/Tools/android-ndk-r10e
# If this is not true -> change it.

# Prepare build directories
mkdir ../../fillwave_android_activity_build
rm -rf ../../fillwave_android_activity_build/*

# Enter build directory
cd ../../fillwave_android_activity_build

cp -R ../fillwave/examples/jni-android-activity/* ./
cp -R ../fillwave/examples/linux/data/* ./assets/
mkdir ./libs/$ANDROID_NDK_ABI_NAME
cp ../fillwave_android_build/libs/$ANDROID_NDK_ABI_NAME/libfillwave.so ./libs/$ANDROID_NDK_ABI_NAME/
cp ../fillwave_android_build/libs/$ANDROID_NDK_ABI_NAME/libfillwaveJNI.so ./libs/$ANDROID_NDK_ABI_NAME/
cp ../fillwave_android_build/ext/assimp/code/libassimp.so ./libs/$ANDROID_NDK_ABI_NAME/
