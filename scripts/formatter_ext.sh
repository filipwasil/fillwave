#!/bin/sh
astyle --options=../doc/coding_standards/filllwave.astylerc --suffix=none --recursive "../../fillwave-examples/*.cpp" "../../fillwave-examples/*.h"
