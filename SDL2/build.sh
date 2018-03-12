#!/bin/bash
clang++ -I /home/yangkang/Library/glew-2.1.0/include -l GL -l GLU -l SDL2 /home/yangkang/Library/glew-2.1.0/lib/libGLEW.a ./Source/main.cpp -o ./Build/app -std=c++11
./Build/app