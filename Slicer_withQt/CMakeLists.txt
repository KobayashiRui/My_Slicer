#find_package(OpenGL REQUIRED)
#include_directories(/usr/local/include)
#include_directories(${OPENGL_INCLUDE_DIR})
#include_directories(./stl_read)
#include_directories(/usr/local/Cellar/eigen/3.3.7/include/eigen3) 
#link_directories(/usr/local/lib)
#add_subdirectory(./stl_read)

#add_executable(Slicer main.cpp)
#target_link_libraries(Slicer stl_read)
#target_link_libraries(Slicer polyclipping)
#target_link_libraries(Slicer glfw)
#target_link_libraries(Slicer ${OPENGL_LIBRARIES} )

cmake_minimum_required(VERSION 3.5)

project(Slicer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14) # C++14...

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_OSX_DEPLOYMENT_TARGET 10.7)
#SET(CMAKE_CXX_FLAGS "-O2 -std=c++03 -stdlib=libc++ -Wall -mmacosx-version-min=10.7")

SET(Qt5_DIR /usr/local/Cellar/qt/5.14.2/)
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})


#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)

find_package(Qt5 REQUIRED Core Qml Quick Gui 3DCore 3DExtras 3DRender 3DInput 3DInput 3DLogic 3DAnimation 3DQuickExtras)
QT5_ADD_RESOURCES(RESOURCES ./qml.qrc)

include_directories(/usr/local/include)
include_directories(/usr/local/Cellar/eigen/3.3.7/include/eigen3) 
link_directories(/usr/local/lib)



add_executable(Slicer main.cpp Slicer.cpp Slicing.cpp ${RESOURCES})
target_link_libraries(Slicer Qt5::Core Qt5::Qml Qt5::Quick Qt5::3DCore Qt5::3DRender Qt5::3DInput Qt5::3DLogic Qt5::3DExtras Qt5::3DAnimation Qt5::3DQuickExtras)
target_link_libraries(Slicer polyclipping)