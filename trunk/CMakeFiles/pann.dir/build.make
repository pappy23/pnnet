# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/booble/pann/trunk/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/booble/pann/trunk

# Include any dependencies generated for this target.
include CMakeFiles/pann.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pann.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pann.dir/flags.make

CMakeFiles/pann.dir/lib.cpp.o: CMakeFiles/pann.dir/flags.make
CMakeFiles/pann.dir/lib.cpp.o: src/lib.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/booble/pann/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building CXX object CMakeFiles/pann.dir/lib.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pann.dir/lib.cpp.o -c src/lib.cpp

CMakeFiles/pann.dir/lib.cpp.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/pann.dir/lib.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E src/lib.cpp > CMakeFiles/pann.dir/lib.cpp.i

CMakeFiles/pann.dir/lib.cpp.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/pann.dir/lib.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S src/lib.cpp -o CMakeFiles/pann.dir/lib.cpp.s

CMakeFiles/pann.dir/lib.cpp.o.requires:
.PHONY : CMakeFiles/pann.dir/lib.cpp.o.requires

CMakeFiles/pann.dir/lib.cpp.o.provides: CMakeFiles/pann.dir/lib.cpp.o.requires
	$(MAKE) -f CMakeFiles/pann.dir/build.make CMakeFiles/pann.dir/lib.cpp.o.provides.build
.PHONY : CMakeFiles/pann.dir/lib.cpp.o.provides

CMakeFiles/pann.dir/lib.cpp.o.provides.build: CMakeFiles/pann.dir/lib.cpp.o
.PHONY : CMakeFiles/pann.dir/lib.cpp.o.provides.build

# Object files for target pann
pann_OBJECTS = \
"CMakeFiles/pann.dir/lib.cpp.o"

# External object files for target pann
pann_EXTERNAL_OBJECTS =

bin/libpann.so: CMakeFiles/pann.dir/lib.cpp.o
bin/libpann.so: CMakeFiles/pann.dir/build.make
bin/libpann.so: CMakeFiles/pann.dir/link.txt
	@echo "Linking CXX shared library bin/libpann.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pann.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pann.dir/build: bin/libpann.so
.PHONY : CMakeFiles/pann.dir/build

CMakeFiles/pann.dir/requires: CMakeFiles/pann.dir/lib.cpp.o.requires
.PHONY : CMakeFiles/pann.dir/requires

CMakeFiles/pann.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pann.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pann.dir/clean

CMakeFiles/pann.dir/depend:
	cd /home/booble/pann/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/booble/pann/trunk/src /home/booble/pann/trunk/src /home/booble/pann/trunk /home/booble/pann/trunk /home/booble/pann/trunk/CMakeFiles/pann.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pann.dir/depend

