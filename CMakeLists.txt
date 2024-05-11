# CMake Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "mk")

# Project Name
project(${PROJECT_NAME})

# CXX Standard
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Subdirectories
add_subdirectory(examples)
