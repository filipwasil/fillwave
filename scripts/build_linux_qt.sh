#!/bin/sh

./build_linux.sh

rm -rf ../../fillwave_qt_build/*

if [ $? -eq 0 ]; then
    echo build directory cleared
else
    mkdir ../../fillwave_qt_build
fi
rm -rf ../../fillwave_qt_build/*

cd ../../fillwave_qt_build

# Build library DEB
cmake ../fillwave -DFILLWAVE_COMPILATION_SUPPRESS_WARNINGS=ON -DNDEBUG=OFF -DFILLWAVE_BUILD_GLFW_EXAMPLES=OFF -DFILLWAVE_BUILD_QT_EXAMPLES=ON -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=OFF && make -j4 && cpack
