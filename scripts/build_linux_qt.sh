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
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DFILLWAVE_BUILD_LINUX_EXAMPLES=ON -DFILLWAVE_BUILD_QT_EXAMPLES=ON -DFILLWAVE_SUPPRESS_WARNINGS=OFF -DFILLWAVE_BUILD_RPM=OFF -DFILLWAVE_BUILD_DEB=ON -DFILLWAVE_BUILD_DEV=OFF  -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
