#!/bin/bash

# Constants
BUILD_DIR="build"

# Building the project
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake ..
make
