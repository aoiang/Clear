# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aoiang/CS/pong

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aoiang/CS/pong/cmake

# Include any dependencies generated for this target.
include CMakeFiles/helloworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helloworld.dir/flags.make

CMakeFiles/helloworld.dir/bin/helloworld.cpp.o: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/bin/helloworld.cpp.o: ../bin/helloworld.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aoiang/CS/pong/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/helloworld.dir/bin/helloworld.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloworld.dir/bin/helloworld.cpp.o -c /Users/aoiang/CS/pong/bin/helloworld.cpp

CMakeFiles/helloworld.dir/bin/helloworld.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/bin/helloworld.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aoiang/CS/pong/bin/helloworld.cpp > CMakeFiles/helloworld.dir/bin/helloworld.cpp.i

CMakeFiles/helloworld.dir/bin/helloworld.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/bin/helloworld.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aoiang/CS/pong/bin/helloworld.cpp -o CMakeFiles/helloworld.dir/bin/helloworld.cpp.s

CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.requires:

.PHONY : CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.requires

CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.provides: CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.requires
	$(MAKE) -f CMakeFiles/helloworld.dir/build.make CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.provides.build
.PHONY : CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.provides

CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.provides.build: CMakeFiles/helloworld.dir/bin/helloworld.cpp.o


CMakeFiles/helloworld.dir/bin/Pong.cpp.o: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/bin/Pong.cpp.o: ../bin/Pong.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aoiang/CS/pong/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/helloworld.dir/bin/Pong.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloworld.dir/bin/Pong.cpp.o -c /Users/aoiang/CS/pong/bin/Pong.cpp

CMakeFiles/helloworld.dir/bin/Pong.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/bin/Pong.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aoiang/CS/pong/bin/Pong.cpp > CMakeFiles/helloworld.dir/bin/Pong.cpp.i

CMakeFiles/helloworld.dir/bin/Pong.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/bin/Pong.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aoiang/CS/pong/bin/Pong.cpp -o CMakeFiles/helloworld.dir/bin/Pong.cpp.s

CMakeFiles/helloworld.dir/bin/Pong.cpp.o.requires:

.PHONY : CMakeFiles/helloworld.dir/bin/Pong.cpp.o.requires

CMakeFiles/helloworld.dir/bin/Pong.cpp.o.provides: CMakeFiles/helloworld.dir/bin/Pong.cpp.o.requires
	$(MAKE) -f CMakeFiles/helloworld.dir/build.make CMakeFiles/helloworld.dir/bin/Pong.cpp.o.provides.build
.PHONY : CMakeFiles/helloworld.dir/bin/Pong.cpp.o.provides

CMakeFiles/helloworld.dir/bin/Pong.cpp.o.provides.build: CMakeFiles/helloworld.dir/bin/Pong.cpp.o


# Object files for target helloworld
helloworld_OBJECTS = \
"CMakeFiles/helloworld.dir/bin/helloworld.cpp.o" \
"CMakeFiles/helloworld.dir/bin/Pong.cpp.o"

# External object files for target helloworld
helloworld_EXTERNAL_OBJECTS =

helloworld: CMakeFiles/helloworld.dir/bin/helloworld.cpp.o
helloworld: CMakeFiles/helloworld.dir/bin/Pong.cpp.o
helloworld: CMakeFiles/helloworld.dir/build.make
helloworld: /usr/local/lib/libsfml-graphics.dylib
helloworld: /usr/local/lib/libsfml-window.dylib
helloworld: /usr/local/lib/libsfml-system.dylib
helloworld: /usr/local/lib/libsfml-audio.dylib
helloworld: /usr/local/lib/libsfml-network.dylib
helloworld: CMakeFiles/helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aoiang/CS/pong/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable helloworld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helloworld.dir/build: helloworld

.PHONY : CMakeFiles/helloworld.dir/build

CMakeFiles/helloworld.dir/requires: CMakeFiles/helloworld.dir/bin/helloworld.cpp.o.requires
CMakeFiles/helloworld.dir/requires: CMakeFiles/helloworld.dir/bin/Pong.cpp.o.requires

.PHONY : CMakeFiles/helloworld.dir/requires

CMakeFiles/helloworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/helloworld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/helloworld.dir/clean

CMakeFiles/helloworld.dir/depend:
	cd /Users/aoiang/CS/pong/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aoiang/CS/pong /Users/aoiang/CS/pong /Users/aoiang/CS/pong/cmake /Users/aoiang/CS/pong/cmake /Users/aoiang/CS/pong/cmake/CMakeFiles/helloworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helloworld.dir/depend

