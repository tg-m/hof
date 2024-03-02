

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
include(../cxx_warnings.cmake)


set(CXX_COMPILE_OPTIONS "-std=c++17;-O3;${ALL_CXX_WARNING_FLAGS}" CACHE INTERNAL "description")

set(CONFIG_SCRIPT_PRELOADED true CACHE BOOL "Ensures that config script was preloaded")

#find_program(CLANG_TIDY_EXE
#    NAMES "clang-tidy"
#    DOC "Path to clang-tidy executable"
#    )
#if(NOT CLANG_TIDY_EXE)
#    message(STATUS "clang-tidy not found...")
#else()
#    message(STATUS "clang-tidy found!")
#    #set(system_headers "--system-headers=0")
#    set(header_filter "--header-filter=*.hh")
#    message(STATUS "system_headers: ${system_headers}")
#    message(STATUS "header_filter: ${header_filter}")
#    #set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" ${system_headers} ${header_filter} "-checks=*,clang-analyzer-alpha.*,-clang-diagnostic-unknown-warning-option,-fuchsia-overloaded-operator,-readability-simplify-boolean-expr,-fuchsia-default-arguments,-fuchsia-trailing-return,-modernize-use-trailing-return-type,-modernize-pass-by-value") # "--fix" "--fix-errors")
#    #set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" ${system_headers} ${header_filter} "cppcoreguidelines-,clang-analyzer-,bugprone-,cert-") # "--fix" "--fix-errors")
#    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" ${system_headers} ${header_filter} "*") # "--fix" "--fix-errors")
#endif()

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--enable-check-profile;--checks=-*,bugprone-*,clang-analyzer-*,misc-*,-modernize-*,performance-*,readability-*,-readability-static-definition-in-anonymous-namespace,-readability-simplify-boolean-expr,-readability-uppercase-literal-suffix,portability-*" CACHE INTERNAL "clang-tidy")
