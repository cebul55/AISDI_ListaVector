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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release"

# Utility rule file for check.

# Include the progress variables for this target.
include tests/CMakeFiles/check.dir/progress.make

tests/CMakeFiles/check: tests/aisdiLinearTests
	cd "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release/tests" && /usr/local/bin/ctest --force-new-ctest-process --output-on-failure

check: tests/CMakeFiles/check
check: tests/CMakeFiles/check.dir/build.make

.PHONY : check

# Rule to build all files generated by this target.
tests/CMakeFiles/check.dir/build: check

.PHONY : tests/CMakeFiles/check.dir/build

tests/CMakeFiles/check.dir/clean:
	cd "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release/tests" && $(CMAKE_COMMAND) -P CMakeFiles/check.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/check.dir/clean

tests/CMakeFiles/check.dir/depend:
	cd "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe" "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/tests" "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release" "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release/tests" "/Users/bartoszcybulski/Documents/Informatyka WEITI Materiały /Semestr_3/Algorytmy i Struktury Danych/Lab/Liniowe/Release/tests/CMakeFiles/check.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/check.dir/depend
