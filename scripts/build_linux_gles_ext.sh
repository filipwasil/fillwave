#!/bin/sh

sudo apt-get remove libfillwave* -y

mkdir ../../fillwave_gles_build
rm -rf ../../fillwave_gles_build/*

# Remove external libraries content - we will build using system libraries
# rm -rf ../ext/glew/*
# rm -rf ../ext/assimp/*
# rm -rf ../ext/glm/*
# rm -rf ../ext/glfw/*

cd ../../fillwave_gles_build

# Build library DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_BUILD_FREEGLUT_EXAMPLES=ON -DFILLWAVE_BUILD_PACK=ON -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DFILLWAVE_COMPILATION_PC_GLES=ON -DFILLWAVE_SUPPRESS_WARNINGS=OFF -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=OFF  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
sudo dpkg -i ./libfillwave-*-Linux.deb

# Build dev DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_COMPILATION_PC_GLES=ON  -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=ON  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Install DEBs
sudo dpkg -i ./libfillwave-dev-*-Linux.deb

# Build library RPM
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_BUILD_FREEGLUT_EXAMPLES=ON -DFILLWAVE_BUILD_PACK=ON -DFILLWAVE_BUILD_GLFW_EXAMPLES=OFF  -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DFILLWAVE_COMPILATION_PC_GLES=ON -DFILLWAVE_SUPPRESS_WARNINGS=OFF -DFILLWAVE_BUILD_RPM=ON -DFILLWAVE_BUILD_DEB=OFF -DFILLWAVE_BUILD_DEV=OFF  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Build dev RPM
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_BUILD_GLFW_EXAMPLES=OFF -DFILLWAVE_COMPILATION_PC_GLES=ON -DFILLWAVE_BUILD_RPM=ON -DFILLWAVE_BUILD_DEB=OFF -DFILLWAVE_BUILD_DEV=ON  -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Enter library build directory
cd ../fillwave_gles_build

# Clear temporary cpack archives
rm -rf ./_CPack_Packages/*

# Build DEBIAN remote repository configuration
dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz

# Build RED HAT remote repository configuration
createrepo .
