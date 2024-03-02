

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS
    "-std=c++17"
    "-O0"
    "-g"
    "--coverage"
    "-fprofile-arcs"
    "-ftest-coverage"
    "${ALL_CXX_WARNING_FLAGS}"
    CACHE INTERNAL
    "description"
)

set(BUILD_COVERAGE ON CACHE INTERNAL "Build coverage")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Cmake build type")

set(CONFIG_SCRIPT_PRELOADED true
    CACHE BOOL
    "Ensures that config script was preloaded"
)
set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY
    "OFF"
    CACHE INTERNAL
    "We do not export coverage version to the global register"
)
