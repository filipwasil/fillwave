#!/bin/sh
astyle --options=../doc/coding_standards/filllwave.astylerc --suffix=none --recursive "../src/*.cpp" "../inc/*.h*"
