

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(../cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS "-std=c++17;-O3;${ALL_CXX_WARNING_FLAGS}" CACHE INTERNAL "description")

set(CMAKE_TOOLCHAIN_FILE "/opt/zynq/xsrc/generic-cmake/main_external_toolchain.cmake" CACHE FILEPATH "Path to the cmake toolchain file")

set(CONFIG_SCRIPT_PRELOADED true CACHE BOOL "Ensures that config script was preloaded")
