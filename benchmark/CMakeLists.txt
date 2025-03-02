#file(GLOB_RECURSE srcs "${CMAKE_SOURCE_DIR}/src/*.cc")


file(GLOB_RECURSE tFs "${CMAKE_SOURCE_DIR}/*.bench.cc")
list(APPEND testFiles "${tFs}")


set(dependencies_static
    benchmark
    ${CMAKE_THREAD_LIBS_INIT}
    "${HOF_LIB_NAME}-static"
)
set(dependencies
    benchmark
    ${CMAKE_THREAD_LIBS_INIT}
    "${HOF_LIB_NAME}"
)



foreach(dep ${dependencies_static})
    message(STATUS "benchmark/CMakeLists.txt, DEP static: ${dep}")
endforeach()
foreach(dep ${dependencies})
    message(STATUS "benchmark/CMakeLists.txt, DEP: ${dep}")
endforeach()


# foreach(src ${testFiles})
#     message(STATUS ${src})
# endforeach()


set(
    include_dirs_list
    "${CMAKE_SOURCE_DIR}/include-wrappers"
    "${GTEST_INCLUDE_DIRS}"
)


set(test_run bench-${PROJECT_NAME})

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


