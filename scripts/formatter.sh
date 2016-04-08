#!/bin/sh
astyle --options=../doc/coding_standards/filllwave.astylerc --recursive "../src/*.cpp" "../inc/*.h*"
