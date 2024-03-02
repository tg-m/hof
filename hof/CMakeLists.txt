# This file requiers that the following variables
# are set in the top level CMakeLists.txt:
# - Library name:
#     HOF_LIB_NAME
#
# - Directory with library source files:
#     HOF_LIB_SOURCE_DIR
#
# - Directory that will contain CMake config files
#   used to automatically find HOF
#   after its intallation on the target system; this name
#   is chosen according to GNUInstallDirs scheme:
#     CMAKE_INSTALL_CMAKE_HOFDIR
#
# - Libraries that are linked with dynamic version of HOF:
#     HOF_TARGET_LINK_LIBRARIES
#
# - Libraries that are linked with static version of HOF:
#     HOF_TARGET_LINK_LIBRARIES_STATIC
#
# - Target include directories:
#     HOF_TARGET_INCLUDE_DIRECTORIES_PRIVATE
#     HOF_TARGET_INCLUDE_DIRECTORIES_PUBLIC
#
#
#
#
#
#




set(HOF_LIB_MAJOR_VERSION ${PROJECT_VERSION_MAJOR} CACHE STRING "major version" FORCE) # force overrides eventual user changes
set(HOF_LIB_MINOR_VERSION ${PROJECT_VERSION_MINOR} CACHE STRING "minor version" FORCE)
set(HOF_LIB_PATCH_VERSION ${PROJECT_VERSION_PATCH} CACHE STRING "patch version" FORCE)
set(HOF_LIB_VERSION ${HOF_LIB_MAJOR_VERSION}.${HOF_LIB_MINOR_VERSION}.${HOF_LIB_PATCH_VERSION}${VERSION_COMPILATION_TAG} CACHE STRING "version" FORCE)
message(STATUS "HOF_LIB_VERSION: ${HOF_LIB_VERSION}")


set(HOF_LIB_NAME_WITH_VERSION "${HOF_LIB_NAME}-${HOF_LIB_VERSION}" CACHE STRING "library name with version" FORCE)
message(STATUS "HOF_LIB_NAME_WITH_VERSION: ${HOF_LIB_NAME_WITH_VERSION}")



foreach(s HOF_TARGET_LINK_LIBRARIES HOF_TARGET_LINK_LIBRARIES_STATIC HOF_TARGET_INCLUDE_DIRECTORIES_PRIVATE HOF_TARGET_INCLUDE_DIRECTORIES_PUBLIC)
    message(STATUS "s: ${s}")
    foreach(t ${${s}})
        message(STATUS "    HOF: ${t}")
    endforeach()
endforeach()




set(hof_config "${HOF_LIB_NAME}-config" CACHE STRING "begining of the config and version files" FORCE)
set(hof_config_cmake "${hof_config}.cmake" CACHE FILEPATH "${HOF_LIB_NAME} config file name" FORCE)
set(hof_config_cmake_in "${hof_config_cmake}.in" CACHE FILEPATH "${HOF_LIB_NAME} config input file name" FORCE)
set(hof_config_version_cmake "${hof_config}-version.cmake" CACHE FILEPATH "${HOF_LIB_NAME} config version file name" FORCE)
set(hof_config_version_cmake_in "${hof_config_version_cmake}.in" CACHE FILEPATH "${HOF_LIB_NAME} config version cmake in file name" FORCE)

set(hof_exports "${HOF_LIB_NAME}-exports" CACHE STRING "${HOF_LIB_NAME} exports files name" FORCE)
set(hof_exports_cmake "${hof_exports}.cmake" CACHE STRING "${HOF_LIB_NAME} exports files name" FORCE)

set(hof_config_hh "${HOF_LIB_NAME}-config.hh" CACHE STRING "${HOF_LIB_NAME} configuration header" FORCE)


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.hh.in)
    configure_file(config.hh.in "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_hh}" @ONLY)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config.internal.hh.in)
    configure_file("config.internal.hh.in" "${CMAKE_CURRENT_BINARY_DIR}/config.internal.hh" @ONLY)
endif()

file(GLOB_RECURSE temp_srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")


set(srcs )
foreach(s ${temp_srcs})
    string(REGEX MATCH ".test.cc" match_test ${s})
    string(REGEX MATCH ".bench.cc" match_bench ${s})
    if(NOT match_test AND NOT math_bench)
        #message(STATUS ${s})
        set(srcs ${srcs} ${s})
    endif()
endforeach()

set(lib_include_install_dir "${CMAKE_INSTALL_INCLUDEDIR}/${HOF_LIB_NAME_WITH_VERSION}")


#include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE include_files "${CMAKE_CURRENT_SOURCE_DIR}/*.hh")

message(STATUS "include_files: ${include_files}")
message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")

foreach(lib ${HOF_TARGET_LINK_LIBRARIES})
    message(STATUS "${HOF_LIB_SOURCE_DIR}/CMakeLists.txt libs: ${lib}")
endforeach()

#list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O3")

add_library(${HOF_LIB_NAME} SHARED ${srcs})
set_target_properties(${HOF_LIB_NAME} PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_hh}")
set_target_properties(${HOF_LIB_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )
#if(CLANG_TIDY_EXE)
#    set_target_properties(${HOF_LIB_NAME} PROPERTIES
#        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#        )
#endif()
#set_target_properties(${HOF_LIB_NAME} PROPERTIES VERSION "${HOF_LIB_VERSION}" SOVERSION "${HOF_LIB_MAJOR_VERSION}.${HOF_LIB_MINOR_VERSION}")
target_link_libraries(${HOF_LIB_NAME} ${HOF_TARGET_LINK_LIBRARIES})

target_include_directories(${HOF_LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${lib_include_install_dir}>
    )
target_include_directories(${HOF_LIB_NAME} PRIVATE
    ${HOF_TARGET_INCLUDE_DIRECTORIES_PRIVATE})
target_include_directories(${HOF_LIB_NAME} PUBLIC
    ${HOF_TARGET_INCLUDE_DIRECTORIES_PUBLIC})


add_library(${HOF_LIB_NAME}-static STATIC ${srcs})
set_target_properties(${HOF_LIB_NAME}-static PROPERTIES OUTPUT_NAME "${HOF_LIB_NAME}")
set_target_properties(${HOF_LIB_NAME}-static PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_hh}")
set_target_properties(${HOF_LIB_NAME}-static PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )
#if(CLANG_TIDY_EXE)
#    set_target_properties(${HOF_LIB_NAME}-static PROPERTIES
#        CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#        )
#endif()
target_link_libraries(${HOF_LIB_NAME}-static ${HOF_TARGET_LINK_LIBRARIES_STATIC})
target_include_directories(${HOF_LIB_NAME}-static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${lib_include_install_dir}>
    )
target_include_directories(${HOF_LIB_NAME}-static PRIVATE
    ${HOF_TARGET_INCLUDE_DIRECTORIES_PRIVATE})
target_include_directories(${HOF_LIB_NAME}-static PUBLIC
    ${HOF_TARGET_INCLUDE_DIRECTORIES_PUBLIC})

#if(BUILD_COVERAGE)
#    add_library(${HOF_LIB_NAME}-${COVERAGE_EXTENSION} SHARED ${srcs})
#    target_link_libraries(${HOF_LIB_NAME}-${COVERAGE_EXTENSION} ${libs})
#
#    add_library(${HOF_LIB_NAME}-${COVERAGE_EXTENSION}-static STATIC ${srcs})
#    set_target_properties(${HOF_LIB_NAME}-${COVERAGE_EXTENSION}-static PROPERTIES OUTPUT_NAME "${HOF_LIB_NAME}-${COVERAGE_EXTENSION}")
#    target_link_libraries(${HOF_LIB_NAME}-${COVERAGE_EXTENSION}-static ${libs})# ${ARMADILLO_LIBRARIES} boost_system boost_chrono)
#endif()


install(TARGETS ${HOF_LIB_NAME}-static ${HOF_LIB_NAME}
    EXPORT ${hof_exports}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    PUBLIC_HEADER DESTINATION "${lib_include_install_dir}" COMPONENT headers
    )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
    COMPONENT headers
    DESTINATION "${lib_include_install_dir}"
    FILES_MATCHING PATTERN "*.hh"
    PATTERN "*.internal.hh" EXCLUDE)


if(EXPORT_PACKAGE_TO_GLOBAL_REGISTRY)
    export(TARGETS  ${HOF_LIB_NAME} ${HOF_LIB_NAME}-static FILE "${hof_exports_cmake}")
    export(PACKAGE ${HOF_LIB_NAME})
endif()

# Build tree
set(CONFIG_DOT_CMAKE_TREE_TYPE "build")
set(CONFIG_DOT_CMAKE_INCLUDE_DIRS "${HOF_LIB_SOURCE_DIR}" "${PROJECT_BINARY_DIR}/${HOF_LIB_NAME}")
configure_file(${hof_config_cmake_in} "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_cmake}" @ONLY)



# Name chosen according to the GNUInstallDirs scheme
set(CMAKE_INSTALL_CMAKE_HOFDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${HOF_LIB_NAME} CACHE PATH "${HOF_LIB_NAME} cmake files installation directory" FORCE)
message(STATUS "CMAKE_INSTALL_CMAKE_HOFDIR: ${CMAKE_INSTALL_CMAKE_HOFDIR}")
# Create absolute paths
foreach(p LIB BIN INCLUDE CMAKE_HOF)
    set(rel_path CMAKE_INSTALL_${p}DIR)
    set(var CMAKE_INSTALL_${p}DIR_ABSOLUTE)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${rel_path}}")
    endif()
    message(STATUS "CMAKE_INSTALL_${p}DIR: ${CMAKE_INSTALL_${p}DIR}")
    message(STATUS "${var}: ${${var}}")
endforeach()

file(RELATIVE_PATH RELATIVE_HOF_INCLUDE_DIR "${CMAKE_INSTALL_CMAKE_HOFDIR_ABSOLUTE}" "${CMAKE_INSTALL_INCLUDEDIR_ABSOLUTE}")



# install tree
set(CONFIG_DOT_CMAKE_TREE_TYPE "install")
set (CONFIG_DOT_CMAKE_INCLUDE_DIRS "\${CMAKE_INSTALL_CMAKE_HOFDIR}/${RELATIVE_HOF_INCLUDE_DIR}")
# maybe PROJECT_BINARY_DIR line below should be changed to CMAKE_CURRENT_BINARY_DIR?
configure_file(${hof_config_cmake_in} "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${hof_config_cmake}" @ONLY)
include(CMakePackageConfigHelpers)
#configure_package_config_file(${hof_config_cmake_in} ${hof_config_cmake}
#    INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKE_HOFDIR})

#set(CONFIG_VERSION_DOT_PACKAGE_VERSION "${HOF_LIB_VERSION}" CACHE STRING "package version string" FORCE)
#configure_file(${hof_config_version_cmake_in} "${PROJECT_BINARY_DIR}/${hof_config_version_cmake}" @ONLY)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_version_cmake}"
  VERSION ${HOF_LIB_VERSION}
  COMPATIBILITY AnyNewerVersion
)



install(FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${hof_config_cmake}"
    "${CMAKE_CURRENT_BINARY_DIR}/${hof_config_version_cmake}"
    DESTINATION "${CMAKE_INSTALL_CMAKE_HOFDIR}"
    COMPONENT dev) # if CMAKE_INSTALL_CMAKE_HOFDIR_ABSOLUTE  left here, then path cannot be changed via CMAKE_INSTALL_PREFIX
install(EXPORT ${hof_exports} DESTINATION "${CMAKE_INSTALL_CMAKE_HOFDIR}" COMPONENT dev) # if CMAKE_INSTALL_CMAKE_HOFDIR_ABSOLUTE  left here, then path cannot be changed via CMAKE_INSTALL_PREFIX





# Debuging...
foreach(var_prop "INCLUDE_DIRECTORIES" "LINK_LIBRARIES" "INTERFACE_INCLUDE_DIRECTORIES" "INTERFACE_SYSTEM_INCLUDE_DIRECTORIES")
    message(STATUS "var_prop: ${var_prop}")
    get_target_property(prop ${HOF_LIB_NAME} ${var_prop})
    foreach(i ${prop})
        message(STATUS "    HOF:${var_prop}: ${i}")
    endforeach()
endforeach()
