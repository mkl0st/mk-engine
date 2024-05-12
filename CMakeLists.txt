# CMake Version
cmake_minimum_required(VERSION 3.5)

# Constants
set(PROJECT_NAME "mk")

# Project Name
project(${PROJECT_NAME})

# CXX Standard
set(CMAKE_CXX_STANDARD_REQUIRED 17)

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

# Finding Library Binaries
find_library(GLEW_LIB NAMES GLEW HINTS "${CMAKE_SOURCE_DIR}/lib/linux")
find_library(GLFW_LIB NAMES glfw3 HINTS "${CMAKE_SOURCE_DIR}/lib/linux")

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

# Linking Libraries
link_libraries(GL)
link_libraries(${GLEW_LIB})
link_libraries(${GLFW_LIB})

# Subdirectories
add_subdirectory(src)
add_subdirectory(examples)
