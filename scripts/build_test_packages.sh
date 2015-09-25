#!/bin/sh

#export CXX=clang++
#export CC=clang

# Prepare build directories
# ../../fillwave_build
# ../../fillwave_example_build

sudo apt-get remove libfillwave* -y
rm -rf ../../fillwave_build/*
if [ $? -eq 0 ]; then
    echo build directory cleared
else
    mkdir ../../fillwave_build
fi
rm -rf ../../fillwave_build/*

rm -rf ../../fillwave_example_build/*
if [ $? -eq 0 ]; then
    echo examples build directory cleared
else
    mkdir ../../fillwave_example_build
fi

# Enter library build directory
cd ../../fillwave_build

# Build library DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DFILLWAVE_COMPILATION_STARTUP_ANIMATION=OFF -DFILLWAVE_COMPILATION_TINY_ASSET_LOADER=OFF -DNDEBUG=ON -DBUILD_PACK=ON -DBUILD_LIB=ON -DBUILD_DEV=ON -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" && make -j8

