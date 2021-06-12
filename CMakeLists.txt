cmake_minimum_required(VERSION 3.18)

project(datastructures)

include(GNUInstallDirs)
include(CMakeOptions.txt)
include_directories(src)

add_subdirectory(src)
if(${TESTS})
add_subdirectory(tests)
endif(${TESTS})
if (${SAMPLES})
add_subdirectory(samples)
endif(${SAMPLES})

message(STATUS "TESTS " ${TESTS})
