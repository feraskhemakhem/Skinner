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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/feraskhemakhem/Desktop/Research/A6_Updated

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/feraskhemakhem/Desktop/Research/A6_Updated/build

# Include any dependencies generated for this target.
include CMakeFiles/A6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A6.dir/flags.make

CMakeFiles/A6.dir/src/Camera.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/Camera.cpp.o: ../src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A6.dir/src/Camera.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/Camera.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Camera.cpp

CMakeFiles/A6.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/Camera.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Camera.cpp > CMakeFiles/A6.dir/src/Camera.cpp.i

CMakeFiles/A6.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/Camera.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Camera.cpp -o CMakeFiles/A6.dir/src/Camera.cpp.s

CMakeFiles/A6.dir/src/Camera.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/Camera.cpp.o.requires

CMakeFiles/A6.dir/src/Camera.cpp.o.provides: CMakeFiles/A6.dir/src/Camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/Camera.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/Camera.cpp.o.provides

CMakeFiles/A6.dir/src/Camera.cpp.o.provides.build: CMakeFiles/A6.dir/src/Camera.cpp.o


CMakeFiles/A6.dir/src/GLSL.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/GLSL.cpp.o: ../src/GLSL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/A6.dir/src/GLSL.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/GLSL.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/GLSL.cpp

CMakeFiles/A6.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/GLSL.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/GLSL.cpp > CMakeFiles/A6.dir/src/GLSL.cpp.i

CMakeFiles/A6.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/GLSL.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/GLSL.cpp -o CMakeFiles/A6.dir/src/GLSL.cpp.s

CMakeFiles/A6.dir/src/GLSL.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/GLSL.cpp.o.requires

CMakeFiles/A6.dir/src/GLSL.cpp.o.provides: CMakeFiles/A6.dir/src/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/GLSL.cpp.o.provides

CMakeFiles/A6.dir/src/GLSL.cpp.o.provides.build: CMakeFiles/A6.dir/src/GLSL.cpp.o


CMakeFiles/A6.dir/src/MatrixStack.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/MatrixStack.cpp.o: ../src/MatrixStack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/A6.dir/src/MatrixStack.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/MatrixStack.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/MatrixStack.cpp

CMakeFiles/A6.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/MatrixStack.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/MatrixStack.cpp > CMakeFiles/A6.dir/src/MatrixStack.cpp.i

CMakeFiles/A6.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/MatrixStack.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/MatrixStack.cpp -o CMakeFiles/A6.dir/src/MatrixStack.cpp.s

CMakeFiles/A6.dir/src/MatrixStack.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/MatrixStack.cpp.o.requires

CMakeFiles/A6.dir/src/MatrixStack.cpp.o.provides: CMakeFiles/A6.dir/src/MatrixStack.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/MatrixStack.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/MatrixStack.cpp.o.provides

CMakeFiles/A6.dir/src/MatrixStack.cpp.o.provides.build: CMakeFiles/A6.dir/src/MatrixStack.cpp.o


CMakeFiles/A6.dir/src/Program.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/Program.cpp.o: ../src/Program.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/A6.dir/src/Program.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/Program.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Program.cpp

CMakeFiles/A6.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/Program.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Program.cpp > CMakeFiles/A6.dir/src/Program.cpp.i

CMakeFiles/A6.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/Program.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/Program.cpp -o CMakeFiles/A6.dir/src/Program.cpp.s

CMakeFiles/A6.dir/src/Program.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/Program.cpp.o.requires

CMakeFiles/A6.dir/src/Program.cpp.o.provides: CMakeFiles/A6.dir/src/Program.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/Program.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/Program.cpp.o.provides

CMakeFiles/A6.dir/src/Program.cpp.o.provides.build: CMakeFiles/A6.dir/src/Program.cpp.o


CMakeFiles/A6.dir/src/ShapeSkin.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/ShapeSkin.cpp.o: ../src/ShapeSkin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/A6.dir/src/ShapeSkin.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/ShapeSkin.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/ShapeSkin.cpp

CMakeFiles/A6.dir/src/ShapeSkin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/ShapeSkin.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/ShapeSkin.cpp > CMakeFiles/A6.dir/src/ShapeSkin.cpp.i

CMakeFiles/A6.dir/src/ShapeSkin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/ShapeSkin.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/ShapeSkin.cpp -o CMakeFiles/A6.dir/src/ShapeSkin.cpp.s

CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.requires

CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.provides: CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.provides

CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.provides.build: CMakeFiles/A6.dir/src/ShapeSkin.cpp.o


CMakeFiles/A6.dir/src/main.cpp.o: CMakeFiles/A6.dir/flags.make
CMakeFiles/A6.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/A6.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A6.dir/src/main.cpp.o -c /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/main.cpp

CMakeFiles/A6.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A6.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/main.cpp > CMakeFiles/A6.dir/src/main.cpp.i

CMakeFiles/A6.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A6.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/feraskhemakhem/Desktop/Research/A6_Updated/src/main.cpp -o CMakeFiles/A6.dir/src/main.cpp.s

CMakeFiles/A6.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/A6.dir/src/main.cpp.o.requires

CMakeFiles/A6.dir/src/main.cpp.o.provides: CMakeFiles/A6.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/A6.dir/build.make CMakeFiles/A6.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/A6.dir/src/main.cpp.o.provides

CMakeFiles/A6.dir/src/main.cpp.o.provides.build: CMakeFiles/A6.dir/src/main.cpp.o


# Object files for target A6
A6_OBJECTS = \
"CMakeFiles/A6.dir/src/Camera.cpp.o" \
"CMakeFiles/A6.dir/src/GLSL.cpp.o" \
"CMakeFiles/A6.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/A6.dir/src/Program.cpp.o" \
"CMakeFiles/A6.dir/src/ShapeSkin.cpp.o" \
"CMakeFiles/A6.dir/src/main.cpp.o"

# External object files for target A6
A6_EXTERNAL_OBJECTS =

A6: CMakeFiles/A6.dir/src/Camera.cpp.o
A6: CMakeFiles/A6.dir/src/GLSL.cpp.o
A6: CMakeFiles/A6.dir/src/MatrixStack.cpp.o
A6: CMakeFiles/A6.dir/src/Program.cpp.o
A6: CMakeFiles/A6.dir/src/ShapeSkin.cpp.o
A6: CMakeFiles/A6.dir/src/main.cpp.o
A6: CMakeFiles/A6.dir/build.make
A6: /Users/feraskhemakhem/Documents/GLSL_Libraries/glfw-3.2.1/debug/src/libglfw3.a
A6: /Users/feraskhemakhem/Documents/GLSL_Libraries/glew-2.1.0/lib/libGLEW.a
A6: CMakeFiles/A6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable A6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A6.dir/build: A6

.PHONY : CMakeFiles/A6.dir/build

CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/Camera.cpp.o.requires
CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/GLSL.cpp.o.requires
CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/MatrixStack.cpp.o.requires
CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/Program.cpp.o.requires
CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/ShapeSkin.cpp.o.requires
CMakeFiles/A6.dir/requires: CMakeFiles/A6.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/A6.dir/requires

CMakeFiles/A6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A6.dir/clean

CMakeFiles/A6.dir/depend:
	cd /Users/feraskhemakhem/Desktop/Research/A6_Updated/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/feraskhemakhem/Desktop/Research/A6_Updated /Users/feraskhemakhem/Desktop/Research/A6_Updated /Users/feraskhemakhem/Desktop/Research/A6_Updated/build /Users/feraskhemakhem/Desktop/Research/A6_Updated/build /Users/feraskhemakhem/Desktop/Research/A6_Updated/build/CMakeFiles/A6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A6.dir/depend

