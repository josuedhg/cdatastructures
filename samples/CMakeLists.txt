set(stack_brackets_src sample.c)
set(stack_postfix_src postfix_eval.c)
set(stack_infix_to_postfix_src infix_to_postfix.c)

add_executable(stack_brackets ${stack_brackets_src})
add_executable(stack_postfix_eval postfix_eval_main.c ${stack_postfix_src})
add_executable(stack_infix_to_postfix infix_to_postfix_main.c ${stack_infix_to_postfix_src})
add_executable(stack_infix_eval infix_eval.c ${stack_postfix_src} ${stack_infix_to_postfix_src})

target_include_directories(stack_brackets PRIVATE ${CMAKE_SOURCE_DIR}/samples)
target_include_directories(stack_postfix_eval PRIVATE ${CMAKE_SOURCE_DIR}/samples)
target_include_directories(stack_infix_to_postfix PRIVATE ${CMAKE_SOURCE_DIR}/samples)
target_include_directories(stack_infix_eval PRIVATE ${CMAKE_SOURCE_DIR}/samples)

target_link_libraries(stack_brackets LINK_PUBLIC array_stack)
target_link_libraries(stack_postfix_eval LINK_PUBLIC array_stack)
target_link_libraries(stack_infix_to_postfix LINK_PUBLIC array_stack)
target_link_libraries(stack_infix_eval LINK_PUBLIC array_stack)
