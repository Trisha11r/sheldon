# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/trisha/SHELDON

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/trisha/SHELDON

# Include any dependencies generated for this target.
include CMakeFiles/sheldon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sheldon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sheldon.dir/flags.make

CMakeFiles/sheldon.dir/sheldon.cpp.o: CMakeFiles/sheldon.dir/flags.make
CMakeFiles/sheldon.dir/sheldon.cpp.o: sheldon.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/trisha/SHELDON/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sheldon.dir/sheldon.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sheldon.dir/sheldon.cpp.o -c /home/trisha/SHELDON/sheldon.cpp

CMakeFiles/sheldon.dir/sheldon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sheldon.dir/sheldon.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/trisha/SHELDON/sheldon.cpp > CMakeFiles/sheldon.dir/sheldon.cpp.i

CMakeFiles/sheldon.dir/sheldon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sheldon.dir/sheldon.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/trisha/SHELDON/sheldon.cpp -o CMakeFiles/sheldon.dir/sheldon.cpp.s

CMakeFiles/sheldon.dir/sheldon.cpp.o.requires:
.PHONY : CMakeFiles/sheldon.dir/sheldon.cpp.o.requires

CMakeFiles/sheldon.dir/sheldon.cpp.o.provides: CMakeFiles/sheldon.dir/sheldon.cpp.o.requires
	$(MAKE) -f CMakeFiles/sheldon.dir/build.make CMakeFiles/sheldon.dir/sheldon.cpp.o.provides.build
.PHONY : CMakeFiles/sheldon.dir/sheldon.cpp.o.provides

CMakeFiles/sheldon.dir/sheldon.cpp.o.provides.build: CMakeFiles/sheldon.dir/sheldon.cpp.o

# Object files for target sheldon
sheldon_OBJECTS = \
"CMakeFiles/sheldon.dir/sheldon.cpp.o"

# External object files for target sheldon
sheldon_EXTERNAL_OBJECTS =

sheldon: CMakeFiles/sheldon.dir/sheldon.cpp.o
sheldon: CMakeFiles/sheldon.dir/build.make
sheldon: /usr/local/lib/libopencv_viz.so.2.4.9
sheldon: /usr/local/lib/libopencv_videostab.so.2.4.9
sheldon: /usr/local/lib/libopencv_video.so.2.4.9
sheldon: /usr/local/lib/libopencv_ts.a
sheldon: /usr/local/lib/libopencv_superres.so.2.4.9
sheldon: /usr/local/lib/libopencv_stitching.so.2.4.9
sheldon: /usr/local/lib/libopencv_photo.so.2.4.9
sheldon: /usr/local/lib/libopencv_ocl.so.2.4.9
sheldon: /usr/local/lib/libopencv_objdetect.so.2.4.9
sheldon: /usr/local/lib/libopencv_nonfree.so.2.4.9
sheldon: /usr/local/lib/libopencv_ml.so.2.4.9
sheldon: /usr/local/lib/libopencv_legacy.so.2.4.9
sheldon: /usr/local/lib/libopencv_imgproc.so.2.4.9
sheldon: /usr/local/lib/libopencv_highgui.so.2.4.9
sheldon: /usr/local/lib/libopencv_gpu.so.2.4.9
sheldon: /usr/local/lib/libopencv_flann.so.2.4.9
sheldon: /usr/local/lib/libopencv_features2d.so.2.4.9
sheldon: /usr/local/lib/libopencv_core.so.2.4.9
sheldon: /usr/local/lib/libopencv_contrib.so.2.4.9
sheldon: /usr/local/lib/libopencv_calib3d.so.2.4.9
sheldon: /usr/lib/i386-linux-gnu/libGLU.so
sheldon: /usr/lib/i386-linux-gnu/libGL.so
sheldon: /usr/lib/i386-linux-gnu/libSM.so
sheldon: /usr/lib/i386-linux-gnu/libICE.so
sheldon: /usr/lib/i386-linux-gnu/libX11.so
sheldon: /usr/lib/i386-linux-gnu/libXext.so
sheldon: /usr/local/lib/libopencv_nonfree.so.2.4.9
sheldon: /usr/local/lib/libopencv_ocl.so.2.4.9
sheldon: /usr/local/lib/libopencv_gpu.so.2.4.9
sheldon: /usr/local/lib/libopencv_photo.so.2.4.9
sheldon: /usr/local/lib/libopencv_objdetect.so.2.4.9
sheldon: /usr/local/lib/libopencv_legacy.so.2.4.9
sheldon: /usr/local/lib/libopencv_video.so.2.4.9
sheldon: /usr/local/lib/libopencv_ml.so.2.4.9
sheldon: /usr/local/lib/libopencv_calib3d.so.2.4.9
sheldon: /usr/local/lib/libopencv_features2d.so.2.4.9
sheldon: /usr/local/lib/libopencv_highgui.so.2.4.9
sheldon: /usr/local/lib/libopencv_imgproc.so.2.4.9
sheldon: /usr/local/lib/libopencv_flann.so.2.4.9
sheldon: /usr/local/lib/libopencv_core.so.2.4.9
sheldon: CMakeFiles/sheldon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sheldon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sheldon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sheldon.dir/build: sheldon
.PHONY : CMakeFiles/sheldon.dir/build

CMakeFiles/sheldon.dir/requires: CMakeFiles/sheldon.dir/sheldon.cpp.o.requires
.PHONY : CMakeFiles/sheldon.dir/requires

CMakeFiles/sheldon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sheldon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sheldon.dir/clean

CMakeFiles/sheldon.dir/depend:
	cd /home/trisha/SHELDON && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON/CMakeFiles/sheldon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sheldon.dir/depend
