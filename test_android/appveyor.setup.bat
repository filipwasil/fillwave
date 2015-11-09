powershell -Command "(New-Object Net.WebClient).DownloadFile('http://downloads.sourceforge.net/project/mingw-w64/mingw-w64/mingw-w64-release/mingw-w64-v4.0.4.tar.bz2?r=&ts=1447082361&use_mirror=skylink', 'mingw64.tar.bz2')"
tar xjvf mingw64.tar.bz2 -C %mypath:~0,-1%\mingw64
SET mypath=%~dp0
echo %mypath:~0,-1%
setx PATH "%PATH%;%mypath:~0,-1%\mingw64\bin"
IF exist fillwave_windows_build ( echo directory exists ) ELSE ( mkdir fillwave_windows_build && echo fillwave_windows_build created)
cd fillwave_windows_build
cmake ../fillwave -G "Eclipse CDT4 - MinGW Makefiles" -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF
mingw32-make -j4
pause