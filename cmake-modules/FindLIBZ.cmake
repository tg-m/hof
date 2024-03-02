# Based on FindITTPP.cmake
#
# - Find libz
# Find the native libz includes and library
# This module defines
# LIBZ_INCLUDE_DIR, where to find library headers
# LIBZ_FOUND, If false, do not try to use libz.
# also defined, but not for general use are
# LIBZ_LIBRARY, where to find the libz library.


message(STATUS "LIBZ_DIR set to: ${LIBZ_DIR}" )
message(STATUS "LIBZ_FIND_REQUIRED: ${LIBZ_FIND_REQUIRED}")

FIND_PATH(LIBZ_INCLUDE_DIR zlib.h
${LIBZ_DIR}/include
/usr/include
/usr/local/include
)


FIND_LIBRARY(LIBZ_LIBRARY
NAMES z
PATHS ${LIBZ_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(LIBZ_LIBRARY AND LIBZ_INCLUDE_DIR)
    set(LIBZ_FOUND "YES")
else(LIBZ_LIBRARY AND LIBZ_INCLUDE_DIR)
    set(LIBZ_FOUND "NO")
endif(LIBZ_LIBRARY AND LIBZ_INCLUDE_DIR)


find_library(LIBZ_LIBRARY_STATIC
NAMES libz.a
PATHS ${LIBZ_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(LIBZ_LIBRARY_STATIC AND LIBZ_INCLUDE_DIR)
    set(LIBZ_FOUND_STATIC "YES")
else()
    set(LIBZ_FOUND_STATIC "NO")
endif()

if(LIBZ_FOUND)
    if(NOT LIBZ_FIND_QUIETLY)
        message(STATUS "Found LIBZ_LIBRARY: ${LIBZ_LIBRARY}")
        message(STATUS "Found LIBZ_LIBRARY_STATIC: ${LIBZ_LIBRARY_STATIC}")
        message(STATUS "Found LIBZ_INCLUDE_DIR: ${LIBZ_INCLUDE_DIR}")
    endif(NOT LIBZ_FIND_QUIETLY)
endif(LIBZ_FOUND)

if(LIBZ_FIND_REQUIRED)
    if(NOT LIBZ_FOUND)
        message(FATAL_ERROR "Could not find libz (dynamic) library!")
    endif()
    if(NOT LIBZ_FOUND_STATIC)
        message(FATAL_ERROR "Could not find libz (static) library!")
    endif()
endif()


MARK_AS_ADVANCED(
LIBZ_LIBRARY
LIBZ_LIBRARY_STATIC
LIBZ_INCLUDE_DIR
)

