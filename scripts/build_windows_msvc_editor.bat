set qtpath=%1
echo %qtpath%
cd ../../
RD /S build_editor /Q
MD build_editor
cd build_editor
cmake ../fillwave -DCMAKE_GENERATOR_PLATFORM=x64 -DFILLWAVE_BUILD_QT_EDITOR=ON -DQTMSVC=%qtpath%
cmake --build examples/editor
xcopy ext\glew\DEBUG\glew64.dll DEBUG\glew64.dll*
xcopy ext\assimp\code\Debug\assimp-vc140-mt.dll DEBUG\assimp-vc140-mt.dll*
xcopy ..\fillwave\examples\editor\assets DEBUG\assets\* /S
xcopy DEBUG\assets\fonts DEBUG\* /S
xcopy ..\fillwave\examples\linux\data\animations DEBUG\animations\* /S
set currentPath=%cd%
cd %qtpath%\bin
windeployqt %currentPath%\Debug\fillwaveEditor.exe
