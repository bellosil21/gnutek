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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tekgnu/gnutek

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tekgnu/gnutek

# Utility rule file for TekRSA_swig_swig_doc.

# Include the progress variables for this target.
include swig/CMakeFiles/TekRSA_swig_swig_doc.dir/progress.make

swig/CMakeFiles/TekRSA_swig_swig_doc: swig/TekRSA_swig_doc.i


swig/TekRSA_swig_doc.i: swig/TekRSA_swig_doc_swig_docs/xml/index.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tekgnu/gnutek/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating python docstrings for TekRSA_swig_doc"
	cd /home/tekgnu/gnutek/docs/doxygen && /usr/bin/python2 -B /home/tekgnu/gnutek/docs/doxygen/swig_doc.py /home/tekgnu/gnutek/swig/TekRSA_swig_doc_swig_docs/xml /home/tekgnu/gnutek/swig/TekRSA_swig_doc.i

swig/TekRSA_swig_doc_swig_docs/xml/index.xml: swig/_TekRSA_swig_doc_tag
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tekgnu/gnutek/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating doxygen xml for TekRSA_swig_doc docs"
	cd /home/tekgnu/gnutek/swig && ./_TekRSA_swig_doc_tag
	cd /home/tekgnu/gnutek/swig && /usr/bin/doxygen /home/tekgnu/gnutek/swig/TekRSA_swig_doc_swig_docs/Doxyfile

TekRSA_swig_swig_doc: swig/CMakeFiles/TekRSA_swig_swig_doc
TekRSA_swig_swig_doc: swig/TekRSA_swig_doc.i
TekRSA_swig_swig_doc: swig/TekRSA_swig_doc_swig_docs/xml/index.xml
TekRSA_swig_swig_doc: swig/CMakeFiles/TekRSA_swig_swig_doc.dir/build.make

.PHONY : TekRSA_swig_swig_doc

# Rule to build all files generated by this target.
swig/CMakeFiles/TekRSA_swig_swig_doc.dir/build: TekRSA_swig_swig_doc

.PHONY : swig/CMakeFiles/TekRSA_swig_swig_doc.dir/build

swig/CMakeFiles/TekRSA_swig_swig_doc.dir/clean:
	cd /home/tekgnu/gnutek/swig && $(CMAKE_COMMAND) -P CMakeFiles/TekRSA_swig_swig_doc.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/TekRSA_swig_swig_doc.dir/clean

swig/CMakeFiles/TekRSA_swig_swig_doc.dir/depend:
	cd /home/tekgnu/gnutek && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tekgnu/gnutek /home/tekgnu/gnutek/swig /home/tekgnu/gnutek /home/tekgnu/gnutek/swig /home/tekgnu/gnutek/swig/CMakeFiles/TekRSA_swig_swig_doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/TekRSA_swig_swig_doc.dir/depend

