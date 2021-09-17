#!/bin/sh
rm -rf cmake-build-debug && mkdir cmake-build-debug && cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . 
sudo cmake --build . --target install