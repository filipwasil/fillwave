set qtpath=%1
echo %qtpath%
cd ../../
RD /S build_editor /Q
MD build_editor
cd build_editor
cmake ../fillwave -DCMAKE_GENERATOR_PLATFORM=x64 -DFILLWAVE_BUILD_QT_EDITOR=ON -DQTMSVC=%qtpath%
cmake --build examples/editor
xcopy ext\glew\DEBUG\glew64d.dll DEBUG\glew64d.dll*
xcopy ext\assimp\code\Debug\assimp-vc140-mtd.dll DEBUG\assimp-vc140-mtd.dll*
xcopy ..\fillwave\examples\data\assets\fonts DEBUG\* /S
xcopy ..\fillwave\examples\data\* DEBUG\* /S
set currentPath=%cd%
cd %qtpath%\bin
windeployqt %currentPath%\Debug\fillwaveEditor.exe