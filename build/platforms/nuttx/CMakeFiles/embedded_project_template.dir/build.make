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
include platforms/nuttx/CMakeFiles/embedded_project_template.dir/depend.make

# Include the progress variables for this target.
include platforms/nuttx/CMakeFiles/embedded_project_template.dir/progress.make

# Include the compile flags for this target's objects.
include platforms/nuttx/CMakeFiles/embedded_project_template.dir/flags.make

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj: platforms/nuttx/CMakeFiles/embedded_project_template.dir/flags.make
platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj: ../platforms/common/src/platform_common/empty.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andressanchez/Escritorio/GIT/project_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj   -c /home/andressanchez/Escritorio/GIT/project_template/platforms/common/src/platform_common/empty.c

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.i"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andressanchez/Escritorio/GIT/project_template/platforms/common/src/platform_common/empty.c > CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.i

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.s"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx && /usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andressanchez/Escritorio/GIT/project_template/platforms/common/src/platform_common/empty.c -o CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.s

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.requires:

.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.requires

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.provides: platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.requires
	$(MAKE) -f platforms/nuttx/CMakeFiles/embedded_project_template.dir/build.make platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.provides.build
.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.provides

platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.provides.build: platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj


# Object files for target embedded_project_template
embedded_project_template_OBJECTS = \
"CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj"

# External object files for target embedded_project_template
embedded_project_template_EXTERNAL_OBJECTS =

platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj
platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/nuttx/CMakeFiles/embedded_project_template.dir/build.make
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/apps/libapps.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/arch/arm/src/libarch.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/binfmt/libbinfmt.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/libs/libc/libc.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/boards/libboards.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/libs/libxx/libxx.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/drivers/libdrivers.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/fs/libfs.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/mm/libmm.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/sched/libsched.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/modules/hello/libhello.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/modules/uORB/libuORB.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/modules/template_module/libtemplate_module.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: boards/stm/nucleo_h743zi/src/libdrivers_board.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/arch/arm/src/libarch.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: boards/stm/nucleo_h743zi/src/libdrivers_board.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/modules/uORB/libuORB.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/common/src/platform_common/libplatform_common.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/modules/uORB/libuORB.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/common/src/platform_common/libplatform_common.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/nuttx/src/os/libos_layer.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/apps/libapps.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: src/lib/cdev/libcdev.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/libs/libxx/libxx.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/libs/libc/libc.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/drivers/libdrivers.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/fs/libfs.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/mm/libmm.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: NuttX/nuttx/sched/libsched.a
platforms/nuttx/stm_nucleo-h743zi_default.elf: platforms/nuttx/CMakeFiles/embedded_project_template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andressanchez/Escritorio/GIT/project_template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stm_nucleo-h743zi_default.elf"
	cd /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/embedded_project_template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
platforms/nuttx/CMakeFiles/embedded_project_template.dir/build: platforms/nuttx/stm_nucleo-h743zi_default.elf

.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/build

platforms/nuttx/CMakeFiles/embedded_project_template.dir/requires: platforms/nuttx/CMakeFiles/embedded_project_template.dir/__/common/src/platform_common/empty.c.obj.requires

.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/requires

platforms/nuttx/CMakeFiles/embedded_project_template.dir/clean:
	cd /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx && $(CMAKE_COMMAND) -P CMakeFiles/embedded_project_template.dir/cmake_clean.cmake
.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/clean

platforms/nuttx/CMakeFiles/embedded_project_template.dir/depend:
	cd /home/andressanchez/Escritorio/GIT/project_template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andressanchez/Escritorio/GIT/project_template /home/andressanchez/Escritorio/GIT/project_template/platforms/nuttx /home/andressanchez/Escritorio/GIT/project_template/build /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx /home/andressanchez/Escritorio/GIT/project_template/build/platforms/nuttx/CMakeFiles/embedded_project_template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : platforms/nuttx/CMakeFiles/embedded_project_template.dir/depend

