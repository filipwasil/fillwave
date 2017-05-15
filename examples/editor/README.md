# Particle editor for Fillwave GE (template)
This is application who provides various of example for fillwave 3d engine. <br />
# Prerequisites
<ul>
  <li>MSVC 2015 build tools</li>
  <li>QT5.X MSVC 64-bit version. You should add msvc2015_64 folder from QT directory to PATH.</li>
  <li>Visual studio 2015 redistributable packeg</li>
</ul> 
# How to build <br />
**Windows** <br />
To build this application you must go to scripts folder in main fillwave directory. 
to build on linux you must run script: <br />

```
build_windows_msvc_InterActiveDemo.bat PATH_TO_QT
```

You must provide path to QT for example:

```
build_windows_msvc_InterActiveDemo.bat C:/Qt/5.8/msvc2015_64
```
After scripts ends  you should go to build_InteractiveDemo/Debug folder. You should find there 
fillwaveInteractiveDemo.exe. <br />
Occasionally, ucrtbased.dll can be missing, in that case you must find and copy to Debug folder this .dll from Program 
Files (x86)\Windows Kits, 
You must choose correct version for example for windows 10 and x64 path is: <br /> 

```
C:\Program Files (x86)\Windows Kits\10\bin\x64\ucrt
```
<br />
**Linux**

![QTEditor.png](https://github.com/filipwasil/fillwave_editor_particles/blob/master/screens/QTEditor.png)
