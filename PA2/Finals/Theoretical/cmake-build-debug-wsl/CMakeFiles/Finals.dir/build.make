# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl

# Include any dependencies generated for this target.
include CMakeFiles/Finals.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Finals.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Finals.dir/flags.make

CMakeFiles/Finals.dir/main.cpp.o: CMakeFiles/Finals.dir/flags.make
CMakeFiles/Finals.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Finals.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Finals.dir/main.cpp.o -c /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/main.cpp

CMakeFiles/Finals.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Finals.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/main.cpp > CMakeFiles/Finals.dir/main.cpp.i

CMakeFiles/Finals.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Finals.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/main.cpp -o CMakeFiles/Finals.dir/main.cpp.s

# Object files for target Finals
Finals_OBJECTS = \
"CMakeFiles/Finals.dir/main.cpp.o"

# External object files for target Finals
Finals_EXTERNAL_OBJECTS =

Finals: CMakeFiles/Finals.dir/main.cpp.o
Finals: CMakeFiles/Finals.dir/build.make
Finals: CMakeFiles/Finals.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Finals"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Finals.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Finals.dir/build: Finals

.PHONY : CMakeFiles/Finals.dir/build

CMakeFiles/Finals.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Finals.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Finals.dir/clean

CMakeFiles/Finals.dir/depend:
	cd /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl /mnt/c/Users/filou/Desktop/School/CVUT_FIT/2nd_Semester/PA2/Finals/Theoretical/cmake-build-debug-wsl/CMakeFiles/Finals.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Finals.dir/depend

