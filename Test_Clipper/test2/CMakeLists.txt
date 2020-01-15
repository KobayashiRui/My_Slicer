cmake_minimum_required(VERSION 3.6)
project(test1 CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...


include_directories(/usr/local/include)

link_directories(/usr/local/lib)

add_executable(test1 main.cpp)
target_link_libraries(test1 polyclipping)/