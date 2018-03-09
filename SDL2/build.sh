#!/bin/bash
clang++ ./Source/main.cpp -o ./Build/app -l SDL2 -std=c++11
./Build/app