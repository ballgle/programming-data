# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\dev_tools\CLion 2019.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\dev_tools\CLion 2019.1.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FFmpegWindows_Clion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FFmpegWindows_Clion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FFmpegWindows_Clion.dir/flags.make

CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj: CMakeFiles/FFmpegWindows_Clion.dir/flags.make
CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj: CMakeFiles/FFmpegWindows_Clion.dir/includes_CXX.rsp
CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj: ../ffmpeg-main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj"
	D:\dev_tools\MinGW-64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FFmpegWindows_Clion.dir\ffmpeg-main.cpp.obj -c D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\ffmpeg-main.cpp

CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.i"
	D:\dev_tools\MinGW-64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\ffmpeg-main.cpp > CMakeFiles\FFmpegWindows_Clion.dir\ffmpeg-main.cpp.i

CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.s"
	D:\dev_tools\MinGW-64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\ffmpeg-main.cpp -o CMakeFiles\FFmpegWindows_Clion.dir\ffmpeg-main.cpp.s

# Object files for target FFmpegWindows_Clion
FFmpegWindows_Clion_OBJECTS = \
"CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj"

# External object files for target FFmpegWindows_Clion
FFmpegWindows_Clion_EXTERNAL_OBJECTS =

FFmpegWindows_Clion.exe: CMakeFiles/FFmpegWindows_Clion.dir/ffmpeg-main.cpp.obj
FFmpegWindows_Clion.exe: CMakeFiles/FFmpegWindows_Clion.dir/build.make
FFmpegWindows_Clion.exe: CMakeFiles/FFmpegWindows_Clion.dir/linklibs.rsp
FFmpegWindows_Clion.exe: CMakeFiles/FFmpegWindows_Clion.dir/objects1.rsp
FFmpegWindows_Clion.exe: CMakeFiles/FFmpegWindows_Clion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FFmpegWindows_Clion.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FFmpegWindows_Clion.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FFmpegWindows_Clion.dir/build: FFmpegWindows_Clion.exe

.PHONY : CMakeFiles/FFmpegWindows_Clion.dir/build

CMakeFiles/FFmpegWindows_Clion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FFmpegWindows_Clion.dir\cmake_clean.cmake
.PHONY : CMakeFiles/FFmpegWindows_Clion.dir/clean

CMakeFiles/FFmpegWindows_Clion.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug D:\code\github\Programming-Notes\Android\00-Code\FFmpeg\FFmpegWindows-Clion\cmake-build-debug\CMakeFiles\FFmpegWindows_Clion.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FFmpegWindows_Clion.dir/depend

