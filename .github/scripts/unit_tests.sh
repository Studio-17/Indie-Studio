#!/bin/bash

pwd
mkdir -p project/build/
cd project/build/
cmake -DUNIT_TEST=ON ..
cmake --build .
cd ..
./build/unit_tests