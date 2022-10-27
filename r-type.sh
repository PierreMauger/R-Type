#!/bin/sh

if [ ! -d "build" ]; then
    mkdir build
fi
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build