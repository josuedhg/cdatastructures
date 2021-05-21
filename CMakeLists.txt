cmake_minimum_required(VERSION 3.18)

project(datastructures)
add_executable(datastructures tests.c array_stack.c)
target_link_libraries(datastructures cmocka)
add_definitions(-DUNIT_TESTING=ON)
