# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC

# Include any dependencies generated for this target.
include CMakeFiles/ACaseSocket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ACaseSocket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ACaseSocket.dir/flags.make

CMakeFiles/ACaseSocket.dir/CSocketIPC.o: CMakeFiles/ACaseSocket.dir/flags.make
CMakeFiles/ACaseSocket.dir/CSocketIPC.o: CSocketIPC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ACaseSocket.dir/CSocketIPC.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ACaseSocket.dir/CSocketIPC.o -c /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CSocketIPC.cpp

CMakeFiles/ACaseSocket.dir/CSocketIPC.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ACaseSocket.dir/CSocketIPC.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CSocketIPC.cpp > CMakeFiles/ACaseSocket.dir/CSocketIPC.i

CMakeFiles/ACaseSocket.dir/CSocketIPC.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ACaseSocket.dir/CSocketIPC.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CSocketIPC.cpp -o CMakeFiles/ACaseSocket.dir/CSocketIPC.s

CMakeFiles/ACaseSocket.dir/CSocketIPC.o.requires:

.PHONY : CMakeFiles/ACaseSocket.dir/CSocketIPC.o.requires

CMakeFiles/ACaseSocket.dir/CSocketIPC.o.provides: CMakeFiles/ACaseSocket.dir/CSocketIPC.o.requires
	$(MAKE) -f CMakeFiles/ACaseSocket.dir/build.make CMakeFiles/ACaseSocket.dir/CSocketIPC.o.provides.build
.PHONY : CMakeFiles/ACaseSocket.dir/CSocketIPC.o.provides

CMakeFiles/ACaseSocket.dir/CSocketIPC.o.provides.build: CMakeFiles/ACaseSocket.dir/CSocketIPC.o


CMakeFiles/ACaseSocket.dir/ServerSocket.o: CMakeFiles/ACaseSocket.dir/flags.make
CMakeFiles/ACaseSocket.dir/ServerSocket.o: ServerSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ACaseSocket.dir/ServerSocket.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ACaseSocket.dir/ServerSocket.o -c /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/ServerSocket.cpp

CMakeFiles/ACaseSocket.dir/ServerSocket.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ACaseSocket.dir/ServerSocket.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/ServerSocket.cpp > CMakeFiles/ACaseSocket.dir/ServerSocket.i

CMakeFiles/ACaseSocket.dir/ServerSocket.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ACaseSocket.dir/ServerSocket.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/ServerSocket.cpp -o CMakeFiles/ACaseSocket.dir/ServerSocket.s

CMakeFiles/ACaseSocket.dir/ServerSocket.o.requires:

.PHONY : CMakeFiles/ACaseSocket.dir/ServerSocket.o.requires

CMakeFiles/ACaseSocket.dir/ServerSocket.o.provides: CMakeFiles/ACaseSocket.dir/ServerSocket.o.requires
	$(MAKE) -f CMakeFiles/ACaseSocket.dir/build.make CMakeFiles/ACaseSocket.dir/ServerSocket.o.provides.build
.PHONY : CMakeFiles/ACaseSocket.dir/ServerSocket.o.provides

CMakeFiles/ACaseSocket.dir/ServerSocket.o.provides.build: CMakeFiles/ACaseSocket.dir/ServerSocket.o


# Object files for target ACaseSocket
ACaseSocket_OBJECTS = \
"CMakeFiles/ACaseSocket.dir/CSocketIPC.o" \
"CMakeFiles/ACaseSocket.dir/ServerSocket.o"

# External object files for target ACaseSocket
ACaseSocket_EXTERNAL_OBJECTS =

/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so: CMakeFiles/ACaseSocket.dir/CSocketIPC.o
/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so: CMakeFiles/ACaseSocket.dir/ServerSocket.o
/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so: CMakeFiles/ACaseSocket.dir/build.make
/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so: CMakeFiles/ACaseSocket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ACaseSocket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ACaseSocket.dir/build: /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/lib/linux/libACaseSocket.so

.PHONY : CMakeFiles/ACaseSocket.dir/build

CMakeFiles/ACaseSocket.dir/requires: CMakeFiles/ACaseSocket.dir/CSocketIPC.o.requires
CMakeFiles/ACaseSocket.dir/requires: CMakeFiles/ACaseSocket.dir/ServerSocket.o.requires

.PHONY : CMakeFiles/ACaseSocket.dir/requires

CMakeFiles/ACaseSocket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ACaseSocket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ACaseSocket.dir/clean

CMakeFiles/ACaseSocket.dir/depend:
	cd /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC /home/xiaole/workspace/cameraframework/000_Framework/CaseClient/src/SocketIPC/CMakeFiles/ACaseSocket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ACaseSocket.dir/depend

