cmake_minimum_required(VERSION 3.1)
project(Slicer CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...



find_package(OpenGL REQUIRED)
include_directories(/usr/local/include)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(./stl_read)
include_directories(/usr/local/Cellar/eigen/3.3.7/include/eigen3) 
link_directories(/usr/local/lib)
#find_package(Python3 COMPONENTS Development NumPy)
add_subdirectory(./stl_read)

add_executable(Slicer main.cpp)
#target_link_libraries(slicer /Users/rui/Documents/GitHub/My_Slicer/stl_read/build/libstl_read_static.a)
target_link_libraries(Slicer stl_read)
target_link_libraries(Slicer glfw)
target_link_libraries(Slicer ${OPENGL_LIBRARIES} )

#target_include_directories(slicer PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
#target_link_libraries(slicer Python3::Python Python2::NumPy)