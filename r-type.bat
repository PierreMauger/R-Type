@echo off

if not exist build (
    mkdir build
)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 8