# Particle editor for Fillwave GE (template)
This is application who provides various of example for fillwave 3d engine. <br />
# Prerequisites

* MSVC 2015 build tools
* QT5.X MSVC 64-bit version. You should add msvc2015_64 folder from QT directory to PATH.
* Visual studio 2015 redistributable packeg

# How to build <br />
**Windows** <br />
To build this application you must go to scripts folder in main fillwave directory. 
to build on linux you must run script: <br />

```
build_windows_msvc_editor.bat PATH_TO_QT
```

You must provide path to QT for example:

```
build_windows_msvc_editor.bat C:/Qt/5.8/msvc2015_64
```
After scripts ends  you should go to build_editor/Debug folder. You should find there 
fillwaveEditor.exe. <br />
Occasionally, ucrtbased.dll can be missing, in that case you must find and copy to Debug folder this .dll from Program 
Files (x86)\Windows Kits, 
You must choose correct version for example for windows 10 and x64 path is: <br /> 

```
C:\Program Files (x86)\Windows Kits\10\bin\x64\ucrt
```

**Linux** <br />

To build on linux you need to have install Qt 5.5 >.
There are two ways to build editor manually or by script. <br />
The easiest way is to use  script who generate RPM or DEB packeg, of course binary with application is built to.
To use scripts go to scripts folder and run: <br />
To build on debian/ubuntu
```
./build_linux_editor_deb.sh
```
To build on RPM based distributions
```
./build_linux_editor_rpm.sh
```
In folder outside main fillwave folder, there will be genereted packeg and binary.

If you want to build only binary and unit tests for application you must compile files manually.<br />
For example we want build application in bin folder outside main fillwave folder, additionally we want to build binary
 with unit tests. <br />
 ```
 #we are in fillwave main folder
 cd ..
 mkdir bin
 cd bin
 cmake ../fillwave -DFILLWAVE_BUILD_QT_EDITOR=ON -DTESTSTATUS=ON
 cmake --build examples/editor -- -j9 #you can change numbers of jobs
 ```
After building is end we can run application or UT.
 ```
 #We are in bin folder
 #To run application
 ./fillwaveEditor
 #To run UT
 cd examples/editor/tests/test/
 ./runUnitTestsEditor
 ```

![QTEditor.png](https://github.com/filipwasil/fillwave_editor_particles/blob/master/screens/QTEditor.png)
