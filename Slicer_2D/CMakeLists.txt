cmake_minimum_required(VERSION 3.1)
project(hello_world CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...



include_directories(./stl_read)
include_directories(./matplotlib)
include_directories(/usr/local/Cellar/python/3.7.4_1/Frameworks/Python.framework/Versions/3.7/include/python3.7m)
include_directories(/usr/local/lib/python3.7/site-packages/numpy/core/include)
include_directories(/usr/local/Cellar/eigen/3.3.7/include/eigen3) 
link_directories(/usr/local/opt/python/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin)
#find_package(Python3 COMPONENTS Development NumPy)
add_subdirectory(./stl_read)

add_executable(slicer main.cpp)
#target_link_libraries(slicer /Users/rui/Documents/GitHub/My_Slicer/stl_read/build/libstl_read_static.a)
target_link_libraries(slicer stl_read)
target_link_libraries(slicer python3.7m)
#target_include_directories(slicer PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
#target_link_libraries(slicer Python3::Python Python2::NumPy)