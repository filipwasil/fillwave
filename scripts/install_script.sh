#!/bin/sh
sudo apt-get install libglm-dev libglew1.10 libglew-dev libassimp3 libassimp-dev libfreetype6 xorg-dev 

#glfw3 is needed to be installed manually, so cmake will be necessary
sudo apt-get install git cmake
mkdir ~/.fillwave
cd ~/.fillwave
git clone https://github.com/glfw/glfw.git
mkdir glfw-build
cd glfw-build
cmake ../glfw -DBUILD_SHARED_LIBS=ON
make -j2
sudo make install

#link glew and glfw against linux
sudo ln -s /usr/local/lib/libglfw.so             /usr/lib/libglfw.so.3
#sudo ln -s /usr/lib/x86_64-linux-gnu/libGLEW.so ./usr/lib/libglew.so

