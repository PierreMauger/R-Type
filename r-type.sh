#!/bin/sh

if [ ! -d "build" ]; then
    mkdir build
fi
cmake -S . -B build
cmake --build build -j 8
