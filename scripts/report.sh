./vera++.sh
./valgrind.sh ../../fillwave_build/testApp
./cccc.sh
cd ../doc
rm -rf ./www/doxygen_doc/*
doxygen Doxyfile
