#!/bin/bash

# Constants
BUILD_DIR="build"

# Windows Flag
if [[ "$*" == *"--windows"* ]]; then
  BUILD_FOR_WINDOWS="ON"
else
  BUILD_FOR_WINDOWS="OFF"
fi

# Build Mode
if [[ "$*" == *"--release"* ]]; then
  BUILD_TYPE="Release"
else
  BUILD_TYPE="Debug"
fi

# Building the project
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBUILD_FOR_WINDOWS=$BUILD_FOR_WINDOWS
make
