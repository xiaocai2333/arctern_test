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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build

# Include any dependencies generated for this target.
include CMakeFiles/example3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example3.dir/flags.make

CMakeFiles/example3.dir/examples/example3.c.o: CMakeFiles/example3.dir/flags.make
CMakeFiles/example3.dir/examples/example3.c.o: /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/examples/example3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/example3.dir/examples/example3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/example3.dir/examples/example3.c.o   -c /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/examples/example3.c

CMakeFiles/example3.dir/examples/example3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/example3.dir/examples/example3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/examples/example3.c > CMakeFiles/example3.dir/examples/example3.c.i

CMakeFiles/example3.dir/examples/example3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/example3.dir/examples/example3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/examples/example3.c -o CMakeFiles/example3.dir/examples/example3.c.s

# Object files for target example3
example3_OBJECTS = \
"CMakeFiles/example3.dir/examples/example3.c.o"

# External object files for target example3
example3_EXTERNAL_OBJECTS =

/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3: CMakeFiles/example3.dir/examples/example3.c.o
/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3: CMakeFiles/example3.dir/build.make
/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3: libminiz.so.2.1.0
/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3: CMakeFiles/example3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example3.dir/build: /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep/bin/example3

.PHONY : CMakeFiles/example3.dir/build

CMakeFiles/example3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example3.dir/clean

CMakeFiles/example3.dir/depend:
	cd /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build /home/liangliu/workspace/arctern/cpp/cmake_build/miniz_ep-prefix/src/miniz_ep-build/CMakeFiles/example3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example3.dir/depend

