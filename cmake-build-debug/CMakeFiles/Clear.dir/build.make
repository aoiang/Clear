# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aoiang/CS/Clear

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aoiang/CS/Clear/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Clear.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Clear.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Clear.dir/flags.make

CMakeFiles/Clear.dir/bin/Clear.cpp.o: CMakeFiles/Clear.dir/flags.make
CMakeFiles/Clear.dir/bin/Clear.cpp.o: ../bin/Clear.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aoiang/CS/Clear/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Clear.dir/bin/Clear.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Clear.dir/bin/Clear.cpp.o -c /Users/aoiang/CS/Clear/bin/Clear.cpp

CMakeFiles/Clear.dir/bin/Clear.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Clear.dir/bin/Clear.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aoiang/CS/Clear/bin/Clear.cpp > CMakeFiles/Clear.dir/bin/Clear.cpp.i

CMakeFiles/Clear.dir/bin/Clear.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Clear.dir/bin/Clear.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aoiang/CS/Clear/bin/Clear.cpp -o CMakeFiles/Clear.dir/bin/Clear.cpp.s

CMakeFiles/Clear.dir/bin/Clear.cpp.o.requires:

.PHONY : CMakeFiles/Clear.dir/bin/Clear.cpp.o.requires

CMakeFiles/Clear.dir/bin/Clear.cpp.o.provides: CMakeFiles/Clear.dir/bin/Clear.cpp.o.requires
	$(MAKE) -f CMakeFiles/Clear.dir/build.make CMakeFiles/Clear.dir/bin/Clear.cpp.o.provides.build
.PHONY : CMakeFiles/Clear.dir/bin/Clear.cpp.o.provides

CMakeFiles/Clear.dir/bin/Clear.cpp.o.provides.build: CMakeFiles/Clear.dir/bin/Clear.cpp.o


# Object files for target Clear
Clear_OBJECTS = \
"CMakeFiles/Clear.dir/bin/Clear.cpp.o"

# External object files for target Clear
Clear_EXTERNAL_OBJECTS =

Clear: CMakeFiles/Clear.dir/bin/Clear.cpp.o
Clear: CMakeFiles/Clear.dir/build.make
Clear: /usr/local/lib/libsfml-graphics.dylib
Clear: /usr/local/lib/libsfml-window.dylib
Clear: /usr/local/lib/libsfml-system.dylib
Clear: /usr/local/lib/libsfml-audio.dylib
Clear: /usr/local/lib/libsfml-network.dylib
Clear: libClear_core.a
Clear: /usr/local/lib/libsfml-graphics.dylib
Clear: /usr/local/lib/libsfml-window.dylib
Clear: /usr/local/lib/libsfml-system.dylib
Clear: /usr/local/lib/libsfml-audio.dylib
Clear: /usr/local/lib/libsfml-network.dylib
Clear: CMakeFiles/Clear.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aoiang/CS/Clear/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Clear"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Clear.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Clear.dir/build: Clear

.PHONY : CMakeFiles/Clear.dir/build

CMakeFiles/Clear.dir/requires: CMakeFiles/Clear.dir/bin/Clear.cpp.o.requires

.PHONY : CMakeFiles/Clear.dir/requires

CMakeFiles/Clear.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Clear.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Clear.dir/clean

CMakeFiles/Clear.dir/depend:
	cd /Users/aoiang/CS/Clear/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aoiang/CS/Clear /Users/aoiang/CS/Clear /Users/aoiang/CS/Clear/cmake-build-debug /Users/aoiang/CS/Clear/cmake-build-debug /Users/aoiang/CS/Clear/cmake-build-debug/CMakeFiles/Clear.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Clear.dir/depend

