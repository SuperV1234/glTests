#!/bin/bash
clang++ -o $1 -std=c++11 -lglfw -O3 "./$1.cpp" && ./$1