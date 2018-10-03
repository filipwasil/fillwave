# Fillwave graphics engine

[Fillwave]: https://filipwasil.bitbucket.io/

[![GitHub release](https://img.shields.io/github/release/filipwasil/fillwave.svg)](https://github.com/filipwasil/fillwave/releases/latest) [![Join the chat at https://gitter.im/filipwasil/fillwave](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/filipwasil/fillwave?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[Fillwave] is a modern, native and totally free rendering engine writen in c++14.

Can be used in any 3D games, apps and visualization tools or as a regular part of your game engine.

- Multiplatform (Linux, Windows)
- MIT License
- Using the greatest open source libraries (Ex. glm for math and assimp for assets)
- OpenGL ES 3.0 and OpenGL 3.3+ support with programmable pipeline

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
```

## Linux builds

```
# Ubuntu 16.04
sudo apt-get install libglfw3-dev libassimp3v5 libassimp-dev libglm-dev cmake

# Optional for GLES support
sudo apt-get install libgles2-mesa-dev

# Fedora
With configured sudo:
sudo dnf install glm-devel assimp-devel glfw3-devel
Without configured sudo:
su
dnf install glm-devel assimp assimp-devel libglfw3-dev
```

## Cmake options

|    Cmake options  |     Default      |
| :-------------|:-------------:|
| FILLWAVE_TESTS                          | ON |
| FILLWAVE_MODEL_LOADER_ASSIMP            | ON |
| FILLWAVE_COMPILATION_DRIVER_WORKAROUNDS | ON |
| FILLWAVE_BACKEND_OPENGL_45              | ON |
| FILLWAVE_COMPILATION_SUPPRESS_WARNINGS  | OFF |
| FILLWAVE_COMPILATION_RELEASE            | OFF |
| FILLWAVE_BACKEND_OPENGL_ES_20           | OFF |
| FILLWAVE_BACKEND_OPENGL_ES_30           | OFF |
| FILLWAVE_TEXTURE_LOADER_CUSTOM          | OFF |
| FILLWAVE_BUILD_GLFW_EXAMPLES            | OFF |
| FILLWAVE_BUILD_LEVEL_EDITOR             | OFF |
| FILLWAVE_BUILD_COTIRE                   | OFF |
| FILLWAVE_BENCHMARK_TESTS                | OFF |
| FILLWAVE_DEBUG_OPENGL_APITRACE          | OFF |


## CI

|    OS    |    Result      |
| :-------------: |:-------------:|
| Linux      | ![](https://travis-ci.org/filipwasil/fillwave.svg?branch=master) |
| Windows (msvs)    | [![Build status](https://ci.appveyor.com/api/projects/status/w5xqq2tntoo9td6k?svg=true)](https://ci.appveyor.com/project/filipwasil/fillwave) |

# Special thanks to
<img src="https://github.com/filipwasil/fillwave/blob/dev_master/ext/support/clion.png" width="32" height="32"> <img src="https://github.com/filipwasil/fillwave/blob/dev_master/ext/support/zube.png" width="32" height="32"> <img src="https://github.com/filipwasil/fillwave/blob/dev_master/ext/support/travis.png" width="32" height="32"> <img src="https://github.com/filipwasil/fillwave/blob/dev_master/ext/support/appveyor.png" width="32" height="32"> <img src="https://github.com/filipwasil/fillwave/blob/dev_master/ext/support/gerrit.png" width="32" height="32">