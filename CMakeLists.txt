## Probably 3.8 would be enough...
    set(CMAKE_MINIMUM_VERSION 3.22)

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_VERSION})


## # Something is broken in cmake 3.10.2
## # and GoogleTest cannot be used properly
## if(${CMAKE_VERSION} VERSION_GREATER "3.3")
##     cmake_policy(SET CMP0057 NEW)
## endif()

function(print_all_variables_regex
        ## regex_txt -> ARGV0
        ##              Only variables matching 'regex_txt' are printed
        ##
        ## Examples:
        ##
        ##   1) regex_txt = "^gf.*"              variables starting with gf
        ##
        ##   2) regex_txt = "^[aA][lL][aA].*"    variables starting with:
        ##
        ##                                        'ala'
        ##
        ##                                       CASE INSENSITIVE
        ##
        ##   3) regex_txt = "^[^C].*"            variables starting with
        ##                                       something different that 'C'
        ##
        ##
        ##
        ## reverse_match -> ARGV1
        ##                  reverses the match controlled by 'regex_txt'
        ##
        ## Example(s):
        ##
        ##   1) reverse_match = TRUE             then we print all
        ##                                       not matching versions
        ##
        ##
        ## Calling with these parameters should give satisfying results:
        ##
        ##   - regex_txt = "^(CMAKE_C_COMPILER_ID_PLATFORM_CONTENT|CMAKE_CXX_COMPILER_ID_PLATFORM_CONTENT).*"
        ##   - reverse_match = TRUE
        )


    ## message("Argument count: ${ARGC}")
    ## message("all arguments: ${ARGV}")
    ## message("optional arguments: ${ARGN}")

    set(regex_txt "")
    if(DEFINED ARGV0)
        ## message(STATUS "ARGV0: ${ARGV0}")
        set(regex_txt "${ARGV0}")
    endif()
    if("" STREQUAL "${regex_txt}")
        set(regex_txt "^z.*")
    endif()
    # message(STATUS "regex_txt: ${regex_txt}")
    # set(regex_txt "^gflags.*")

    message(STATUS "ARGV0: ${ARGV0}")
    message(STATUS "ARGV1: ${ARGV1}")


    set(reverse_match FALSE)
    if(DEFINED ARGV1)
        if(ARGV1)
            set(reverse_match TRUE)
        else()
            set(reverse_match FALSE)
        endif()
        ## set(reverse_match ${ARGV1})
    endif()

    message(STATUS)
    message(STATUS)
    message(STATUS "-------------------------------------------------------")
    message(STATUS
        ">> BEGIN print_all_variables_regex("
        "${regex_txt}, ${reverse_match}"
        ")"
    )
    message(STATUS "-------------------------------------------------------")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        set(do_print FALSE)
        string(REGEX MATCH
            ${regex_txt}
            do_print
            ${_variableName}
            )
        if(reverse_match)
            if(do_print)
                set(do_print FALSE)
            else()
                set(do_print TRUE)
            endif()
            ## set(do_print (not do_print))
        endif()
        if(${do_print})
            message(STATUS "${_variableName}=${${_variableName}}")
        endif()
    endforeach()
    # message(STATUS "print_all_variables_regex(${regex_txt}, ${reverse_match}) ------------------------------------------}")
    message(STATUS "-------------------------------------------------------")
    message(STATUS
        ">> END print_all_variables_regex("
        "${regex_txt}, ${reverse_match}"
        ")"
    )
    message(STATUS "-------------------------------------------------------")
    message(STATUS)
    message(STATUS)
endfunction()

project(hof VERSION 0.1.0)  # LANGUAGE CXX)
message(STATUS "${PROJECT_NAME}_SOURCE_DIR:  ${${PROJECT_NAME}_SOURCE_DIR}")


message(STATUS "PROJECT_VERSION_MAJOR: ${PROJECT_VERSION_MAJOR}")
message(STATUS "PROJECT_VERSION_MINOR: ${PROJECT_VERSION_MINOR}")
message(STATUS "PROJECT_VERSION_PATCH: ${PROJECT_VERSION_PATCH}")



set(HOF_LIB_NAME hof)
set(HOF_SOURCE_DIR "${HOF_LIB_NAME}")


include(GNUInstallDirs) # adds CMAKE_INSTALL_{LIBDIR,INCLUDEDIR,BINDIR}

# Exports compilations database (file: compile_commands.json)
# which when linked in the root project directory can hint vim's
# plugin for graying unused code about which code section could / should
# be grayed-out. Besides, can also be used by LSP (Language Server)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")



# Do not keep it in the cache, since it modifies / appends
# path to the previous CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH
    "${CMAKE_MODULE_PATH}"
    "${CMAKE_SOURCE_DIR}/cmake-modules"
    # CACHE PATH "path to the cmake modules" FORCE
)
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

message(STATUS "CONFIG_SCRIPT_PRELOADED: ${CONFIG_SCRIPT_PRELOADED}")
if(NOT CONFIG_SCRIPT_PRELOADED)
    message(FATAL_ERROR
        "Run cmake -C /path/to/cmake.script to preload a config script!"
    )
endif()


message(STATUS
    "CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES: "
    "${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}"
)
message(STATUS
    "CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES: "
    "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}"
)
message(STATUS
    "CMAKE_SYSTEM_INCLUDE_PATH: "
    "${CMAKE_SYSTEM_INCLUDE_PATH}"
)
message(STATUS
    "CMAKE_SYSTEM_LIBRARY_PATH: "
    "${CMAKE_SYSTEM_LIBRARY_PATH}"
)
message(STATUS
    "CMAKE_BUILD_RPATH: "
    "${CMAKE_BUILD_RPATH}"
)
message(STATUS
    "CMAKE_INSTALL_RPATH: "
    "${CMAKE_INSTALL_RPATH}"
)
# message(FATAL_ERROR "STOP!")



set(COVERAGE_EXTENSION coverage)
option(BUILD_COVERAGE
    "Add options to bulid libraries and executable(s) with tracking test coverage"
    OFF
)
if(NOT DEFINED EXPORT_PACKAGE_TO_GLOBAL_REGISTRY)
    option(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY
        "Do not export package to the cmake registry"
        ON
    )
endif()
if(BUILD_COVERAGE)
    # We don't want to share coverage build with the world
    set(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY OFF)
endif()
message(STATUS
    "EXPORT_PACKAGE_TO_GLOBAL_REGISTRY: ${EXPORT_PACKAGE_TO_GLOBAL_REGISTRY}"
 )

# CXX_COMPILE_OPTIONS must be set by an appropriate cmake script
include(CheckCXXCompilerFlag)
message(STATUS "CXX_COMPILE_OPTIONS: ${CXX_COMPILE_OPTIONS}")
set(f_index 26)
foreach(flag
        -g
        -std=c++11 -std=c++14 -std=c++17 -std=c++20 -std=c++23
        ${CXX_COMPILE_OPTIONS}
    )
    # message(STATUS "flag: ${flag}")
    check_cxx_compiler_flag(${flag} accepts)
    if(NOT accepts)
        message(FATAL_ERROR "Compiler does not support ${flag}")
    else()
        if(0 LESS f_index)
            message(STATUS
                "Compiler ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_ID} "
                "version: ${CMAKE_CXX_COMPILER_VERSION}) supports ${flag} "
                )
            ## message(STATUS "f_index: ${f_index}")
        endif()
        if(0 EQUAL f_index)
            message(STATUS
                "--------------"
                " remaining compiler flags are omitted "
                "--------------"
                )
            break()
        endif()
        math(EXPR f_index "${f_index} - 1")
    endif()
endforeach()
unset(f_index)

if(BUILD_COVERAGE)
    include(CodeCoverage)
endif()



enable_testing()


print_all_variables_regex("^CMAKE_CXX[0-9][0-9].*" FALSE)

#find_package(Boost REQUIRED COMPONENTS system chrono thread)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(LIBGFLAGS REQUIRED)
find_package(fmt)
## TODO(tgm): Inspect if it is possible to use 'gflags' instead of LIBGFLAGS.
##            This only searches for the library. In reality LIBGFLAGS (above)
##            is used, since there are -isystem related includes problems when
##            building with gflags...
find_package(gflags REQUIRED)
print_all_variables_regex("^gflags.*")
find_package(benchmark REQUIRED VERSION 1.5.0)
# print_all_variables_regex("^CMAKE.*" FALSE)

# find_package(LIBYAMLCPP REQUIRED VERSION 0.6)

message(STATUS "ENV_USER: $ENV{USER}")
message(STATUS "hof_INCLUDE_DIRS: ${hof_INCLUDE_DIRS}")

# find_package(LIBGFLAGS REQUIRED)

#set(CMAKE_THREAD_PREFER_PTHREAD ON)


#if(CMAKE_ZYNQ_CROSS_BUILD)
#    find_package(IIO REQUIRED)
#    find_package(XML2 REQUIRED)
#    find_package(LIBZ REQUIRED)
#endif()

# After all find_package
# set(HOF_TARGET_LINK_LIBRARIES
#     "xcomm"
#     "rf-aes-cipher"
# )
# set(HOF_TARGET_LINK_LIBRARIES_STATIC
#     "xcomm-static"
#     "rf-aes-cipher-static"
# )






execute_process (
    COMMAND bash -c "git rev-parse HEAD"
    OUTPUT_VARIABLE GIT_VERSION
)
string(REGEX REPLACE "\n$" "" GIT_VERSION "${GIT_VERSION}")
message(STATUS "GIT_VERSION: ${GIT_VERSION}")

execute_process (
    COMMAND bash -c "D=\"$(git status --porcelain | wc -l)\"; [ $D -ne 0 ] && echo \"-dirty\" || echo \"\""
    OUTPUT_VARIABLE GIT_DIRTY
)
string(REGEX REPLACE "\n$" "" GIT_DIRTY "${GIT_DIRTY}")
message(STATUS "GIT_DIRTY: ${GIT_DIRTY}")



add_compile_options(${CXX_COMPILE_OPTIONS})
add_definitions(-DSOURCE_DIRECTORY_ROOT_PATH="${CMAKE_SOURCE_DIR}/")
add_definitions(-DGIT_VERSION="${GIT_VERSION}")
add_definitions(-DGIT_DIRTY="${GIT_DIRTY}")



add_subdirectory(${HOF_SOURCE_DIR})
if(NOT DO_NOT_BUILD_TESTS)
    add_subdirectory(test)
endif()

if(NOT DO_NOT_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()


configure_file(
    "${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
# print_all_variables_regex(
#     "^(CMAKE_C_COMPILER_ID_PLATFORM_CONTENT|CMAKE_CXX_COMPILER_ID_PLATFORM_CONTENT).*"
#     TRUE
# )
