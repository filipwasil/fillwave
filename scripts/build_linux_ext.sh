#!/bin/sh

sudo apt-get remove libfillwave* -y
sudo apt-get remove fillwave-examples -y

mkdir ../../fillwave_build_with_external_libraries

cd ../../fillwave_build_with_external_libraries

# Build library DEB
cmake ../fillwave -DNDEBUG=OFF -DFILLWAVE_BUILD_LINUX_EXAMPLES=ON -DFILLWAVE_SUPPRESS_WARNINGS=OFF -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DFILLWAVE_BUILD_DEV=OFF  -DFILLWAVE_BUILD_PACK=ON && make
