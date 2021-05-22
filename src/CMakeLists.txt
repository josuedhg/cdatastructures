cmake_minimum_required(VERSION 3.18)

set(c_sources
	${CMAKE_SOURCE_DIR}/src/array_stack.c
	${CMAKE_SOURCE_DIR}/src/array_queue.c
	PARENT_SCOPE)
set(c_headers array_stack.h array_queue.h)

add_library(array_stack SHARED array_stack.c)
add_library(array_queue SHARED array_queue.c)

set_target_properties(array_queue PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(array_stack PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS array_stack array_queue LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)
install( FILES ${c_headers} DESTINATION include/${PROJECT_NAME} COMPONENT headers)
