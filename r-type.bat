@echo off

if not exist build (
    mkdir build
)
cd build
cmake ..
cd ..
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j 8