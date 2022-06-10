#!/bin/bash

pwd
mkdir -p project/build/
cd project/build/
cmake ..
cmake --build .