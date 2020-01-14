cmake_minimum_required(VERSION 3.1)
project(hello_world CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...


#find_package( Eigen3 REQUIRED PATHS /usr/local/Cellar/eigen/3.3.7/include/eigen3)

include_directories(./stl_read)
include_directories(/usr/local/Cellar/eigen/3.3.7/include/eigen3) 

add_subdirectory(./stl_read)

add_executable(slicer main.cpp)
#target_link_libraries(slicer /Users/rui/Documents/GitHub/My_Slicer/stl_read/build/libstl_read_static.a)
target_link_libraries(slicer stl_read)