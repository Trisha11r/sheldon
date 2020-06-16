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
include CMakeFiles/camera.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camera.dir/flags.make

CMakeFiles/camera.dir/camera.cpp.o: CMakeFiles/camera.dir/flags.make
CMakeFiles/camera.dir/camera.cpp.o: camera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/trisha/SHELDON/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/camera.dir/camera.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/camera.dir/camera.cpp.o -c /home/trisha/SHELDON/camera.cpp

CMakeFiles/camera.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/camera.dir/camera.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/trisha/SHELDON/camera.cpp > CMakeFiles/camera.dir/camera.cpp.i

CMakeFiles/camera.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/camera.dir/camera.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/trisha/SHELDON/camera.cpp -o CMakeFiles/camera.dir/camera.cpp.s

CMakeFiles/camera.dir/camera.cpp.o.requires:
.PHONY : CMakeFiles/camera.dir/camera.cpp.o.requires

CMakeFiles/camera.dir/camera.cpp.o.provides: CMakeFiles/camera.dir/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/camera.dir/build.make CMakeFiles/camera.dir/camera.cpp.o.provides.build
.PHONY : CMakeFiles/camera.dir/camera.cpp.o.provides

CMakeFiles/camera.dir/camera.cpp.o.provides.build: CMakeFiles/camera.dir/camera.cpp.o

# Object files for target camera
camera_OBJECTS = \
"CMakeFiles/camera.dir/camera.cpp.o"

# External object files for target camera
camera_EXTERNAL_OBJECTS =

camera: CMakeFiles/camera.dir/camera.cpp.o
camera: CMakeFiles/camera.dir/build.make
camera: /usr/local/lib/libopencv_viz.so.2.4.9
camera: /usr/local/lib/libopencv_videostab.so.2.4.9
camera: /usr/local/lib/libopencv_video.so.2.4.9
camera: /usr/local/lib/libopencv_ts.a
camera: /usr/local/lib/libopencv_superres.so.2.4.9
camera: /usr/local/lib/libopencv_stitching.so.2.4.9
camera: /usr/local/lib/libopencv_photo.so.2.4.9
camera: /usr/local/lib/libopencv_ocl.so.2.4.9
camera: /usr/local/lib/libopencv_objdetect.so.2.4.9
camera: /usr/local/lib/libopencv_nonfree.so.2.4.9
camera: /usr/local/lib/libopencv_ml.so.2.4.9
camera: /usr/local/lib/libopencv_legacy.so.2.4.9
camera: /usr/local/lib/libopencv_imgproc.so.2.4.9
camera: /usr/local/lib/libopencv_highgui.so.2.4.9
camera: /usr/local/lib/libopencv_gpu.so.2.4.9
camera: /usr/local/lib/libopencv_flann.so.2.4.9
camera: /usr/local/lib/libopencv_features2d.so.2.4.9
camera: /usr/local/lib/libopencv_core.so.2.4.9
camera: /usr/local/lib/libopencv_contrib.so.2.4.9
camera: /usr/local/lib/libopencv_calib3d.so.2.4.9
camera: /usr/lib/i386-linux-gnu/libGLU.so
camera: /usr/lib/i386-linux-gnu/libGL.so
camera: /usr/lib/i386-linux-gnu/libSM.so
camera: /usr/lib/i386-linux-gnu/libICE.so
camera: /usr/lib/i386-linux-gnu/libX11.so
camera: /usr/lib/i386-linux-gnu/libXext.so
camera: /usr/local/lib/libopencv_nonfree.so.2.4.9
camera: /usr/local/lib/libopencv_ocl.so.2.4.9
camera: /usr/local/lib/libopencv_gpu.so.2.4.9
camera: /usr/local/lib/libopencv_photo.so.2.4.9
camera: /usr/local/lib/libopencv_objdetect.so.2.4.9
camera: /usr/local/lib/libopencv_legacy.so.2.4.9
camera: /usr/local/lib/libopencv_video.so.2.4.9
camera: /usr/local/lib/libopencv_ml.so.2.4.9
camera: /usr/local/lib/libopencv_calib3d.so.2.4.9
camera: /usr/local/lib/libopencv_features2d.so.2.4.9
camera: /usr/local/lib/libopencv_highgui.so.2.4.9
camera: /usr/local/lib/libopencv_imgproc.so.2.4.9
camera: /usr/local/lib/libopencv_flann.so.2.4.9
camera: /usr/local/lib/libopencv_core.so.2.4.9
camera: CMakeFiles/camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camera.dir/build: camera
.PHONY : CMakeFiles/camera.dir/build

CMakeFiles/camera.dir/requires: CMakeFiles/camera.dir/camera.cpp.o.requires
.PHONY : CMakeFiles/camera.dir/requires

CMakeFiles/camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camera.dir/clean

CMakeFiles/camera.dir/depend:
	cd /home/trisha/SHELDON && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON /home/trisha/SHELDON/CMakeFiles/camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/camera.dir/depend
