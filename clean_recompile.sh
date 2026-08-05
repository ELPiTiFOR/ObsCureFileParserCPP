#!/bin/sh

rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
cp ../OCFP.config .
exit 0
