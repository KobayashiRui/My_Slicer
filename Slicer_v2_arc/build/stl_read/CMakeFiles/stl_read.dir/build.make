# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build

# Include any dependencies generated for this target.
include stl_read/CMakeFiles/stl_read.dir/depend.make

# Include the progress variables for this target.
include stl_read/CMakeFiles/stl_read.dir/progress.make

# Include the compile flags for this target's objects.
include stl_read/CMakeFiles/stl_read.dir/flags.make

stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.o: stl_read/CMakeFiles/stl_read.dir/flags.make
stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.o: ../stl_read/stl_read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.o"
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stl_read.dir/stl_read.cpp.o -c /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/stl_read/stl_read.cpp

stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stl_read.dir/stl_read.cpp.i"
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/stl_read/stl_read.cpp > CMakeFiles/stl_read.dir/stl_read.cpp.i

stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stl_read.dir/stl_read.cpp.s"
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/stl_read/stl_read.cpp -o CMakeFiles/stl_read.dir/stl_read.cpp.s

# Object files for target stl_read
stl_read_OBJECTS = \
"CMakeFiles/stl_read.dir/stl_read.cpp.o"

# External object files for target stl_read
stl_read_EXTERNAL_OBJECTS =

stl_read/libstl_read.dylib: stl_read/CMakeFiles/stl_read.dir/stl_read.cpp.o
stl_read/libstl_read.dylib: stl_read/CMakeFiles/stl_read.dir/build.make
stl_read/libstl_read.dylib: stl_read/CMakeFiles/stl_read.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libstl_read.dylib"
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stl_read.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stl_read/CMakeFiles/stl_read.dir/build: stl_read/libstl_read.dylib

.PHONY : stl_read/CMakeFiles/stl_read.dir/build

stl_read/CMakeFiles/stl_read.dir/clean:
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read && $(CMAKE_COMMAND) -P CMakeFiles/stl_read.dir/cmake_clean.cmake
.PHONY : stl_read/CMakeFiles/stl_read.dir/clean

stl_read/CMakeFiles/stl_read.dir/depend:
	cd /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/stl_read /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read /Users/rui/Documents/GitHub/My_Slicer/Slicer_v2_arc/build/stl_read/CMakeFiles/stl_read.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stl_read/CMakeFiles/stl_read.dir/depend

