@echo off

if not exist build (
    mkdir build
)
cmake -S . -B build
cmake --build build -j 8
