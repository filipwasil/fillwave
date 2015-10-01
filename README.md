# Fillwave graphics engine

[Fillwave]: http://filipwasil.bitbucket.org/


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
mkdir ../fillwave_build && cd ../fillwave_build
```

## Debian/Ubuntu

```
sudo apt-get install libglm-dev libglew1.10 libglew-dev libassimp3 libassimp-dev libfreetype6 xorg-dev 

cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=OFF -DBUILD_DEB=ON -DBUILD_LIB=OFF -DBUILD_DEV=ON -DVERSION_MAJOR=2 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
```

## Fedora/RedHat

```
sudo yum install glm-devel.x86_64 glm.x86_64 assimp.x86_64 assimp-devel.x86_64 glew.x86_64 glew-devel.x86_64 freetype-devel.x86_64 freetype.x86_64

cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=ON -DBUILD_DEB=OFF -DBUILD_LIB=ON -DBUILD_DEV=OFF -DVERSION_MAJOR=2 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

```

## Windows

```
set PATH%PATH%;C:\MinGW\bin
cmake ../fillwave -G "Eclipse CDT4 - MinGW Makefiles" -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF
mingw32-make -j4

```

## Android

API > 18 support (openGLES 3.0) needed and android NDK path specified (Ex. ~/Tools/android-ndk-r10e)

```
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_LIB=ON -DBUILD_DEV=ON -DVERSION_MAJOR=2 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -D_ECLIPSE_VERSION="4.4" -DCMAKE_TOOLCHAIN_FILE=../fillwave/cmake/android.toolchain.cmake -DANDROID_NDK=~/Tools/android-ndk-r10e -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=18 && make -j4 && cpack

```

Wiki pages are normal files, with the .md extension. You can edit them locally, as well as creating new ones.

## QT framework
to be continued ...

## OSX
```
# if homebrew is not there
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

# if other stuff is not there
brew install cmake gcc g++ glew glm freetype

# if omp.h is missing build gcc compiler wihout multilib support
brew reinstall gcc --without-multilib

# we are fine now. go.

cmake ../fillwave -G"Xcode" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_LIB=ON -DBUILD_DEV=ON -DVERSION_MAJOR=1 -DVERSION_MINOR=0 -DVERSION_PATCH=0 -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF && cpack

```

## iOS
to be continued ...

## WebGL
to be continued ...
