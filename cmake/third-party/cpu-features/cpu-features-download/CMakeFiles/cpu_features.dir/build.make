# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download

# Utility rule file for cpu_features.

# Include any custom commands dependencies for this target.
include CMakeFiles/cpu_features.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cpu_features.dir/progress.make

CMakeFiles/cpu_features: CMakeFiles/cpu_features-complete

CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-install
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-mkdir
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-download
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-update
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-patch
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-build
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-install
CMakeFiles/cpu_features-complete: cpu_features-prefix/src/cpu_features-stamp/cpu_features-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'cpu_features'"
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E make_directory /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles/cpu_features-complete
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-done

cpu_features-prefix/src/cpu_features-stamp/cpu_features-build: cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-build

cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure: cpu_features-prefix/tmp/cpu_features-cfgcmd.txt
cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure: cpu_features-prefix/src/cpu_features-stamp/cpu_features-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure

cpu_features-prefix/src/cpu_features-stamp/cpu_features-download: cpu_features-prefix/src/cpu_features-stamp/cpu_features-gitinfo.txt
cpu_features-prefix/src/cpu_features-stamp/cpu_features-download: cpu_features-prefix/src/cpu_features-stamp/cpu_features-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features && /usr/local/Cellar/cmake/3.25.2/bin/cmake -P /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/tmp/cpu_features-gitclone.cmake
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-download

cpu_features-prefix/src/cpu_features-stamp/cpu_features-install: cpu_features-prefix/src/cpu_features-stamp/cpu_features-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-install

cpu_features-prefix/src/cpu_features-stamp/cpu_features-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'cpu_features'"
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -Dcfgdir= -P /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/tmp/cpu_features-mkdirs.cmake
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-mkdir

cpu_features-prefix/src/cpu_features-stamp/cpu_features-patch: cpu_features-prefix/src/cpu_features-stamp/cpu_features-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'cpu_features'"
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	/usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-patch

cpu_features-prefix/src/cpu_features-stamp/cpu_features-test: cpu_features-prefix/src/cpu_features-stamp/cpu_features-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-test

cpu_features-prefix/src/cpu_features-stamp/cpu_features-update: cpu_features-prefix/src/cpu_features-stamp/cpu_features-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No update step for 'cpu_features'"
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-src && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E echo_append
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-src && /usr/local/Cellar/cmake/3.25.2/bin/cmake -E touch /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/cpu_features-update

cpu_features: CMakeFiles/cpu_features
cpu_features: CMakeFiles/cpu_features-complete
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-build
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-configure
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-download
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-install
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-mkdir
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-patch
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-test
cpu_features: cpu_features-prefix/src/cpu_features-stamp/cpu_features-update
cpu_features: CMakeFiles/cpu_features.dir/build.make
.PHONY : cpu_features

# Rule to build all files generated by this target.
CMakeFiles/cpu_features.dir/build: cpu_features
.PHONY : CMakeFiles/cpu_features.dir/build

CMakeFiles/cpu_features.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpu_features.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpu_features.dir/clean

CMakeFiles/cpu_features.dir/depend:
	cd /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download /Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/CMakeFiles/cpu_features.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpu_features.dir/depend

