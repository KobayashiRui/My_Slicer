cmake_minimum_required (VERSION 3.10)
project(stl_read CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...
add_library(stl_read SHARED stl_read.cpp)
add_library(stl_read_static STATIC stl_read.cpp)