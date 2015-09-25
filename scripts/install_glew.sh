#!/bin/sh

git clone https://github.com/nigels-com/glew.git glew
cd glew
make extensions
#skopiować libGL
sudo ln -s /usr/lib/x86_64-linux-gnu/mesa/libGL.so.1 /usr/lib/libGL.so
sudo ln -s /usr/lib64/libGLEW.so.1.11 /usr/lib/libGLEW.so.1.11
make


