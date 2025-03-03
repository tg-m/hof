

# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!


# include(cxx_warnings.cmake)





#
# May require disabling find_package(Threads REQUIRED) to compile!
#

set(llvm_clang_dir "/opt/git/llvm/build/bin/")
set(llvm_clang_dir "/opt/local/bin/")
set(llvm_clang_dir "")

SET(CMAKE_C_COMPILER "${llvm_clang_dir}clang" CACHE INTERNAL STRING)
SET(CMAKE_CXX_COMPILER "${llvm_clang_dir}clang++" CACHE INTERNAL STRING)
SET(CMAKE_RANLIB "${llvm_clang_dir}llvm-ranlib" CACHE INTERNAL STRING)
SET(CMAKE_AR "${llvm_clang_dir}llvm-ar" CACHE INTERNAL STRING)
SET(CMAKE_AS "${llvm_clang_dir}llvm-as" CACHE INTERNAL STRING)
# SET(CMAKE_LINKER "${llvm_clang_dir}ld.lld" CACHE INTERNAL STRING)



set(ALL_CXX_WARNING_FLAGS
  "--all-warnings"
  "-Weverything"
  "-Wno-c++98-compat"
  "-Wno-c++98-c++11-compat"
  "-Wno-c++98-c++11-c++14-compat"
  "-Wno-padded"
  "-Wno-c++98-compat-pedantic"
  ## "-fcomment-block-commands=parblock,snippet,endparblock"
  ## "-fsafe-buffer-usage-suggestions"
  "-std=c++23"
  # "-Werror"
  # "--system-header-prefix=up_api_include/"
  # "--system-header-prefix=nanopb_include/"
  # "--system-header-prefix=requests.pb.h"
  # "--system-header-prefix=responses.pb.h"
)



set(CXX_COMPILE_OPTIONS
    "-O2"
    "${ALL_CXX_WARNING_FLAGS}"
    CACHE INTERNAL
    "C++ compile options / settings"
)


## set(CMAKE_CROSSCOMPILING True)
## set(CMAKE_TOOLCHAIN_FILE
##     "../cmake-scripts/toolchain_arm_clang.cmake"
##     CACHE
##     FILEPATH
##     "Clang-compatible ARM toolchain file"
## )

# set(CMAKE_TOOLCHAIN_FILE
#     "/opt/zynq/flavours/<REDACTED>/xsrc/generic-cmake/main_external_toolchain.cmake"
#     CACHE
#     FILEPATH
#     "Path to the cmake toolchain file"
# )

# set(LLVM_INSTALL_DIR /opt/git/llvm/build/bin)
# set(CLANG_INSTALL_DIR ${LLVM_INSTALL_DIR})
#
# set(LLVM_TABLEGEN ${LLVM_INSTALL_DIR}/llvm-tblgen)
# set(CLANG_TABLEGEN ${CLANG_INSTALL_DIR}/clang-tblgen)
#
# set(LLVM_DEFAULT_TARGET "arm-linux-gnueabihf")
# set(LLVM_TARGET_ARCH arm)
# set(LLVM_TARGETS_TO_BUILD ARM)

set(CONFIG_SCRIPT_PRELOADED
    true
    CACHE
    BOOL
    "Ensures that config script was preloaded"
)




set(build_test False)

if(build_test)
    message(STATUS "Using test mode clang-tidy checks!")
    ## ##
    ## ## Configuration for clang-tidy builds with testing was moved to
    ## ## `clang-tidy/tests.yaml`.
    ## ##
    ## set(cmake_cxx_clang_tidy_checks_for_tests
    ##     "-google-readability-avoid-underscore-in-googletest-name"
    ##     "-cppcoreguidelines-avoid-magic-numbers"
    ##     "-cppcoreguidelines-special-member-functions"
    ## )
endif()


## set(cmake_cxx_clang_tidy_checks
##     "-*"
##     "abseil-string-find-startswith"
##     "bugprone-*"
##     "cert-*"
##     "clang-analyzer-*"
##     "cppcoreguidelines-*"
##     "google-*"
##     "hicpp-*"
##     "llvm-*"
##     "misc-*"
##     "modernize-*"
##     "-modernize-use-trailing-return-type"
##     "-modernize-concat-nested-namespaces"
##     "performance-*"
##     "readability-*"
##     "-readability-static-definition-in-anonymous-namespace"
##     "-readability-simplify-boolean-expr"
##     # "-readability-identifier-length" ## Warns about ids shorter than 3 chars
##     "portability-*"
##     ## "bugprone-easily-swappable-parameters.MinimumLength=3"
##
##     ## Add bugprone... again!
##     "-bugprone-easily-swappable-parameters"
##     "${cmake_cxx_clang_tidy_checks_for_tests}"
## )
## string(REPLACE
##     ";"
##     ","
##     clang_tidy_checks
##     "${cmake_cxx_clang_tidy_checks}"
## )
## string(CONCAT clang_check_options
##   # # default
##   # "{key: readability-identifier-length.MinimumVariableNameLength, value: 3}"
##   # default
##   "  {"
##       "key: readability-identifier-length.MinimumVariableNameLength, "
##       "value: 3"
##   "}"
##   ", {"
##       "key: readability-identifier-length.IgnoredVariableNames, "
##       "value: \"^it|m$\""
##       # # default:
##       # "value: \"\""
##   "}"
##   ## # default
##   ## ", {"
##   ##     "key: readability-identifier-length.MinimumParameterNameLength, "
##   ##     "value: 3"
##   ## "}"
##   # default
##   ", {"
##       "key: readability-identifier-length.IgnoredParameterNames, "
##       "value: \"^[n]|os$\""
##       ## # default:
##       ## "value: \"^[n]$\""
##   "}"
##   ## ", {"
##   ##     "key: readability-identifier-length.MinimumLoopCounterNameLength, "
##   ##     "value: 1"
##   ##     ## # default:
##   ##     ## "value: 2"
##   ## "}"
##   ", {"
##       "key: readability-identifier-length.IgnoredLoopCounterNames, "
##       "value: \"^[eijk_]|fp$\""
##       ## # default:
##       ## "value: \"^[ijk_]$\""
##   "}"
##   ", {"
##       "key: misc-include-header.IgnoreHeaders, "
##       "value: \"yaml-cpp/*;yaml-cpp/yaml.h\""
##       # # default:
##       # "value: \"\""
##   "}"
##   ", {"
##       "key: misc-include-header.DeduplicateFindings, "
##       "value: true"
##       # # default:
##       # "value: true
##   "}"
## )


set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy"
    "--enable-check-profile"
    # "--checks=${clang_tidy_checks}"
    # "--config={CheckOptions: [${clang_check_options}]}"
    "--config-file=${CMAKE_SOURCE_DIR}/clang-tidy/all.yaml"
    # "--fix"
    CACHE INTERNAL
    "Configuration of clang-tidy"
)



message(STATUS "build_test: ${build_test}")
## message(STATUS
##     "cmake_cxx_clang_tidy_checks_for_tests:"
##     "${cmake_cxx_clang_tidy_checks_for_tests}"
## )
message(STATUS "CMAKE_CXX_CLANG_TIDY: ${CMAKE_CXX_CLANG_TIDY}")

# We want to skip building tests when clang-tidy is run
# (it takes too much time and serves nothing)
if(DEFINED CMAKE_CXX_CLANG_TIDY AND NOT build_test)
    set(DO_NOT_BUILD_TESTS true CACHE BOOL "Turns OFF building tests")
    set(DO_NOT_BUILD_BENCHMARKS
        true
        CACHE
        BOOL
        "Turns OFF building benchmarks"
    )
endif()


unset(build_test)
## unset(cmake_cxx_clang_tidy_checks_for_tests)
## unset(cmake_cxx_clang_tidy_checks)
## unset(clang_tidy_checks)
unset(clang_check_options)

unset(llvm_clang_dir)

set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY
    "OFF"
    CACHE
    INTERNAL
    "We don't export clang-tidy-all version to global register"
)
