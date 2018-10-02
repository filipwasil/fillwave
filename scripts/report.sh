#!/usr/bin/env bash
./vera++.sh
./cccc.sh
cd ../doc
rm -rf ./www/*
doxygen Doxyfile
