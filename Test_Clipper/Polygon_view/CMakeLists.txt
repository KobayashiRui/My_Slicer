cmake_minimum_required(VERSION 3.6)
project(offset_path CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...


find_package(OpenGL REQUIRED)
include_directories(/usr/local/include)
include_directories(${OPENGL_INCLUDE_DIR})


link_directories(/usr/local/lib)

add_executable(offset_path main.cpp)
target_link_libraries(offset_path polyclipping)
target_link_libraries(offset_path glfw)
target_link_libraries(offset_path ${OPENGL_LIBRARIES} )
