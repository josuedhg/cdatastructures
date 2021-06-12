
include_directories(${CMAKE_SOURCE_DIR}/src)

set(stack_sample_src sample.c)
add_executable(stack_sample ${stack_sample_src})

target_link_libraries(stack_sample LINK_PUBLIC array_stack)
