#cd ~/
#mkdir Tools
#cd Tools
#wget http://downloads.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz

#export PATH=~/Tools/android-ndk-r10d/bin:$PATH
export PATH=~/Tools/android-ndk-r10d/build/tools:$PATH

cmake ~/Tools/freeglut-3.0.0 -DCMAKE_TOOLCHAIN_FILE=~/Tools/freeglut-3.0.0/android_toolchain.cmake -DCMAKE_INSTALL_PREFIX=~/Tools/android-ndk-r10d-standalone/sysroot/usr -DCMAKE_BUILD_TYPE=Debug -DFREEGLUT_GLES=ON -DFREEGLUT_BUILD_DEMOS=NO -DANDROID_NDK=~/Tools/android-ndk-r10d -DANDROID_NATIVE_API_LEVEL=18


#cmake ~/Tools/freeglut-3.0.0 -DCMAKE_TOOLCHAIN_FILE=/home/filip/Projects/fillwave/cmake/android.toolchain.cmake -DCMAKE_INSTALL_PREFIX=~/Tools/android-ndk-r10d/sysroot/usr -DCMAKE_BUILD_TYPE=Debug -DFREEGLUT_GLES=ON -DFREEGLUT_BUILD_DEMOS=NO -DANDROID_NDK=~/Tools/android-ndk-r10d -DANDROID_NATIVE_API_LEVEL=18



