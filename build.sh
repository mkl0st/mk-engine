#!/bin/bash

# Constants
BUILD_DIR="build"

# Title
echo -e "\033[1;32mMK Builder\033[0m"

# Clean Command
if [[ "$*" == *"--clean"* ]]; then
  rm -rf $BUILD_DIR
  echo -e "\033[0;31mCleaned the build folder.\033[0m"
  exit 0
fi

# Windows Flag
if [[ "$*" == *"--windows"* ]]; then
  BUILD_FOR_WINDOWS="ON"
  echo -e "\033[0;34mTarget System: Windows\033[0m"
else
  BUILD_FOR_WINDOWS="OFF"
  echo -e "\033[0;34mTarget System: Linux\033[0m"
fi

# Build Folder Log
echo -e "\033[0;35mBuild Folder:  $BUILD_DIR\033[0m"

# Build Mode
if [[ "$*" == *"--release"* ]]; then
  BUILD_TYPE="Release"
  echo -e "\033[0;33mBuild Type:    Release\033[0m"
else
  BUILD_TYPE="Debug"
  echo -e "\033[0;33mBuild Type:    Debug\033[0m"
fi

# Building the project
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake .. -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBUILD_FOR_WINDOWS=$BUILD_FOR_WINDOWS
make

# Run Command
if [[ "$*" == *"--run"* ]]; then
  cd ..
  if [ -f ./$BUILD_DIR/examples/mk ]; then
    echo
    ./$BUILD_DIR/examples/mk
  elif [ -f ./$BUILD_DIR/examples/mk.exe ]; then
    ./$BUILD_DIR/examples/mk.exe
  fi
fi
