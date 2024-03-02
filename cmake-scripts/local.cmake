

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS
    "-std=c++17"
    "-O3"
    "${ALL_CXX_WARNING_FLAGS}"
    ##
    ## Sometimes useful options:
    ##
    ##   "-fno-unsafe-loop-optimizations"
    ##   "-Wno-unsafe-loop-optimizations"
    ##
    ## Usefule on Gentoo
    ##
    ##   ## We need to disable it in local (i.e., x86) builds,
    ##   ## because GCC 10.3.0 (Gentoo 10.3.0-r2 p3) complains.
    ##   ## It is checked during cross / ARM builds anyway.
    ##   "-Wno-strict-overflow"
    ##
    CACHE INTERNAL "description"
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
