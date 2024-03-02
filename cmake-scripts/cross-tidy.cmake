

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(../cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS "-std=c++17;-O3;${ALL_CXX_WARNING_FLAGS}" CACHE INTERNAL "description")

set(CMAKE_TOOLCHAIN_FILE "/opt/zynq/xsrc/generic-cmake/main_external_toolchain.cmake" CACHE FILEPATH "Path to the cmake toolchain file")


# Intentionally turned off to ensure that cross compilation won't be used
# together with clang-tidy, since clang-tidy tool produes a diagnostic error
# about its inability to find c/c++ headers, such as <utility>, <chrono>, etc.
# This is probably due to the cross-compilation.
#set(CONFIG_SCRIPT_PRELOADED true CACHE BOOL "Ensures that config script was preloaded")

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--enable-check-profile;--checks=-*,bugprone-*,clang-analyzer-*,performance-*" CACHE INTERNAL "clang-tidy")
