

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(cxx_warnings.cmake)


# set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.2")
set(CMAKE_CXX_COMPILER
    "/opt/multi/gcc/13.2.0/bin/g++-13.2.0"
    CACHE STRING
    "CXX compiler"
)
# set(
#     CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES
#     # CMAKE_INCLUDE_PATH
#     "/opt/multi/gcc/13.2.0/include/c++/13.2.0/"
#     "/opt/multi/gcc/13.2.0/include/c++/13.2.0/x86_64-pc-linux-gnu/"
#     CACHE INTERNAL STRING
# )
set(
    CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
    "/opt/multi/gcc/13.2.0/include/c++/13.2.0/"
    "/opt/multi/gcc/13.2.0/include/c++/13.2.0/x86_64-pc-linux-gnu/"
    CACHE INTERNAL STRING
)
# set(
#     CMAKE_SYSTEM_INCLUDE_PATH
#     "/opt/multi/gcc/13.2.0/include/c++/13.2.0/"
#     "/opt/multi/gcc/13.2.0/include/c++/13.2.0/x86_64-pc-linux-gnu/"
#     CACHE INTERNAL STRING
# )
# set(
#     CMAKE_SYSTEM_LIBRARY_PATH
#     "/opt/multi/gcc/13.2.0/lib64/"
#     CACHE INTERNAL STRING
# )
set(
    CMAKE_INSTALL_RPATH
    "/opt/multi/gcc/13.2.0/lib64/"
    CACHE INTERNAL STRING
)
set(
    CMAKE_BUILD_RPATH
    "/opt/multi/gcc/13.2.0/lib64/"
    CACHE INTERNAL STRING
)
set(CXX_COMPILE_OPTIONS
    "-std=c++23"
    "-fconcepts"
    "-O3"
    "-nostdinc++"
    "-nostdlib++"
    ## "-isystem /opt/multi/gcc/13.2.0/include/c++/13.2.0/"
    ## "-isystem /opt/multi/gcc/13.2.0/include/c++/13.2.0/x86_64-pc-linux-gnu/"
    ## "-L /opt/multi/gcc/13.2.0/lib64/"
    ## "-Wl,-rpath,/opt/multi/gcc/13.2.0/lib64/"
    "-lstdc++"
    "-lgcc"
    "${ALL_CXX_WARNING_FLAGS}"
    ##
    ## Sometimes useful options:
    ##
    ##   "-fno-unsafe-loop-optimizations"
    ##   "-Wno-unsafe-loop-optimizations"
    ##
    ##
    ##
    ##
    ## Sometimes useful when testing various (custom built) compilers:
    ##
    ##   "-Wno-missing-include-dirs"
    ##
    ##
    ##
    ##
    ## Usefule on Gentoo
    ##
    ##   ## We need to disable it in local (i.e., x86) builds,
    ##   ## because GCC 10.3.0 (Gentoo 10.3.0-r2 p3) complains.
    ##   ## It is checked during cross / ARM builds anyway.
    ##   "-Wno-strict-overflow"
    ##
    ##
    CACHE INTERNAL
    "C++ compile options / settings"
)

set(CONFIG_SCRIPT_PRELOADED
    true
    CACHE BOOL
    "Ensures that config script was preloaded"
)
set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY
    "ON"
    CACHE INTERNAL
    "We do export local version to the global register"
)
