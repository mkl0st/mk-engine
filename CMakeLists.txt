# CMake Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "mk")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Project Name
project(${PROJECT_NAME})

# CXX Standard
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# MinGW
if(BUILD_FOR_WINDOWS)
  set(CMAKE_SYSTEM_NAME Windows)
  set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
  set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
  set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
  set(CMAKE_MAKE_PROGRAM x86_64-w64-mingw32-make)
endif()

# Compile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Finding Library Include Directories
find_path(GLEW_INCLUDE_DIR NAMES GL/glew.h HINTS "${CMAKE_SOURCE_DIR}/include")
find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h HINTS "${CMAKE_SOURCE_DIR}/include")
set(MK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Validating Library Include Paths
if(NOT GLEW_INCLUDE_DIR)
  message(FATAL_ERROR "GLEW Include Directory not found!")
elseif(NOT GLFW_INCLUDE_DIR)
  message(FATAL_ERROR "GLFW Include Directory not found!")
elseif(NOT GLFW_INCLUDE_DIR)
  message(FATAL_ERROR "MK Include Directory not found!")
endif()

# Library Folder
if(BUILD_FOR_WINDOWS)
  set(LIB_FOLDER "windows")
else()
  set(LIB_FOLDER "linux")
endif()

# Finding Library Binaries
find_library(GLEW_LIB NAMES GLEW HINTS "${CMAKE_SOURCE_DIR}/lib/${LIB_FOLDER}")
find_library(GLFW_LIB NAMES glfw3 HINTS "${CMAKE_SOURCE_DIR}/lib/${LIB_FOLDER}")

# Validating Library Binaries
if(NOT GLEW_LIB)
  message(FATAL_ERROR "GLEW Binary not found!")
elseif(NOT GLFW_INCLUDE_DIR)
  message(GLFW_LIB "GLFW Binary not found!")
endif()

# Include Paths
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${MK_INCLUDE_DIR})

# DLL Files
if(WIN32 OR BUILD_FOR_WINDOWS)
  file(GLOB dll_files ${CMAKE_SOURCE_DIR}/lib/dll/*.dll)
  foreach(dll_file ${dll_files})
    file(COPY ${dll_file} DESTINATION ${CMAKE_SOURCE_DIR}/build/examples)
  endforeach()
endif()

# Resource Files
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_SOURCE_DIR}/build/examples)

# Subdirectories
add_subdirectory(src)
add_subdirectory(examples)
