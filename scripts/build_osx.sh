#!/bin/sh

# Mak sure homebrew is there
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# Remove fillwave from system if installed
brew uninstall libfillwave libfillwave-dev

# Prepare build directories
mkdir ../../fillwave_osx_build
rm -rf ../../fillwave_osx_build/*

# Enter build directory
cd ../../fillwave_osx_build

# Install other stuff
brew install cmake gcc g++ glm freetype

# we are fine now. go.
cmake ../fillwave -G"Xcode" -DNDEBUG=OFF -DFILLWAVE_BUILD_PACK=ON -DFILLWAVE_BUILD_LIB=ON -DFILLWAVE_BUILD_DEV=OFF -DVERSION_MAJOR=1 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF && cpack

# Crate TGZ package
cpack