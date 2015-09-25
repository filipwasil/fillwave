#!/bin/sh

#target
sudo apt-get install libfreetype6 libfreetype6-dev libglew1.10 libglew-dev -y
sudo apt-get install libassimp3 libassimp-dev -y
sudo apt-get install libglm-dev -y
sudo apt-get install libx11-dev mesa-utils libglu-dev -y # glxinfo, X11, glu
sudo apt-get install -y libxtst-dev xvfb # freeglut
sudo apt-get install dput -y # adding ppa's

#standard
sudo apt-get install google-chrome-stable vlc -y

#development tools
sudo apt-get install vim git gitk clang cmake mercurial openjdk-7-jre openjdk-7-jdk -y

#packages
sudo apt-get install rpm createrepo reprepro dpkg-dev -y

#documentation metrics
sudo apt-get install latexml doxygen texlive-full texlive-latex-base texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended lmodern latex-beamer cccc cloc vera++ -y

#testing
sudo apt-get install apitrace-gl-tracers apitrace-gl-frontend -y


#opengl
sudo apt-get install xorg-dev libglu1-mesa-dev -y #for randr library for glfw

mkdir ~/.fillwave
cd ~/.fillwave 
git clone https://github.com/glfw/glfw.git
mkdir glfw-build
cd glfw-build
sudo apt-get install xorg-dev libglu1-mesa-dev #for randr library for glfw
cmake ../glfw -DBUILD_SHARED_LIBS=ON

make -j2
sudo make install

# dput ppa:fillwave/fillwave-demo
