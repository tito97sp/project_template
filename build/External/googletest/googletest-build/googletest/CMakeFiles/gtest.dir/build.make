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
CMAKE_SOURCE_DIR = /home/andressanchez/Escritorio/GIT/project_template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andressanchez/Escritorio/GIT/project_template/build

# Include any dependencies generated for this target.
include External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/flags.make

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/flags.make
External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: External/googletest/googletest-src/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andressanchez/Escritorio/GIT/project_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && /usr/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.obj -c /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-src/googletest/src/gtest-all.cc

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-src/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && /usr/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-src/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.requires:

.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.requires

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.provides: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.requires
	$(MAKE) -f External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/build.make External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.provides.build
.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.provides

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.provides.build: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.obj"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

lib/libgtest.a: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj
lib/libgtest.a: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/build.make
lib/libgtest.a: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andressanchez/Escritorio/GIT/project_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../lib/libgtest.a"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/build: lib/libgtest.a

.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/build

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/requires: External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj.requires

.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/requires

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/clean:
	cd /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/clean

External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/depend:
	cd /home/andressanchez/Escritorio/GIT/project_template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andressanchez/Escritorio/GIT/project_template /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-src/googletest /home/andressanchez/Escritorio/GIT/project_template/build /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest /home/andressanchez/Escritorio/GIT/project_template/build/External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : External/googletest/googletest-build/googletest/CMakeFiles/gtest.dir/depend

