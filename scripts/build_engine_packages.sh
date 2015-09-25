#!/bin/sh

if [ $1 -eq 0 ]; then
  echo jesli nie ma argumentow nie powinien sie wykonac
fi

# Prepare build directories
# ../../fillwave_build
# ../../fillwave-examples_build

sudo apt-get remove libfillwave* -y
sudo apt-get remove fillwave-examples -y

rm -rf ../../fillwave_build/*
rm -rf ../../fillwave-examples_build/*
if [ $? -eq 0 ]; then
    echo build directory cleared
else
    mkdir ../../fillwave_build
fi
rm -rf ../../fillwave_build/*

rm -rf ../../fillwave-examples_build/*
if [ $? -eq 0 ]; then
    echo examples build directory cleared
else
    mkdir ../../fillwave-examples_build
fi

# Enter library build directory
# rm -rf ../ext/glew/*
# rm -rf ../ext/assimp/*
# rm -rf ../ext/glm/*
# rm -rf ../ext/glfw/*

cd ../../fillwave_build

# Build library DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=OFF -DBUILD_DEB=ON -DBUILD_LIB=ON -DBUILD_DEV=OFF -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
sudo dpkg -i ./libfillwave-$1.$2.$3-Linux.deb

# Build dev DEB
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=OFF -DBUILD_DEB=ON -DBUILD_LIB=OFF -DBUILD_DEV=ON -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack
sudo dpkg -i ./libfillwave-dev-$1.$2.$3-Linux.deb

# Build library RPM
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=ON -DBUILD_DEB=OFF -DBUILD_LIB=ON -DBUILD_DEV=OFF -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Build dev RPM
cmake ../fillwave -G"Eclipse CDT4 - Unix Makefiles" -DNDEBUG=OFF -DBUILD_PACK=ON -DBUILD_RPM=ON -DBUILD_DEB=OFF -DBUILD_LIB=OFF -DBUILD_DEV=ON -DVERSION_MAJOR=$1 -DVERSION_MINOR=$2 -DVERSION_PATCH=$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack

# Enter example build directory
cd ../fillwave-examples_build

# Build and copy examples DEB
cmake ../fillwave-examples -G"Eclipse CDT4 - Unix Makefiles" -DPROJECT_VERSION=$1.$2.$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack -G DEB 
cp ./fillwave-examples-$1.$2.$3-Linux.deb ../fillwave_build/fillwave-examples-$1.$2.$3-Linux.deb
sudo dpkg -i ./fillwave-examples-$1.$2.$3-Linux.deb

# Build and copy examples RPM
cmake ../fillwave-examples -G"Eclipse CDT4 - Unix Makefiles" -DPROJECT_VERSION=$1.$2.$3 -D_ECLIPSE_VERSION="4.4" && make -j4 && cpack -G RPM 
cp ./fillwave-examples-$1.$2.$3-Linux.rpm ../fillwave_build/fillwave-examples-$1.$2.$3-Linux.rpm

# pack and copy examples
cd ../fillwave-examples
zip -r9 fillwave-examples-$1.$2.$3-Linux.zip cmake data inc src CMakeLists.txt Copyrights_assets.txt
mv ./fillwave-examples-$1.$2.$3-Linux.zip ../fillwave_build/fillwave-examples-$1.$2.$3-Linux.zip

# Enter library build directory
cd ../fillwave_build

# Clear temporary cpack archives
rm -rf ./_CPack_Packages/*

# Build DEBIAN remote repository configuration
dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz

# Build RED HAT remote repository configuration
createrepo .

# Remove old packages
rm ../fillwave/doc/html/downloads/libfillwave-$1.$2.$(($3-1))-Linux.deb
rm ../fillwave/doc/html/downloads/libfillwave-dev-$1.$2.$(($3-1))-Linux.deb
rm ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$(($3-1))-Linux.deb
rm ../fillwave/doc/html/downloads/libfillwave-$1.$2.$(($3-1))-Linux.rpm
rm ../fillwave/doc/html/downloads/libfillwave-dev-$1.$2.$(($3-1))-Linux.rpm
rm ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$(($3-1))-Linux.rpm
rm ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$(($3-1))-Linux.zip
rm ../fillwave/doc/html/downloads/Packages.gz
rm -r ../fillwave/doc/html/downloads/repodata

cp libfillwave-$1.$2.$3-Linux.deb ../fillwave/doc/html/downloads/libfillwave-$1.$2.$3-Linux.deb
cp libfillwave-dev-$1.$2.$3-Linux.deb ../fillwave/doc/html/downloads/libfillwave-dev-$1.$2.$3-Linux.deb
cp fillwave-examples-$1.$2.$3-Linux.deb ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$3-Linux.deb
cp libfillwave-$1.$2.$3-Linux.rpm ../fillwave/doc/html/downloads/libfillwave-$1.$2.$3-Linux.rpm
cp libfillwave-dev-$1.$2.$3-Linux.rpm ../fillwave/doc/html/downloads/libfillwave-dev-$1.$2.$3-Linux.rpm
cp fillwave-examples-$1.$2.$3-Linux.rpm ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$3-Linux.rpm
cp fillwave-examples-$1.$2.$3-Linux.zip ../fillwave/doc/html/downloads/fillwave-examples-$1.$2.$3-Linux.zip
cp Packages.gz ../fillwave/doc/html/downloads/Packages.gz
cp -r repodata ../fillwave/doc/html/downloads/repodata
cp ../fillwave/scripts/installer_ubuntu.sh ../fillwave/doc/html/downloads/installer_ubuntu.sh
cp ../fillwave/doc/quickstart/quickstart.pdf ../fillwave/doc/html/downloads/Fillwave.pdf

