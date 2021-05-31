#ifndef __LISTS_TESTS_H__
#define __LISTS_TESTS_H__

void list_append_test(void **state);
void list_prepend_test(void **state);
void list_insert_after_tests(void **state);
void list_insert_after_custom_search_tests(void **state);
void list_delete_tests(void **state);
void list_delete_custom_search_tests(void **state);
void list_delete_nth_tests(void **state);
void list_get_nth_test(void **state);
void list_size_tests(void **state);
void list_uninitialized(void **state);

#endif /* end of include guard: __LISTS_TESTS_H__ */
