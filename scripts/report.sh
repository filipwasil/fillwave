#!/usr/bin/env bash
./vera++.sh
./valgrind.sh ../../fillwave_build/testApp
./cccc.sh
cd ../doc
rm -rf ./www/*
doxygen Doxyfile
