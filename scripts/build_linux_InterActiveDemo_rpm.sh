#!/usr/bin/env bash
cd ../InteractiveDemo
rm -rf bin
mkdir bin
cd bin
cmake .. -DTESTSTATUS=FALSE -DPKGTYPE=RPM
cpack -c Relase