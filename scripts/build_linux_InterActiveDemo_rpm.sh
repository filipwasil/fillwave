#!/usr/bin/env bash
cd ../InteractiveDemo
rm -rf bin
mkdir bin
cp assets/fonts/* bin/
cd bin
cmake .. -DTESTSTATUS=FALSE -DPKGSTATUS=ON -DPKGTYPE=DEB
cpack -c Relase