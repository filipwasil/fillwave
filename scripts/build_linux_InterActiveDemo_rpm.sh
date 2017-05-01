#!/usr/bin/env bash
cd ../InteractiveDemo
rm -rf bin
mkdir bin
cp assets/fonts/* bin/
cd bin
cmake .. -DTESTSTATUS=FALSE -DPKGSTATUS=ON -DPKGTYPE=RPM
make -j3
cpack -c Relase
