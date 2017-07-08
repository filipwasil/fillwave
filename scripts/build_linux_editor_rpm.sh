#!/usr/bin/env bash
cd ../../
rm -rf build_linux_deb_editor
mkdir build_linux_deb_editor
cd build_linux_deb_editor
cmake ../fillwave -DFILLWAVE_BUILD_QT_EDITOR=ON -DFILLWAVE_BUILD_RPM=ON -DTESTSTATUS=OFF
cmake --build examples/editor -- -j5
cpack -c Relase
