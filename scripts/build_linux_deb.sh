#!/bin/sh

sudo apt-get remove libfillwave* -y
sudo apt-get remove fillwave-examples -y

# Prepare build directories
# ../../fillwave_build
# ../../fillwave-examples_build

rm -rf ../../fillwave_build
rm -rf ../../fillwave-examples_build/*

mkdir ../../fillwave_build


# Remove external libraries content - we will build using system libraries
# rm -rf ../ext/glew/*
# rm -rf ../ext/assimp/*
# rm -rf ../ext/glm/*
# rm -rf ../ext/glfw/*

cd ../../fillwave_build

# Build library DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DFILLWAVE_TESTS=OFF -DNDEBUG=OFF -DFILLWAVE_BUILD_GLFW_EXAMPLES=OFF -DFILLWAVE_COMPILATION_SUPPRESS_WARNINGS=OFF -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=OFF  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
sudo dpkg -i ./libfillwave-*-Linux.deb

# Build dev DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=ON  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Install DEBs
sudo dpkg -i ./libfillwave-dev-*-Linux.deb

# Enter library build directory
cd ../fillwave_build

# Clear temporary cpack archives
rm -rf ./_CPack_Packages/*

# Build DEBIAN remote repository configuration
dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz

cd ..
 
