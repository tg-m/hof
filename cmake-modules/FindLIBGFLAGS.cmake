# Based on FindITTPP.cmake
#
# - Find gflags
# Find the native gflags includes and library
# This module defines
# LIBGFLAGS_INCLUDE_DIR, where to find library headers
# LIBGFLAGS_FOUND, If false, do not try to use gflags.
# also defined, but not for general use are
# LIBGFLAGS_LIBRARY, where to find the gflags library.


message(STATUS "LIBGFLAGS_DIR set to: ${LIBGFLAGS_DIR}" )
message(STATUS "LIBGFLAGS_FIND_REQUIRED: ${LIBGFLAGS_FIND_REQUIRED}")

FIND_PATH(LIBGFLAGS_INCLUDE_DIR gflags/gflags.h
${LIBGFLAGS_DIR}/include
/usr/include/
/usr/local/include
#${LIBGFLAGS_DIR}/include/gflags
#/usr/include/gflags
#/usr/local/include/gflags
)


FIND_LIBRARY(LIBGFLAGS_LIBRARY
NAMES gflags
PATHS ${LIBGFLAGS_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(LIBGFLAGS_LIBRARY AND LIBGFLAGS_INCLUDE_DIR)
    set(LIBGFLAGS_FOUND "YES")
else(LIBGFLAGS_LIBRARY AND LIBGFLAGS_INCLUDE_DIR)
    set(LIBGFLAGS_FOUND "NO")
endif(LIBGFLAGS_LIBRARY AND LIBGFLAGS_INCLUDE_DIR)


find_library(LIBGFLAGS_LIBRARY_STATIC
NAMES libgflags.a
PATHS ${LIBGFLAGS_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(LIBGFLAGS_LIBRARY_STATIC AND LIBGFLAGS_INCLUDE_DIR)
    set(LIBGFLAGS_FOUND_STATIC "YES")
else()
    set(LIBGFLAGS_FOUND_STATIC "NO")
endif()

message(STATUS "Found LIBGFLAGS_LIBRARY: ${LIBGFLAGS_LIBRARY}")
message(STATUS "Found LIBGFLAGS_LIBRARY_STATIC: ${LIBGFLAGS_LIBRARY_STATIC}")
message(STATUS "Found LIBGFLAGS_INCLUDE_DIR: ${LIBGFLAGS_INCLUDE_DIR}")

if(LIBGFLAGS_FIND_REQUIRED)
    if(NOT LIBGFLAGS_FOUND)
        message(FATAL_ERROR "Could not find gflags (dynamic) library!")
    endif()
    if(NOT LIBGFLAGS_FOUND_STATIC)
        message(FATAL_ERROR "Could not find gflags (static) library!")
    endif()
endif()


MARK_AS_ADVANCED(
LIBGFLAGS_LIBRARY
LIBGFLAGS_LIBRARY_STATIC
LIBGFLAGS_INCLUDE_DIR
)

