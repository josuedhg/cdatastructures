#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "singly_linked_list.h"

struct data_obj
{
	int data1;
	int data2;
};

static int data_obj_search(void *data1, void *data2)
{
	struct data_obj *obj = (struct data_obj *)data1;
	struct data_obj *obj2 = (struct data_obj *)data2;
	return obj->data1 == obj2->data1 && obj->data2 == obj2->data2;
}

void singly_linked_list_append_test(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 1, 2};
	singly_linked_list_append(list, (void *)&data[0]);
	singly_linked_list_append(list, (void *)&data[1]);
	singly_linked_list_append(list, (void *)&data[2]);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 3; i++) {
		int *value = (int *)singly_linked_node_get_data(node);
		assert_int_equal(*value, data[i]);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_prepend_test(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 1, 2};
	singly_linked_list_prepend(list, (void *)&data[0]);
	singly_linked_list_prepend(list, (void *)&data[1]);
	singly_linked_list_prepend(list, (void *)&data[2]);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 2; i >= 0; i--) {
		int *value = (int *)singly_linked_node_get_data(node);
		assert_int_equal(*value, data[i]);
		singly_linked_node_move_next(&node);
	}

	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_insert_after_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 1, 2, 4, 3};
	struct list *head = NULL;
	singly_linked_list_append(list, (void*)&data[0]);
	singly_linked_list_append(list, (void*)&data[1]);
	singly_linked_list_append(list, (void*)&data[2]);
	singly_linked_list_append(list, (void*)&data[3]);
	singly_linked_list_insert_after(list, (void *)&data[4], (void*)&data[2], NULL);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 5; i++) {
		int *value = (int *)singly_linked_node_get_data(node);
		assert_non_null(value);
		assert_int_equal(*value, i);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_insert_after_custom_search_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	struct data_obj obj1 = {0,1};
	struct data_obj obj2 = {1,2};
	struct data_obj obj3 = {2,3};
	struct data_obj obj4 = {3,4};
	struct data_obj obj5 = {4,5};
	singly_linked_list_append(list, (void*)&obj1);
	singly_linked_list_append(list, (void*)&obj2);
	singly_linked_list_append(list, (void*)&obj3);
	singly_linked_list_append(list, (void*)&obj5);
	struct data_obj obj_search = {2,3};
	singly_linked_list_insert_after(list, (void *)&obj4, (void*)&obj_search, data_obj_search);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 5; i++) {
		struct data_obj *obj = (struct data_obj *)singly_linked_node_get_data(node);
		assert_int_equal(obj->data1, i);
		assert_int_equal(obj->data2, i + 1);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_delete_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 1, 4, 2};
	singly_linked_list_append(list, (void*)&data[0]);
	singly_linked_list_append(list, (void*)&data[1]);
	singly_linked_list_append(list, (void*)&data[2]);
	singly_linked_list_append(list, (void*)&data[3]);

	void *deleted = singly_linked_list_delete(list, (void*)&data[2], NULL);
	assert_non_null(deleted);

	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 3; i++) {
		int *value = (int *)singly_linked_node_get_data(node);
		assert_non_null(value);
		assert_int_equal(*value, i);
		assert_int_not_equal(*value, data[2]);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_delete_custom_search_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	struct data_obj obj1 = {0,1};
	struct data_obj del  = {3,4};
	struct data_obj obj2 = {1,2};
	struct data_obj obj3 = {2,3};

	singly_linked_list_append(list, (void*)&obj1);
	singly_linked_list_append(list, (void*)&obj2);
	singly_linked_list_append(list, (void*)&obj3);

	struct data_obj obj_search = {3,4};
	singly_linked_list_delete(list, (void*)&obj_search, data_obj_search);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 2; i++) {
		struct data_obj *obj = (struct data_obj *)singly_linked_node_get_data(node);
		assert_int_equal(obj->data1, i);
		assert_int_equal(obj->data2, i + 1);
		assert_int_not_equal(obj->data1, 3);
		assert_int_not_equal(obj->data2, 4);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_delete_nth_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 1, 4, 2};
	singly_linked_list_append(list, (void*)&data[0]);
	singly_linked_list_append(list, (void*)&data[1]);
	singly_linked_list_append(list, (void*)&data[2]);
	singly_linked_list_append(list, (void*)&data[3]);
	singly_linked_list_delete_nth(list, 2);
	struct singly_linked_node *node = singly_linked_list_get_head(list);
	for (int i = 0; i < 3; i++) {
		int *value = (int *)singly_linked_node_get_data(node);
		assert_int_equal(*value, i);
		assert_int_not_equal(*value, 4);
		singly_linked_node_move_next(&node);
	}
	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_get_nth_test(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 2, 4, 3};
	singly_linked_list_append(list, (void*)&data[0]);
	singly_linked_list_append(list, (void*)&data[1]);
	singly_linked_list_append(list, (void*)&data[2]);

	int *value = (int *)singly_linked_list_get_nth(list, 1);
	assert_int_equal(*value, 2);

	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_size_tests(void **state)
{
	struct singly_linked_list *list = singly_linked_list_init();
	int data[] = {0, 2, 4};
	struct list *head = NULL;
	singly_linked_list_append(list, (void*)&data[0]);
	singly_linked_list_append(list, (void*)&data[1]);
	singly_linked_list_append(list, (void*)&data[2]);

	assert_int_equal(singly_linked_list_get_size(list), 3);

	singly_linked_list_free_nodes(list);
	singly_linked_list_free(&list);
	assert_null(list);
}

void singly_linked_list_uninitialized(void **state)
{
	expect_assert_failure(singly_linked_list_prepend(NULL, (void*)1));
	expect_assert_failure(singly_linked_list_insert_after(NULL, (void*)2, 0, NULL));
	expect_assert_failure(singly_linked_list_append(NULL, (void*)3));
	expect_assert_failure(singly_linked_list_delete(NULL, (void*)4, NULL));
	expect_assert_failure(singly_linked_list_delete_nth(NULL, 0));
	expect_assert_failure(singly_linked_list_get_nth(NULL, 3));
	expect_assert_failure(singly_linked_list_get_size(NULL));
}

int main()
{
	const struct CMUnitTest tests[] = {
		// list
		cmocka_unit_test(singly_linked_list_append_test),
		cmocka_unit_test(singly_linked_list_prepend_test),
		cmocka_unit_test(singly_linked_list_insert_after_tests),
		cmocka_unit_test(singly_linked_list_insert_after_custom_search_tests),
		cmocka_unit_test(singly_linked_list_delete_tests),
		cmocka_unit_test(singly_linked_list_delete_custom_search_tests),
		cmocka_unit_test(singly_linked_list_delete_nth_tests),
		cmocka_unit_test(singly_linked_list_get_nth_test),
		cmocka_unit_test(singly_linked_list_size_tests),
		cmocka_unit_test(singly_linked_list_uninitialized),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
