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
CMAKE_SOURCE_DIR = /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build

# Include any dependencies generated for this target.
include CMakeFiles/offset_path.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/offset_path.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/offset_path.dir/flags.make

CMakeFiles/offset_path.dir/main.cpp.o: CMakeFiles/offset_path.dir/flags.make
CMakeFiles/offset_path.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/offset_path.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/offset_path.dir/main.cpp.o -c /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/main.cpp

CMakeFiles/offset_path.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/offset_path.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/main.cpp > CMakeFiles/offset_path.dir/main.cpp.i

CMakeFiles/offset_path.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/offset_path.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/main.cpp -o CMakeFiles/offset_path.dir/main.cpp.s

# Object files for target offset_path
offset_path_OBJECTS = \
"CMakeFiles/offset_path.dir/main.cpp.o"

# External object files for target offset_path
offset_path_EXTERNAL_OBJECTS =

offset_path: CMakeFiles/offset_path.dir/main.cpp.o
offset_path: CMakeFiles/offset_path.dir/build.make
offset_path: CMakeFiles/offset_path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable offset_path"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/offset_path.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/offset_path.dir/build: offset_path

.PHONY : CMakeFiles/offset_path.dir/build

CMakeFiles/offset_path.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/offset_path.dir/cmake_clean.cmake
.PHONY : CMakeFiles/offset_path.dir/clean

CMakeFiles/offset_path.dir/depend:
	cd /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build /Users/rui/Documents/GitHub/My_Slicer/Test_Clipper/OffsetPath/build/CMakeFiles/offset_path.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/offset_path.dir/depend

