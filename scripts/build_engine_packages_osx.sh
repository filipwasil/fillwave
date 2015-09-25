#!/bin/sh

# Prepare build directories
# ../../fillwave_osx_build

sudo apt-get remove libfillwave* -y
rm -rf ../../fillwave_osx_build/*
if [ $? -eq 0 ]; then
   echo build directory cleared
else
   mkdir ../../fillwave_osx_build
fi
rm -rf ../../fillwave_osx_build/*

# Enter library build directory
cd ../../fillwave_osx_build

# Build library TGZ
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_LIB=ON -DBUILD_DEV=ON -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF  && make -j4 && cpack

#mv ./libfillwave-$1.$2.$3-Linux.tar.gz ../fillwave/doc/html/downloads/libfillwave-$1.$2.$3-Linux.tar.gz
