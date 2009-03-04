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

CMakeFiles/pann.dir/Object.cpp.o: CMakeFiles/pann.dir/flags.make
CMakeFiles/pann.dir/Object.cpp.o: src/Object.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/booble/pann/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building CXX object CMakeFiles/pann.dir/Object.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pann.dir/Object.cpp.o -c src/Object.cpp

CMakeFiles/pann.dir/Object.cpp.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/pann.dir/Object.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E src/Object.cpp > CMakeFiles/pann.dir/Object.cpp.i

CMakeFiles/pann.dir/Object.cpp.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/pann.dir/Object.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S src/Object.cpp -o CMakeFiles/pann.dir/Object.cpp.s

CMakeFiles/pann.dir/Object.cpp.o.requires:
.PHONY : CMakeFiles/pann.dir/Object.cpp.o.requires

CMakeFiles/pann.dir/Object.cpp.o.provides: CMakeFiles/pann.dir/Object.cpp.o.requires
	$(MAKE) -f CMakeFiles/pann.dir/build.make CMakeFiles/pann.dir/Object.cpp.o.provides.build
.PHONY : CMakeFiles/pann.dir/Object.cpp.o.provides

CMakeFiles/pann.dir/Object.cpp.o.provides.build: CMakeFiles/pann.dir/Object.cpp.o
.PHONY : CMakeFiles/pann.dir/Object.cpp.o.provides.build

CMakeFiles/pann.dir/Neuron.cpp.o: CMakeFiles/pann.dir/flags.make
CMakeFiles/pann.dir/Neuron.cpp.o: src/Neuron.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/booble/pann/trunk/CMakeFiles $(CMAKE_PROGRESS_2)
	@echo "Building CXX object CMakeFiles/pann.dir/Neuron.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pann.dir/Neuron.cpp.o -c src/Neuron.cpp

CMakeFiles/pann.dir/Neuron.cpp.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/pann.dir/Neuron.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E src/Neuron.cpp > CMakeFiles/pann.dir/Neuron.cpp.i

CMakeFiles/pann.dir/Neuron.cpp.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/pann.dir/Neuron.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S src/Neuron.cpp -o CMakeFiles/pann.dir/Neuron.cpp.s

CMakeFiles/pann.dir/Neuron.cpp.o.requires:
.PHONY : CMakeFiles/pann.dir/Neuron.cpp.o.requires

CMakeFiles/pann.dir/Neuron.cpp.o.provides: CMakeFiles/pann.dir/Neuron.cpp.o.requires
	$(MAKE) -f CMakeFiles/pann.dir/build.make CMakeFiles/pann.dir/Neuron.cpp.o.provides.build
.PHONY : CMakeFiles/pann.dir/Neuron.cpp.o.provides

CMakeFiles/pann.dir/Neuron.cpp.o.provides.build: CMakeFiles/pann.dir/Neuron.cpp.o
.PHONY : CMakeFiles/pann.dir/Neuron.cpp.o.provides.build

# Object files for target pann
pann_OBJECTS = \
"CMakeFiles/pann.dir/Object.cpp.o" \
"CMakeFiles/pann.dir/Neuron.cpp.o"

# External object files for target pann
pann_EXTERNAL_OBJECTS =

bin/libpann.a: CMakeFiles/pann.dir/Object.cpp.o
bin/libpann.a: CMakeFiles/pann.dir/Neuron.cpp.o
bin/libpann.a: CMakeFiles/pann.dir/build.make
bin/libpann.a: CMakeFiles/pann.dir/link.txt
	@echo "Linking CXX static library bin/libpann.a"
	$(CMAKE_COMMAND) -P CMakeFiles/pann.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pann.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pann.dir/build: bin/libpann.a
.PHONY : CMakeFiles/pann.dir/build

CMakeFiles/pann.dir/requires: CMakeFiles/pann.dir/Object.cpp.o.requires
CMakeFiles/pann.dir/requires: CMakeFiles/pann.dir/Neuron.cpp.o.requires
.PHONY : CMakeFiles/pann.dir/requires

CMakeFiles/pann.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pann.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pann.dir/clean

CMakeFiles/pann.dir/depend:
	cd /home/booble/pann/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/booble/pann/trunk/src /home/booble/pann/trunk/src /home/booble/pann/trunk /home/booble/pann/trunk /home/booble/pann/trunk/CMakeFiles/pann.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pann.dir/depend

