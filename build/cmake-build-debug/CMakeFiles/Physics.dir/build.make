# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/clion-2017.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aapogodin/CLionProjects/Physics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aapogodin/CLionProjects/Physics/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Physics.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Physics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Physics.dir/flags.make

CMakeFiles/Physics.dir/main.cpp.o: CMakeFiles/Physics.dir/flags.make
CMakeFiles/Physics.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aapogodin/CLionProjects/Physics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Physics.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Physics.dir/main.cpp.o -c /home/aapogodin/CLionProjects/Physics/main.cpp

CMakeFiles/Physics.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Physics.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aapogodin/CLionProjects/Physics/main.cpp > CMakeFiles/Physics.dir/main.cpp.i

CMakeFiles/Physics.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Physics.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aapogodin/CLionProjects/Physics/main.cpp -o CMakeFiles/Physics.dir/main.cpp.s

CMakeFiles/Physics.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Physics.dir/main.cpp.o.requires

CMakeFiles/Physics.dir/main.cpp.o.provides: CMakeFiles/Physics.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Physics.dir/build.make CMakeFiles/Physics.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Physics.dir/main.cpp.o.provides

CMakeFiles/Physics.dir/main.cpp.o.provides.build: CMakeFiles/Physics.dir/main.cpp.o


CMakeFiles/Physics.dir/vectors.cpp.o: CMakeFiles/Physics.dir/flags.make
CMakeFiles/Physics.dir/vectors.cpp.o: ../vectors.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aapogodin/CLionProjects/Physics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Physics.dir/vectors.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Physics.dir/vectors.cpp.o -c /home/aapogodin/CLionProjects/Physics/vectors.cpp

CMakeFiles/Physics.dir/vectors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Physics.dir/vectors.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aapogodin/CLionProjects/Physics/vectors.cpp > CMakeFiles/Physics.dir/vectors.cpp.i

CMakeFiles/Physics.dir/vectors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Physics.dir/vectors.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aapogodin/CLionProjects/Physics/vectors.cpp -o CMakeFiles/Physics.dir/vectors.cpp.s

CMakeFiles/Physics.dir/vectors.cpp.o.requires:

.PHONY : CMakeFiles/Physics.dir/vectors.cpp.o.requires

CMakeFiles/Physics.dir/vectors.cpp.o.provides: CMakeFiles/Physics.dir/vectors.cpp.o.requires
	$(MAKE) -f CMakeFiles/Physics.dir/build.make CMakeFiles/Physics.dir/vectors.cpp.o.provides.build
.PHONY : CMakeFiles/Physics.dir/vectors.cpp.o.provides

CMakeFiles/Physics.dir/vectors.cpp.o.provides.build: CMakeFiles/Physics.dir/vectors.cpp.o


CMakeFiles/Physics.dir/kinematics.cpp.o: CMakeFiles/Physics.dir/flags.make
CMakeFiles/Physics.dir/kinematics.cpp.o: ../kinematics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aapogodin/CLionProjects/Physics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Physics.dir/kinematics.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Physics.dir/kinematics.cpp.o -c /home/aapogodin/CLionProjects/Physics/kinematics.cpp

CMakeFiles/Physics.dir/kinematics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Physics.dir/kinematics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aapogodin/CLionProjects/Physics/kinematics.cpp > CMakeFiles/Physics.dir/kinematics.cpp.i

CMakeFiles/Physics.dir/kinematics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Physics.dir/kinematics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aapogodin/CLionProjects/Physics/kinematics.cpp -o CMakeFiles/Physics.dir/kinematics.cpp.s

CMakeFiles/Physics.dir/kinematics.cpp.o.requires:

.PHONY : CMakeFiles/Physics.dir/kinematics.cpp.o.requires

CMakeFiles/Physics.dir/kinematics.cpp.o.provides: CMakeFiles/Physics.dir/kinematics.cpp.o.requires
	$(MAKE) -f CMakeFiles/Physics.dir/build.make CMakeFiles/Physics.dir/kinematics.cpp.o.provides.build
.PHONY : CMakeFiles/Physics.dir/kinematics.cpp.o.provides

CMakeFiles/Physics.dir/kinematics.cpp.o.provides.build: CMakeFiles/Physics.dir/kinematics.cpp.o


# Object files for target Physics
Physics_OBJECTS = \
"CMakeFiles/Physics.dir/main.cpp.o" \
"CMakeFiles/Physics.dir/vectors.cpp.o" \
"CMakeFiles/Physics.dir/kinematics.cpp.o"

# External object files for target Physics
Physics_EXTERNAL_OBJECTS =

Physics: CMakeFiles/Physics.dir/main.cpp.o
Physics: CMakeFiles/Physics.dir/vectors.cpp.o
Physics: CMakeFiles/Physics.dir/kinematics.cpp.o
Physics: CMakeFiles/Physics.dir/build.make
Physics: CMakeFiles/Physics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aapogodin/CLionProjects/Physics/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Physics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Physics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Physics.dir/build: Physics

.PHONY : CMakeFiles/Physics.dir/build

CMakeFiles/Physics.dir/requires: CMakeFiles/Physics.dir/main.cpp.o.requires
CMakeFiles/Physics.dir/requires: CMakeFiles/Physics.dir/vectors.cpp.o.requires
CMakeFiles/Physics.dir/requires: CMakeFiles/Physics.dir/kinematics.cpp.o.requires

.PHONY : CMakeFiles/Physics.dir/requires

CMakeFiles/Physics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Physics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Physics.dir/clean

CMakeFiles/Physics.dir/depend:
	cd /home/aapogodin/CLionProjects/Physics/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aapogodin/CLionProjects/Physics /home/aapogodin/CLionProjects/Physics /home/aapogodin/CLionProjects/Physics/cmake-build-debug /home/aapogodin/CLionProjects/Physics/cmake-build-debug /home/aapogodin/CLionProjects/Physics/cmake-build-debug/CMakeFiles/Physics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Physics.dir/depend

