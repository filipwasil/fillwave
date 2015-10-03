cd ../..
IF exist myDirName ( echo directory exists ) ELSE ( mkdir fillwave_build && echo fillwave_build created)
cd fillwave_build
set PATH%PATH%;C:\MinGW\bin
cmake ../fillwave -G "Eclipse CDT4 - MinGW Makefiles" -DASSIMP_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF
mingw32-make -j4
cpack
set destination=%cd%\..\fillwave\doc\html\downloads\
set source=%cd%\libfillwave-1.9.9-win32.tar.gz
xcopy %source% %destination% /y
pause