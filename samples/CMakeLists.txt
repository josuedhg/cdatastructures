set(stack_brackets_src sample.c)

set(stack_postfix_src postfix_eval.c)

add_executable(stack_brackets ${stack_brackets_src})
add_executable(stack_postfix_eval postfix_eval_main.c ${stack_postfix_src})

target_include_directories(stack_brackets PRIVATE ${CMAKE_SOURCE_DIR}/samples)
target_include_directories(stack_postfix_eval PRIVATE ${CMAKE_SOURCE_DIR}/samples)

target_link_libraries(stack_brackets LINK_PUBLIC array_stack)
target_link_libraries(stack_postfix_eval LINK_PUBLIC array_stack)
