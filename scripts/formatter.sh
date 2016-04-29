#!/bin/sh
astyle --options=../doc/coding_standards/filllwave.astylerc --suffix=none --recursive "../src/*.cpp" "../inc/*.h*" "../examples/linux/inc/*.h" "../examples/linux/src/*.cpp" "../examples/qt/*.cpp" "../examples/qt/*.h*"
