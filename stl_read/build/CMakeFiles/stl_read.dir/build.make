# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rui/Documents/GitHub/My_Slicer/stl_read

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rui/Documents/GitHub/My_Slicer/stl_read/build

# Include any dependencies generated for this target.
include CMakeFiles/stl_read.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stl_read.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stl_read.dir/flags.make

CMakeFiles/stl_read.dir/stl_read.cpp.o: CMakeFiles/stl_read.dir/flags.make
CMakeFiles/stl_read.dir/stl_read.cpp.o: ../stl_read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/stl_read/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stl_read.dir/stl_read.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stl_read.dir/stl_read.cpp.o -c /Users/rui/Documents/GitHub/My_Slicer/stl_read/stl_read.cpp

CMakeFiles/stl_read.dir/stl_read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stl_read.dir/stl_read.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rui/Documents/GitHub/My_Slicer/stl_read/stl_read.cpp > CMakeFiles/stl_read.dir/stl_read.cpp.i

CMakeFiles/stl_read.dir/stl_read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stl_read.dir/stl_read.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rui/Documents/GitHub/My_Slicer/stl_read/stl_read.cpp -o CMakeFiles/stl_read.dir/stl_read.cpp.s

# Object files for target stl_read
stl_read_OBJECTS = \
"CMakeFiles/stl_read.dir/stl_read.cpp.o"

# External object files for target stl_read
stl_read_EXTERNAL_OBJECTS =

libstl_read.dylib: CMakeFiles/stl_read.dir/stl_read.cpp.o
libstl_read.dylib: CMakeFiles/stl_read.dir/build.make
libstl_read.dylib: CMakeFiles/stl_read.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/stl_read/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libstl_read.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stl_read.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stl_read.dir/build: libstl_read.dylib

.PHONY : CMakeFiles/stl_read.dir/build

CMakeFiles/stl_read.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stl_read.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stl_read.dir/clean

CMakeFiles/stl_read.dir/depend:
	cd /Users/rui/Documents/GitHub/My_Slicer/stl_read/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rui/Documents/GitHub/My_Slicer/stl_read /Users/rui/Documents/GitHub/My_Slicer/stl_read /Users/rui/Documents/GitHub/My_Slicer/stl_read/build /Users/rui/Documents/GitHub/My_Slicer/stl_read/build /Users/rui/Documents/GitHub/My_Slicer/stl_read/build/CMakeFiles/stl_read.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stl_read.dir/depend

