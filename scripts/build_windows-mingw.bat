cd ../..
IF exist fillwave_windows_build ( echo directory exists ) ELSE ( mkdir fillwave_windows_build && echo fillwave_windows_build created)
cd fillwave_windows_build
set path=%path:C:/mingw64/bin;=%
cmake ../fillwave -G "Eclipse CDT4 - MinGW Makefiles" -DASSIMP_BUILD_TESTS=OFF -DGLFW_BUILD_TESTS=OFF -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF
mingw32-make -j4
cpack
pause
