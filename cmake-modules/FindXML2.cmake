# Based on FindITTPP.cmake
#
# - Find Xml2
# Find the native Xml2 includes and library
# This module defines
# XML2_INCLUDE_DIR, where to find library headers
# XML2_FOUND, If false, do not try to use Xml2.
# also defined, but not for general use are
# XML2_LIBRARY, where to find the Xml2 library.

#
# TODO: Add libxml2 dependency
#

message(STATUS "XML2_DIR set to: ${XML2_DIR}" )
message(STATUS "XML2_FIND_REQUIRED: ${XML2_FIND_REQUIRED}")

FIND_PATH(XML2_INCLUDE_DIR xmlreader.h
#${XML2_DIR}/include
#${XML2_DIR}/include/libxml2
${XML2_DIR}/include/libxml2/libxml
/usr/include
/usr/local/include
)

#set(xml2_lib_name "xml2")
#if(XML2_PREFER_STATIC)
#    set(xml2_lib_name "libxml2.a")
#endif()

FIND_LIBRARY(XML2_LIBRARY
NAMES xml2
PATHS ${XML2_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(XML2_LIBRARY AND XML2_INCLUDE_DIR)
    set(XML2_FOUND "YES")
else(XML2_LIBRARY AND XML2_INCLUDE_DIR)
    set(XML2_FOUND "NO")
endif(XML2_LIBRARY AND XML2_INCLUDE_DIR)


find_library(XML2_LIBRARY_STATIC
NAMES libxml2.a
PATHS ${XML2_DIR}/lib
/usr/lib
/usr/local/lib
NO_DEFAULT_PATH
)


if(XML2_LIBRARY_STATIC AND XML2_INCLUDE_DIR)
    set(XML2_FOUND_STATIC "YES")
else()
    set(XML2_FOUND_STATIC "NO")
endif()

if(XML2_FOUND)
    if(NOT XML2_FIND_QUIETLY)
        message(STATUS "Found XML2_LIBRARY: ${XML2_LIBRARY}")
        message(STATUS "Found XML2_LIBRARY_STATIC: ${XML2_LIBRARY_STATIC}")
        message(STATUS "Found XML2_INCLUDE_DIR: ${XML2_INCLUDE_DIR}")
    endif(NOT XML2_FIND_QUIETLY)
else(XML2_FOUND)
    #if(XML2_FIND_REQUIRED)
    #    message(FATAL_ERROR "Could not find Xml2 library")
    #endif(XML2_FIND_REQUIRED)
endif(XML2_FOUND)

if(XML2_FIND_REQUIRED)
    if(NOT XML2_FOUND)
        message(FATAL_ERROR "Could not find Xml2 (dynamic) library!")
    endif()
    if(NOT XML2_FOUND_STATIC)
        message(FATAL_ERROR "Could not find Xml2 (static) library!")
    endif()
endif()


MARK_AS_ADVANCED(
XML2_LIBRARY
XML2_LIBRARY_STATIC
XML2_INCLUDE_DIR
)

