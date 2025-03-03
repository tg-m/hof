

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS
    "-std=c++23"
    "-O3"
    "-fno-omit-frame-pointer"
    "${ALL_CXX_WARNING_FLAGS}"
    CACHE INTERNAL
    "C++ compile options / settings"
)

set(CONFIG_SCRIPT_PRELOADED true
    CACHE BOOL
    "Ensures that config script was preloaded"
)
set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY
    "OFF"
    CACHE INTERNAL
    "We do not export benchmark version to the global register"
)
