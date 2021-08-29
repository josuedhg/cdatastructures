find_package(cmocka)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)
add_definitions(-DUNIT_TESTING=ON)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

file(GLOB c_tests *_tests.c)
foreach (file ${c_tests})
	get_filename_component(test_name ${file} NAME_WE)
	add_executable(${test_name} ${file} ${c_sources})

	target_link_libraries(${test_name} cmocka)
	add_test(NAME ${test_name}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${test_name})
endforeach()
