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
#Ubnuntu
sudo apt-get install libglew1.10 libglew-dev libglfw3 libglfw3-dev libassimp3 libassimp-dev libfreetype6 libfreetype6-dev libglm-dev libx11-dev libglm-dev
```

```
#Fedora
sudo yum install glm-devel.x86_64 glm.x86_64 assimp.x86_64 assimp-devel.x86_64 glew.x86_64 glew-devel.x86_64 freetype-devel.x86_64 freetype.x86_64
```


Next, run build script:

```
./build_linux.sh
```

## Windows

Windows build needs [MinGW](http://www.mingw.org/) installed (If you want to use pthreads then use [mingw64](http://mingw-w64.org/doku.php) version). Soon VS 14 2015 version will be also available.

```
./build_windows_mingw.bat # ./build_windows_msvc will work soon
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
| Windows (mingw)    | Needs C++14 support |
| Coverity   | [![Coverage Status](https://coveralls.io/repos/github/filipwasil/fillwave/badge.svg?branch=master)](https://coveralls.io/github/filipwasil/fillwave?branch=master)