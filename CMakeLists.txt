cmake_minimum_required(VERSION 3.8)

project(dto_examples_root)

# Set the default C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the Examples directory as a subproject
add_subdirectory(Examples)