# Based on FindITTPP.cmake
#
# - Find IIO
# Find the native IIO includes and library
# This module defines
# IIO_INCLUDE_DIR, where to find iio.h, etc.
# IIO_LIBRARIES, the libraries needed to use IIO.
# IIO_FOUND, If false, do not try to use IIO.
# also defined, but not for general use are
# IIO_LIBRARY, where to find the IIO library.

#
# TODO: Add libxml2 dependency
#

message(STATUS "IIO_DIR set to: ${IIO_DIR}" )
message(STATUS "IIO_FIND_REQUIRED: ${IIO_FIND_REQUIRED}")

FIND_PATH(IIO_INCLUDE_DIR iio.h
${IIO_DIR}/include
/usr/include
/usr/local/include
)

#set(iio_lib_name "iio")
#if(${IIO_PREFER_STATIC})
#    set(iio_lib_name "libiio.a")
#endif()


FIND_LIBRARY(IIO_LIBRARY
NAMES iio
PATHS ${IIO_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)

if(IIO_LIBRARY AND IIO_INCLUDE_DIR)
    set(IIO_FOUND "YES")
else(IIO_LIBRARY AND IIO_INCLUDE_DIR)
    set(IIO_FOUND "NO")
endif(IIO_LIBRARY AND IIO_INCLUDE_DIR)


find_library(IIO_LIBRARY_STATIC
NAMES libiio.a
PATHS ${IIO_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(IIO_LIBRARY_STATIC AND IIO_INCLUDE_DIR)
    set(IIO_FOUND_STATIC "YES")
else()
    set(IIO_FOUND_STATIC "NO")
endif()

if(IIO_FOUND)
    if(NOT IIO_FIND_QUIETLY)
        message(STATUS "Found IIO_LIBRARY: ${IIO_LIBRARY}")
        message(STATUS "Found IIO_LIBRARY_STATIC: ${IIO_LIBRARY_STATIC}")
        message(STATUS "Found IIO_INCLUDE_DIR: ${IIO_INCLUDE_DIR}")
    endif(NOT IIO_FIND_QUIETLY)
else(IIO_FOUND)
    #if(IIO_FIND_REQUIRED)
    #    message(FATAL_ERROR "Could not find IIO library")
    #endif(IIO_FIND_REQUIRED)
endif(IIO_FOUND)

if(IIO_FIND_REQUIRED)
    if(NOT IIO_FOUND)
        message(FATAL_ERROR "Could not find IIO (dynamic) library!")
    endif()
    if(NOT IIO_FOUND_STATIC)
        message(FATAL_ERROR "Could not find IIO (static) library!")
    endif()
endif()


MARK_AS_ADVANCED(
IIO_LIBRARY
IIO_LIBRARY_STATIC
IIO_INCLUDE_DIR
)

