# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/slinky/Project3/playground

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/slinky/Project3/playground/cmake-build-debug

# Include any dependencies generated for this target.
include libWad/CMakeFiles/Wad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include libWad/CMakeFiles/Wad.dir/compiler_depend.make

# Include the progress variables for this target.
include libWad/CMakeFiles/Wad.dir/progress.make

# Include the compile flags for this target's objects.
include libWad/CMakeFiles/Wad.dir/flags.make

libWad/CMakeFiles/Wad.dir/Wad.cpp.o: libWad/CMakeFiles/Wad.dir/flags.make
libWad/CMakeFiles/Wad.dir/Wad.cpp.o: /Users/slinky/Project3/libWad/Wad.cpp
libWad/CMakeFiles/Wad.dir/Wad.cpp.o: libWad/CMakeFiles/Wad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/slinky/Project3/playground/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libWad/CMakeFiles/Wad.dir/Wad.cpp.o"
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT libWad/CMakeFiles/Wad.dir/Wad.cpp.o -MF CMakeFiles/Wad.dir/Wad.cpp.o.d -o CMakeFiles/Wad.dir/Wad.cpp.o -c /Users/slinky/Project3/libWad/Wad.cpp

libWad/CMakeFiles/Wad.dir/Wad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Wad.dir/Wad.cpp.i"
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/slinky/Project3/libWad/Wad.cpp > CMakeFiles/Wad.dir/Wad.cpp.i

libWad/CMakeFiles/Wad.dir/Wad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Wad.dir/Wad.cpp.s"
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/slinky/Project3/libWad/Wad.cpp -o CMakeFiles/Wad.dir/Wad.cpp.s

# Object files for target Wad
Wad_OBJECTS = \
"CMakeFiles/Wad.dir/Wad.cpp.o"

# External object files for target Wad
Wad_EXTERNAL_OBJECTS =

libWad/libWad.a: libWad/CMakeFiles/Wad.dir/Wad.cpp.o
libWad/libWad.a: libWad/CMakeFiles/Wad.dir/build.make
libWad/libWad.a: libWad/CMakeFiles/Wad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/slinky/Project3/playground/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libWad.a"
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && $(CMAKE_COMMAND) -P CMakeFiles/Wad.dir/cmake_clean_target.cmake
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Wad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libWad/CMakeFiles/Wad.dir/build: libWad/libWad.a
.PHONY : libWad/CMakeFiles/Wad.dir/build

libWad/CMakeFiles/Wad.dir/clean:
	cd /Users/slinky/Project3/playground/cmake-build-debug/libWad && $(CMAKE_COMMAND) -P CMakeFiles/Wad.dir/cmake_clean.cmake
.PHONY : libWad/CMakeFiles/Wad.dir/clean

libWad/CMakeFiles/Wad.dir/depend:
	cd /Users/slinky/Project3/playground/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/slinky/Project3/playground /Users/slinky/Project3/libWad /Users/slinky/Project3/playground/cmake-build-debug /Users/slinky/Project3/playground/cmake-build-debug/libWad /Users/slinky/Project3/playground/cmake-build-debug/libWad/CMakeFiles/Wad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libWad/CMakeFiles/Wad.dir/depend

