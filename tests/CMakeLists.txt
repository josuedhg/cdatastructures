find_package(cmocka)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(c_tests tests.c array_stack_tests.c array_queue_tests.c list_tests.c) 

add_definitions(-DUNIT_TESTING=ON)

add_executable(tests ${c_tests} ${c_sources})

target_link_libraries(tests cmocka)
