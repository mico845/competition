# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_34395.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_34395.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_34395.dir/flags.make

CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.obj: CMakeFiles/cmTC_34395.dir/flags.make
CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.obj: testCXXCompiler.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.obj"
	C:\MinGW\gcc-arm-none-eabi\bin\arm-none-eabi-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cmTC_34395.dir\testCXXCompiler.cxx.obj -c C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\testCXXCompiler.cxx

CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.i: cmake_force
	@echo Preprocessing CXX source to CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.i
	C:\MinGW\gcc-arm-none-eabi\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\testCXXCompiler.cxx > CMakeFiles\cmTC_34395.dir\testCXXCompiler.cxx.i

CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.s: cmake_force
	@echo Compiling CXX source to assembly CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.s
	C:\MinGW\gcc-arm-none-eabi\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\testCXXCompiler.cxx -o CMakeFiles\cmTC_34395.dir\testCXXCompiler.cxx.s

# Object files for target cmTC_34395
cmTC_34395_OBJECTS = \
"CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.obj"

# External object files for target cmTC_34395
cmTC_34395_EXTERNAL_OBJECTS =

libcmTC_34395.a: CMakeFiles/cmTC_34395.dir/testCXXCompiler.cxx.obj
libcmTC_34395.a: CMakeFiles/cmTC_34395.dir/build.make
libcmTC_34395.a: CMakeFiles/cmTC_34395.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcmTC_34395.a"
	$(CMAKE_COMMAND) -P CMakeFiles\cmTC_34395.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cmTC_34395.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_34395.dir/build: libcmTC_34395.a

.PHONY : CMakeFiles/cmTC_34395.dir/build

CMakeFiles/cmTC_34395.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cmTC_34395.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_34395.dir/clean

CMakeFiles/cmTC_34395.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp C:\Users\Whisky\MYProjects\Project_STM32\STM32_F407_VET6\main\main_lcd\cmake-build-default\CMakeFiles\CMakeTmp\CMakeFiles\cmTC_34395.dir\DependInfo.cmake
.PHONY : CMakeFiles/cmTC_34395.dir/depend

