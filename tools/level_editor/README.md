# Level editor for Fillwave GE (template)
This is application too provide editor of levels for FillWaveEngine.<br />
# Prerequisites

* Linux with > Qt 5.7 

# How to build <br />
**Windows** <br />
Currently not supported

**Linux** <br />

To build on linux you need to have install Qt 5.7 >.
In order to build solution you need use cmake command with parameters like this: <br />

```
-DTESTSTATUS=ON -DFILLWAVE_BUILD_LEVEL_EDITOR=ON -DFILLWAVE_BUILD_GLFW_EXAMPLES=OFF -DFILLWAVE_COMPILATION_UBUNTU1710_WORKAROUNDS=ON
```
<br />
There will be generate binary with program and binary with UT tests.

![QTEditor.png](https://github.com/filipwasil/fillwave_editor_particles/blob/master/screens/QTEditor.png)
