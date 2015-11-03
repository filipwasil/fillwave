# Fillwave graphics engine

[Fillwave]: http://filipwasil.bitbucket.org/

[![Join the chat at https://gitter.im/filipwasil/fillwave](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/filipwasil/fillwave?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

![](https://travis-ci.org/filipwasil/fillwave.svg?branch=master)

[![wercker status](https://app.wercker.com/status/176e362189e969142c07469b492ef216/m "wercker status")](https://app.wercker.com/project/bykey/176e362189e969142c07469b492ef216)

[Fillwave] is a modern, native and totally free rendering engine writen in c++11 .

Can be used in any 3D games, apps and visualization tools or as a regular part of your game engine.

- Multiplatform (Linux, Windows, Android, OSX)
- Native Android apps (JNI, or C++).
- Using the greatest open source libraries (Ex. glm for math and assimp for assets)
- OpenGL ES 3.0 and OpenGL 3.3+ support with programmable pipeline
- Engine can be fully open source and free under BSD license

This wiki uses the [Markdown](http://daringfireball.net/projects/markdown/) syntax.

# Building with cmake

```
git clone https://github.com/filipwasil/fillwave.git
cd fillwave
git submodule init
git submodule update
cd scripts
```

## Debian/Ubuntu/Fedora/RedHat

```
./build_linux.sh
```

## Windows

```
./build_windows.bat
```

## Android

Script assumes that android NDK is under ~/Tools/android-ndk-r10e

```
./build_android.sh

```

## OSX

```
./build_osx.sh
```
