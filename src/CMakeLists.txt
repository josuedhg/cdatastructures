cmake_minimum_required(VERSION 3.18)

set(c_headers array_stack.h array_queue.h singly_linked_list.h btree.h node.h)

file(GLOB array_files array_*.c)
foreach(file ${array_files})
	get_filename_component(libname ${file} NAME_WE)
	add_library(${libname} SHARED ${file})
	set_target_properties(${libname} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
	install(TARGETS ${libname} LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)
endforeach()

file(GLOB list_files *_list.c)
foreach(file ${list_files})
	get_filename_component(libname ${file} NAME_WE)
	add_library(${libname} SHARED ${file} node.c)
	set_target_properties(${libname} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
	install(TARGETS ${libname} LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)
endforeach()

add_library(btree SHARED btree.c)
set_target_properties(btree PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS btree LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT sharedlibs)

install( FILES ${c_headers} DESTINATION include/${PROJECT_NAME} COMPONENT headers)
