cmake_minimum_required(VERSION 3.18)

set(c_sources
	${CMAKE_SOURCE_DIR}/src/array_stack.c
	${CMAKE_SOURCE_DIR}/src/array_queue.c
	${CMAKE_SOURCE_DIR}/src/singly_linked_list.c
	${CMAKE_SOURCE_DIR}/src/doubly_linked_list.c
	PARENT_SCOPE)
set(c_headers array_stack.h array_queue.h singly_linked_list.h)

add_library(array_stack SHARED array_stack.c)
add_library(array_queue SHARED array_queue.c)
add_library(list SHARED singly_linked_list.c)
add_library(dlist SHARED doubly_linked_list.c)

set_target_properties(array_queue PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(array_stack PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(list PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(dlist PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS array_stack array_queue list dlist LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)
install( FILES ${c_headers} DESTINATION include/${PROJECT_NAME} COMPONENT headers)
