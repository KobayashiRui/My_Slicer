# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kr/git/My_Slicer/Slicer_withQt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kr/git/My_Slicer/Slicer_withQt/build

# Include any dependencies generated for this target.
include CMakeFiles/Slicer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Slicer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Slicer.dir/flags.make

qrc_qml.cpp: ../main.qml
qrc_qml.cpp: ../testvertexcolor.frag
qrc_qml.cpp: ../testvertexcolor.vert
qrc_qml.cpp: qml.qrc.depends
qrc_qml.cpp: ../qml.qrc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating qrc_qml.cpp"
	/home/kr/Qt/5.14.2/gcc_64/bin/rcc --name qml --output /home/kr/git/My_Slicer/Slicer_withQt/build/qrc_qml.cpp /home/kr/git/My_Slicer/Slicer_withQt/qml.qrc

CMakeFiles/Slicer.dir/main.cpp.o: CMakeFiles/Slicer.dir/flags.make
CMakeFiles/Slicer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Slicer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slicer.dir/main.cpp.o -c /home/kr/git/My_Slicer/Slicer_withQt/main.cpp

CMakeFiles/Slicer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slicer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kr/git/My_Slicer/Slicer_withQt/main.cpp > CMakeFiles/Slicer.dir/main.cpp.i

CMakeFiles/Slicer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slicer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kr/git/My_Slicer/Slicer_withQt/main.cpp -o CMakeFiles/Slicer.dir/main.cpp.s

CMakeFiles/Slicer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Slicer.dir/main.cpp.o.requires

CMakeFiles/Slicer.dir/main.cpp.o.provides: CMakeFiles/Slicer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slicer.dir/build.make CMakeFiles/Slicer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Slicer.dir/main.cpp.o.provides

CMakeFiles/Slicer.dir/main.cpp.o.provides.build: CMakeFiles/Slicer.dir/main.cpp.o


CMakeFiles/Slicer.dir/Slicer.cpp.o: CMakeFiles/Slicer.dir/flags.make
CMakeFiles/Slicer.dir/Slicer.cpp.o: ../Slicer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Slicer.dir/Slicer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slicer.dir/Slicer.cpp.o -c /home/kr/git/My_Slicer/Slicer_withQt/Slicer.cpp

CMakeFiles/Slicer.dir/Slicer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slicer.dir/Slicer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kr/git/My_Slicer/Slicer_withQt/Slicer.cpp > CMakeFiles/Slicer.dir/Slicer.cpp.i

CMakeFiles/Slicer.dir/Slicer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slicer.dir/Slicer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kr/git/My_Slicer/Slicer_withQt/Slicer.cpp -o CMakeFiles/Slicer.dir/Slicer.cpp.s

CMakeFiles/Slicer.dir/Slicer.cpp.o.requires:

.PHONY : CMakeFiles/Slicer.dir/Slicer.cpp.o.requires

CMakeFiles/Slicer.dir/Slicer.cpp.o.provides: CMakeFiles/Slicer.dir/Slicer.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slicer.dir/build.make CMakeFiles/Slicer.dir/Slicer.cpp.o.provides.build
.PHONY : CMakeFiles/Slicer.dir/Slicer.cpp.o.provides

CMakeFiles/Slicer.dir/Slicer.cpp.o.provides.build: CMakeFiles/Slicer.dir/Slicer.cpp.o


CMakeFiles/Slicer.dir/Slicing.cpp.o: CMakeFiles/Slicer.dir/flags.make
CMakeFiles/Slicer.dir/Slicing.cpp.o: ../Slicing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Slicer.dir/Slicing.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slicer.dir/Slicing.cpp.o -c /home/kr/git/My_Slicer/Slicer_withQt/Slicing.cpp

CMakeFiles/Slicer.dir/Slicing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slicer.dir/Slicing.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kr/git/My_Slicer/Slicer_withQt/Slicing.cpp > CMakeFiles/Slicer.dir/Slicing.cpp.i

CMakeFiles/Slicer.dir/Slicing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slicer.dir/Slicing.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kr/git/My_Slicer/Slicer_withQt/Slicing.cpp -o CMakeFiles/Slicer.dir/Slicing.cpp.s

CMakeFiles/Slicer.dir/Slicing.cpp.o.requires:

.PHONY : CMakeFiles/Slicer.dir/Slicing.cpp.o.requires

CMakeFiles/Slicer.dir/Slicing.cpp.o.provides: CMakeFiles/Slicer.dir/Slicing.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slicer.dir/build.make CMakeFiles/Slicer.dir/Slicing.cpp.o.provides.build
.PHONY : CMakeFiles/Slicer.dir/Slicing.cpp.o.provides

CMakeFiles/Slicer.dir/Slicing.cpp.o.provides.build: CMakeFiles/Slicer.dir/Slicing.cpp.o


CMakeFiles/Slicer.dir/qrc_qml.cpp.o: CMakeFiles/Slicer.dir/flags.make
CMakeFiles/Slicer.dir/qrc_qml.cpp.o: qrc_qml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Slicer.dir/qrc_qml.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slicer.dir/qrc_qml.cpp.o -c /home/kr/git/My_Slicer/Slicer_withQt/build/qrc_qml.cpp

CMakeFiles/Slicer.dir/qrc_qml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slicer.dir/qrc_qml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kr/git/My_Slicer/Slicer_withQt/build/qrc_qml.cpp > CMakeFiles/Slicer.dir/qrc_qml.cpp.i

CMakeFiles/Slicer.dir/qrc_qml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slicer.dir/qrc_qml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kr/git/My_Slicer/Slicer_withQt/build/qrc_qml.cpp -o CMakeFiles/Slicer.dir/qrc_qml.cpp.s

CMakeFiles/Slicer.dir/qrc_qml.cpp.o.requires:

.PHONY : CMakeFiles/Slicer.dir/qrc_qml.cpp.o.requires

CMakeFiles/Slicer.dir/qrc_qml.cpp.o.provides: CMakeFiles/Slicer.dir/qrc_qml.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slicer.dir/build.make CMakeFiles/Slicer.dir/qrc_qml.cpp.o.provides.build
.PHONY : CMakeFiles/Slicer.dir/qrc_qml.cpp.o.provides

CMakeFiles/Slicer.dir/qrc_qml.cpp.o.provides.build: CMakeFiles/Slicer.dir/qrc_qml.cpp.o


CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o: CMakeFiles/Slicer.dir/flags.make
CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o: Slicer_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o -c /home/kr/git/My_Slicer/Slicer_withQt/build/Slicer_autogen/mocs_compilation.cpp

CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kr/git/My_Slicer/Slicer_withQt/build/Slicer_autogen/mocs_compilation.cpp > CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.i

CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kr/git/My_Slicer/Slicer_withQt/build/Slicer_autogen/mocs_compilation.cpp -o CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.s

CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.requires:

.PHONY : CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.requires

CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.provides: CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slicer.dir/build.make CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.provides.build
.PHONY : CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.provides

CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.provides.build: CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o


# Object files for target Slicer
Slicer_OBJECTS = \
"CMakeFiles/Slicer.dir/main.cpp.o" \
"CMakeFiles/Slicer.dir/Slicer.cpp.o" \
"CMakeFiles/Slicer.dir/Slicing.cpp.o" \
"CMakeFiles/Slicer.dir/qrc_qml.cpp.o" \
"CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o"

# External object files for target Slicer
Slicer_EXTERNAL_OBJECTS =

Slicer: CMakeFiles/Slicer.dir/main.cpp.o
Slicer: CMakeFiles/Slicer.dir/Slicer.cpp.o
Slicer: CMakeFiles/Slicer.dir/Slicing.cpp.o
Slicer: CMakeFiles/Slicer.dir/qrc_qml.cpp.o
Slicer: CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o
Slicer: CMakeFiles/Slicer.dir/build.make
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DAnimation.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DQuickExtras.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DExtras.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DRender.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DInput.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Gamepad.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DLogic.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DQuick.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Quick.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5QmlModels.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Qml.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt53DCore.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Network.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Gui.so.5.14.2
Slicer: /home/kr/Qt/5.14.2/gcc_64/lib/libQt5Core.so.5.14.2
Slicer: CMakeFiles/Slicer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Slicer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Slicer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Slicer.dir/build: Slicer

.PHONY : CMakeFiles/Slicer.dir/build

CMakeFiles/Slicer.dir/requires: CMakeFiles/Slicer.dir/main.cpp.o.requires
CMakeFiles/Slicer.dir/requires: CMakeFiles/Slicer.dir/Slicer.cpp.o.requires
CMakeFiles/Slicer.dir/requires: CMakeFiles/Slicer.dir/Slicing.cpp.o.requires
CMakeFiles/Slicer.dir/requires: CMakeFiles/Slicer.dir/qrc_qml.cpp.o.requires
CMakeFiles/Slicer.dir/requires: CMakeFiles/Slicer.dir/Slicer_autogen/mocs_compilation.cpp.o.requires

.PHONY : CMakeFiles/Slicer.dir/requires

CMakeFiles/Slicer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Slicer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Slicer.dir/clean

CMakeFiles/Slicer.dir/depend: qrc_qml.cpp
	cd /home/kr/git/My_Slicer/Slicer_withQt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kr/git/My_Slicer/Slicer_withQt /home/kr/git/My_Slicer/Slicer_withQt /home/kr/git/My_Slicer/Slicer_withQt/build /home/kr/git/My_Slicer/Slicer_withQt/build /home/kr/git/My_Slicer/Slicer_withQt/build/CMakeFiles/Slicer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Slicer.dir/depend

