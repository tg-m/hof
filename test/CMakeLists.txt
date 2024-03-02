#file(GLOB_RECURSE srcs "${CMAKE_SOURCE_DIR}/src/*.cc")


file(GLOB_RECURSE tFs "${CMAKE_SOURCE_DIR}/test/*.test.cc")
list(APPEND testFiles "${tFs}")

file(GLOB_RECURSE tFs "${CMAKE_SOURCE_DIR}/${HOF_SOURCE_DIR}/*.test.cc")
list(APPEND testFiles "${tFs}")

set(dependencies_static
    ${LIBGFLAGS_LIBRARY_STATIC}
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    "${HOF_LIB_NAME}-static"
)
set(dependencies
    ${GTEST_LIBRARIES}
    ${LIBGFLAGS_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    "${HOF_LIB_NAME}"
)



foreach(dep ${dependencies_static})
    message(STATUS "test/CMakeLists.txt, DEP static: ${dep}")
endforeach()
foreach(dep ${dependencies})
    message(STATUS "test/CMakeLists.txt, DEP: ${dep}")
endforeach()


# foreach(src ${testFiles})
#     message(STATUS ${src})
# endforeach()


set(
    include_dirs_list
    "${CMAKE_SOURCE_DIR}/include-wrappers"
    "${GTEST_INCLUDE_DIRS}"
    ## ${CMAKE_SOURCE_DIR}/nanopb_include
    ## ${CMAKE_SOURCE_DIR}/up_api_include
)

# set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(test_run alltests-${PROJECT_NAME})

add_executable(${test_run}-static ${testFiles})
# GTEST_ADD_TESTS(${test_run}-static "" ${testFiles})

# It would probably be better to link against the static library
# instead of the shared one.
#
#   set(CMAKE_EXE_LINKER_FLAGS " -static")
#
#   target_link_libraries(
#       ${test_run}-static
#       -static-libgcc
#       -static-libstdc++
#       ${dependencies_static}
#   )
#
target_link_libraries(
    ${test_run}-static
    ${dependencies_static}
    ${LIBZ_LIBRARY_STATIC}
    ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(${test_run}-static PRIVATE ${include_dirs_list})

add_executable(${test_run} ${testFiles})
# GTEST_ADD_TESTS(${test_run} "" ${testFiles})
target_link_libraries(${test_run} ${dependencies})
target_include_directories(${test_run} PRIVATE ${include_dirs_list})


if(BUILD_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME ${test_run}-cov EXECUTABLE
        ${test_run}
        DEPENDENCIES ${test_run}
    )
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME ${test_run}-cov-static
        EXECUTABLE ${test_run}-static
        DEPENDENCIES ${test_run}-static
    )
    # add_executable(${test_run}-${COVERAGE_EXTENSION} ${testFiles})
    # GTEST_ADD_TESTS(${test_run}-${COVERAGE_EXTENSION} "" ${testFiles})
    # target_link_libraries(
    #     ${test_run}-${COVERAGE_EXTENSION}
    #     ${dependencies_coverage}
    # )
endif()


