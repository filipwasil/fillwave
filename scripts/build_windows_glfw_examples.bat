cd ../../
RD /S build_win_glfw_examples /Q
MD build_win_glfw_examples
cd build_win_glfw_examples
cmake ../fillwave -DCMAKE_GENERATOR_PLATFORM=x64 -DFILLWAVE_BUILD_GLFW_EXAMPLES=ON
cmake --build .
xcopy ext\glew\DEBUG\glew64d.dll DEBUG\glew64d.dll*
xcopy ext\assimp\code\Debug\assimp-vc140-mtd.dll DEBUG\assimp-vc140-mtd.dll*
xcopy ..\fillwave\examples\data\* DEBUG\* /S

