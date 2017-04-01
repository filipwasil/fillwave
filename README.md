# Fillwave graphics engine

[Fillwave]: http://filipwasil.bitbucket.org/

[![Join the chat at https://gitter.im/filipwasil/fillwave](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/filipwasil/fillwave?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[Fillwave] is a modern, native and totally free rendering engine writen in c++14.

Can be used in any 3D games, apps and visualization tools or as a regular part of your game engine.

- Multiplatform (Linux, Windows, Android, OSX)
- Native Android apps (JNI, or C++).
- Using the greatest open source libraries (Ex. glm for math and assimp for assets)
- OpenGL ES 3.0 and OpenGL 3.3+ support with programmable pipeline
- Engine can be fully open source and free under BSD license

- All models placed in examples/linux/data are various models which I found across internet.
  I was looking only for free ones in case of which the license permits for placing them here.
  If your work is placed here, please write to me and i will change it or remove it.

# Building with cmake

To build Fillwave you must have [CMake](https://cmake.org/), [GIT](https://git-scm.com/) and C++ compliers installed (So far, Clang and GCC are supported. MSVC version will be available soon). If you are not familiar with CMake I created few scripts to help you with building the project. Note that we use external libraries - each of them in separate git submodule.

```
git clone https://github.com/filipwasil/fillwave.git
cd fillwave
git submodule init
git submodule update
cd scripts
```

## Debian/Ubuntu/Fedora/RedHat

Linux builds requires packages installed:

```
#Ubnuntu 14.04
sudo apt-get install libglew1.10 libglew-dev libglfw3 libglfw3-dev libassimp3 libassimp-dev libfreetype6 libfreetype6-dev libglm-dev libx11-dev libglm-dev
```

```
#Ubnuntu 16.04
sudo apt-get install libglew1.13 libglew-dev libglfw3 libglfw3-dev libassimp3v5 libassimp-dev libfreetype6 libfreetype6-dev libglm-dev libx11-dev libglm-dev libspdlog-dev
```

```
#Fedora
With configured sudo:
sudo dnf install glm-devel assimp assimp-devel glew glew-devel freetype-devel freetype spdlog rpm-build rpmdevtools
Without configured sudo:
su
dnf install glm-devel assimp assimp-devel glew glew-devel freetype-devel freetype spdlog rpm-build rpmdevtools

```


Next, run build script:

```
for ubuntu:
./build_linux_deb.sh
for fedora if you want build and install(you must have configured sudo):
./build_linux_rpm.sh i
for fedora if you want build rpm packges only(RPM packges are in fillwave_build):
./build_linux_rpm.sh ni
```

## Windows

Windows build needs [MinGW](http://www.mingw.org/) installed (If you want to use pthreads then use [mingw64](http://mingw-w64.org/doku.php) version). Soon VS 14 2015 version will be also available.

```
./build_windows_msvs.bat
```

Please also note that if you have sh.exe in your PATH, you should remove it for the compilation time. MinGW projects does not line sh.exe in PATH. Sorry.

## Android

Android script is currently designed to work only with Linux. It assumes that Android [NDK] (http://developer.android.com/ndk/index.html) is under ~/Tools/android-ndk-r10e. If this is not true, update the script with correct path.

```
./build_android.sh

```

## OSX

```
./build_osx.sh
```

## Developers

* Workflow: https://github.com/filipwasil/fillwave/wiki/Workflow
* Coding standards: https://github.com/filipwasil/fillwave/tree/master/doc/coding_standards/ide
* Review: https://review.gerrithub.io/#/admin/projects/filipwasil/fillwave
* Agile: https://zube.io/boards/43120442

## Other repos

* Particle editor: https://github.com/filipwasil/fillwave_editor_particles
* Examples: https://github.com/filipwasil/fillwave-examples
* Example racer game (legacy API): https://github.com/filipwasil/fillwave-waveracer 

|    CI build    |    Result      |
| :-------------: |:-------------:|
| Linux      | ![](https://travis-ci.org/filipwasil/fillwave.svg?branch=master) |
| Android (native)    | ![](https://travis-ci.org/filipwasil/fillwave.svg?branch=master)      |
| Windows (msvs)    | [![Build status](https://ci.appveyor.com/api/projects/status/w5xqq2tntoo9td6k?svg=true)](https://ci.appveyor.com/project/filipwasil/fillwave) |
| Coverity   | [![Coverage Status](https://coveralls.io/repos/github/filipwasil/fillwave/badge.svg?branch=master)](https://coveralls.io/github/filipwasil/fillwave?branch=master)
