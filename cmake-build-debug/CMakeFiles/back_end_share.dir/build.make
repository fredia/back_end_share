# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/fredia/CLion-2018.3.4/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/fredia/CLion-2018.3.4/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fredia/CLionProjects/back-end-share

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fredia/CLionProjects/back-end-share/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/back_end_share.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/back_end_share.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/back_end_share.dir/flags.make

CMakeFiles/back_end_share.dir/src/main/main.cpp.o: CMakeFiles/back_end_share.dir/flags.make
CMakeFiles/back_end_share.dir/src/main/main.cpp.o: ../src/main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fredia/CLionProjects/back-end-share/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/back_end_share.dir/src/main/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/back_end_share.dir/src/main/main.cpp.o -c /home/fredia/CLionProjects/back-end-share/src/main/main.cpp

CMakeFiles/back_end_share.dir/src/main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/back_end_share.dir/src/main/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fredia/CLionProjects/back-end-share/src/main/main.cpp > CMakeFiles/back_end_share.dir/src/main/main.cpp.i

CMakeFiles/back_end_share.dir/src/main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/back_end_share.dir/src/main/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fredia/CLionProjects/back-end-share/src/main/main.cpp -o CMakeFiles/back_end_share.dir/src/main/main.cpp.s

# Object files for target back_end_share
back_end_share_OBJECTS = \
"CMakeFiles/back_end_share.dir/src/main/main.cpp.o"

# External object files for target back_end_share
back_end_share_EXTERNAL_OBJECTS =

back_end_share: CMakeFiles/back_end_share.dir/src/main/main.cpp.o
back_end_share: CMakeFiles/back_end_share.dir/build.make
back_end_share: CMakeFiles/back_end_share.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fredia/CLionProjects/back-end-share/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable back_end_share"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/back_end_share.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/back_end_share.dir/build: back_end_share

.PHONY : CMakeFiles/back_end_share.dir/build

CMakeFiles/back_end_share.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/back_end_share.dir/cmake_clean.cmake
.PHONY : CMakeFiles/back_end_share.dir/clean

CMakeFiles/back_end_share.dir/depend:
	cd /home/fredia/CLionProjects/back-end-share/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fredia/CLionProjects/back-end-share /home/fredia/CLionProjects/back-end-share /home/fredia/CLionProjects/back-end-share/cmake-build-debug /home/fredia/CLionProjects/back-end-share/cmake-build-debug /home/fredia/CLionProjects/back-end-share/cmake-build-debug/CMakeFiles/back_end_share.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/back_end_share.dir/depend

