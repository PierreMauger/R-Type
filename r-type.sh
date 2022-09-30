#!/bin/sh

if ! command -v cmake &> /dev/null
then
    echo "Couldn't find Cmake"
    exit
fi

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake ..
cd ..
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 8