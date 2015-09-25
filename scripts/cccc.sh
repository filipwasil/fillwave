#!/bin/sh
rm -rf ../doc/cccc/*
cccc --outdir=../doc/cccc --lang=c++ ../src/*/*.cpp ../src/*.cpp ../src/Fillwave.cpp ../inc/fillwave/*/*.h ../inc/fillwave/*.h
