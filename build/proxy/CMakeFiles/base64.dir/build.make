# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lijinqi/workspace/zhuge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lijinqi/workspace/zhuge/build

# Include any dependencies generated for this target.
include proxy/CMakeFiles/base64.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include proxy/CMakeFiles/base64.dir/compiler_depend.make

# Include the progress variables for this target.
include proxy/CMakeFiles/base64.dir/progress.make

# Include the compile flags for this target's objects.
include proxy/CMakeFiles/base64.dir/flags.make

proxy/CMakeFiles/base64.dir/base64.cc.o: proxy/CMakeFiles/base64.dir/flags.make
proxy/CMakeFiles/base64.dir/base64.cc.o: ../proxy/base64.cc
proxy/CMakeFiles/base64.dir/base64.cc.o: proxy/CMakeFiles/base64.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lijinqi/workspace/zhuge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object proxy/CMakeFiles/base64.dir/base64.cc.o"
	cd /home/lijinqi/workspace/zhuge/build/proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT proxy/CMakeFiles/base64.dir/base64.cc.o -MF CMakeFiles/base64.dir/base64.cc.o.d -o CMakeFiles/base64.dir/base64.cc.o -c /home/lijinqi/workspace/zhuge/proxy/base64.cc

proxy/CMakeFiles/base64.dir/base64.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base64.dir/base64.cc.i"
	cd /home/lijinqi/workspace/zhuge/build/proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lijinqi/workspace/zhuge/proxy/base64.cc > CMakeFiles/base64.dir/base64.cc.i

proxy/CMakeFiles/base64.dir/base64.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base64.dir/base64.cc.s"
	cd /home/lijinqi/workspace/zhuge/build/proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lijinqi/workspace/zhuge/proxy/base64.cc -o CMakeFiles/base64.dir/base64.cc.s

# Object files for target base64
base64_OBJECTS = \
"CMakeFiles/base64.dir/base64.cc.o"

# External object files for target base64
base64_EXTERNAL_OBJECTS =

proxy/base64: proxy/CMakeFiles/base64.dir/base64.cc.o
proxy/base64: proxy/CMakeFiles/base64.dir/build.make
proxy/base64: proxy/CMakeFiles/base64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lijinqi/workspace/zhuge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable base64"
	cd /home/lijinqi/workspace/zhuge/build/proxy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base64.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proxy/CMakeFiles/base64.dir/build: proxy/base64
.PHONY : proxy/CMakeFiles/base64.dir/build

proxy/CMakeFiles/base64.dir/clean:
	cd /home/lijinqi/workspace/zhuge/build/proxy && $(CMAKE_COMMAND) -P CMakeFiles/base64.dir/cmake_clean.cmake
.PHONY : proxy/CMakeFiles/base64.dir/clean

proxy/CMakeFiles/base64.dir/depend:
	cd /home/lijinqi/workspace/zhuge/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lijinqi/workspace/zhuge /home/lijinqi/workspace/zhuge/proxy /home/lijinqi/workspace/zhuge/build /home/lijinqi/workspace/zhuge/build/proxy /home/lijinqi/workspace/zhuge/build/proxy/CMakeFiles/base64.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proxy/CMakeFiles/base64.dir/depend

