# Wiki at https://gitlab.kitware.com/cmake/community/wikis/FAQ#can-i-do-make-uninstall-with-cmake
# Code Source from https://gitlab.kitware.com/cmake/cmake/blob/master/cmake_uninstall.cmake.in
# License: BSD-3 as documented here: https://gitlab.kitware.com/cmake/cmake/blob/master/Copyright.txt

IF(NOT EXISTS "/home/tekgnu/gnutek/build/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/tekgnu/gnutek/build/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/tekgnu/gnutek/build/install_manifest.txt")

FILE(READ "/home/tekgnu/gnutek/build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  IF(EXISTS "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF(NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF(NOT "${rm_retval}" STREQUAL 0)
  ELSEIF(IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF(NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF(NOT "${rm_retval}" STREQUAL 0)
  ELSE(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  ENDIF(EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)
