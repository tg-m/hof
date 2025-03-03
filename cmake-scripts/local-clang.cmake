# The silent assumption is that cxx_warnings.cmake is
# in the parent directory of the directory in which
# a cmake -C /path/to/this/script .. is invoked!
#include(../cxx_warnings.cmake)






set(llvm_clang_dir "/opt/git/llvm/build/bin/")
set(llvm_clang_dir "/opt/local/bin/")
set(llvm_clang_dir "")

SET(CMAKE_C_COMPILER "${llvm_clang_dir}clang" CACHE INTERNAL STRING)
SET(CMAKE_CXX_COMPILER "${llvm_clang_dir}clang++" CACHE INTERNAL STRING)
SET(CMAKE_RANLIB "${llvm_clang_dir}llvm-ranlib" CACHE INTERNAL STRING)
SET(CMAKE_AR "${llvm_clang_dir}llvm-ar" CACHE INTERNAL STRING)
SET(CMAKE_AS "${llvm_clang_dir}llvm-as" CACHE INTERNAL STRING)
# SET(CMAKE_LINKER "${llvm_clang_dir}ld.lld" CACHE INTERNAL STRING)



## set(ALL_CXX_WARNING_FLAGS
##     "--all-warnings"
##     "-Weverything"
##     "-Wno-c++98-compat"
##     "-Wno-c++98-c++11-compat"
##     "-Wno-c++98-c++11-c++14-compat"
##     "-Wno-padded"
##     "-Wno-c++98-compat-pedantic"
## )
set(ALL_CXX_WARNING_FLAGS
  "--all-warnings"
  "-Weverything"
  "-Wno-c++98-compat"
  "-Wno-c++98-c++11-compat"
  "-Wno-c++98-c++11-c++14-compat"
  "-Wno-padded"
  "-Wno-c++98-compat-pedantic"
  "-std=c++26"
  # "-Werror"
  # "--system-header-prefix=up_api_include/"
  # "--system-header-prefix=nanopb_include/"
  "--system-header-prefix=requests.pb.h"
  "--system-header-prefix=responses.pb.h"
)
set(CXX_COMPILE_OPTIONS
    "-std=c++17"
    "-O2"
    "${ALL_CXX_WARNING_FLAGS}"
    CACHE INTERNAL
    "C++ compile options / settings"
)

set(CONFIG_SCRIPT_PRELOADED true
    CACHE BOOL
    "Ensures that config script was preloaded"
)
set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY "OFF"
    CACHE INTERNAL
    "We don't export local-clang version to global register"
)


########################################################
# set(build_test False)
#
# if(build_test)
#     message(STATUS "Using test mode clang-tidy checks!")
#     set(extra_clang_tidy_unchecks_for_tests_only
#         ",-google-readability-avoid-underscore-in-googletest-name"
#         ",-cppcoreguidelines-avoid-magic-numbers,"
#         "-cppcoreguidelines-special-member-functions"
#     )
# endif()
#
# set(CMAKE_CXX_CLANG_TIDY
#     "clang-tidy"
#     ";--enable-check-profile"
#     ";--checks=-*"
#         ",abseil-string-find-startswith"
#         ",bugprone-*"
#         ",cert-*"
#         ",clang-analyzer-*"
#         ",cppcoreguidelines-*"
#         ",google-*"
#         ",hicpp-*"
#         ",llvm-*"
#         ",misc-*"
#         ",modernize-*"
#         ",-modernize-use-trailing-return-type"
#         ",performance-*"
#         ",readability-*"
#         ",-readability-static-definition-in-anonymous-namespace"
#         ",-readability-simplify-boolean-expr"
#         ",portability-*"
#     "${extra_clang_tidy_unchecks_for_tests_only}"
#     CACHE INTERNAL "clang-tidy"
# )
#
# message(STATUS "build_test: ${build_test}")
# message(STATUS
#     "extra_clang_tidy_unchecks_for_tests_only:
#     ${extra_clang_tidy_unchecks_for_tests_only}"
# )
# message(STATUS "CMAKE_CXX_CLANG_TIDY: ${CMAKE_CXX_CLANG_TIDY}")
#
# ## We want to skip building tests when clang-tidy is run (it takes too
# ## much time and serves nothing)
# if(DEFINED CMAKE_CXX_CLANG_TIDY AND NOT build_test)
#     set(DO_NOT_BUILD_TESTS true
#         CACHE BOOL
#         "Turns OFF building tests"
#     )
#     set(DO_NOT_BUILD_BENCHMARKS true
#         CACHE BOOL
#         "Turns OFF building benchmarks"
#     )
# endif()
#
#
# unset(build_test)
# unset(extra_clang_tidy_unchecks_for_tests_only)


unset(llvm_clang_dir)
