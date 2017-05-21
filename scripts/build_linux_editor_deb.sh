#!/usr/bin/env bash
cd ../../
rm -rf build_linux_deb_editor
mkdir build_linux_deb_editor
cd build_linux_deb_editor
cmake ../fillwave -DFILLWAVE_BUILD_QT_EDITOR=ON -DTESTSTATUS=OFF -DPKGTYPE=DEB
make -j3
cp ../fillwave/examples/data/fonts/* .
cp -rf ../fillwave/examples/data/* .
#cpack -c Relase
