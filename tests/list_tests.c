#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "list.h"
#include "list_tests.h"

struct data_obj
{
	int data1;
	int data2;
};

static int data_obj_search(struct list *node, void *data)
{
	struct data_obj *obj = (struct data_obj *)data;
	struct data_obj *obj2 = (struct data_obj *)node->data;
	return obj->data1 == obj2->data1 && obj->data2 == obj2->data2;
}

void list_append_test(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void *)0);
	list_append(&head, (void *)1);
	list_append(&head, (void *)2);
	struct list *node = head;
	for (int i = 0; i < 3; i++) {
		assert_int_equal(node->data, i);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_prepend_test(void **state)
{
	struct list *head = NULL;
	list_prepend(&head, (void *)0);
	list_prepend(&head, (void *)1);
	list_prepend(&head, (void *)2);
	struct list *node = head;
	for (int i = 2; i >= 0; i--) {
		assert_int_equal(node->data, i);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_insert_after_tests(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void*)0);
	list_append(&head, (void*)1);
	list_append(&head, (void*)2);
	list_append(&head, (void*)4);
	list_instert_after(&head, (void *)3, (void*)2, NULL);
	struct list *node = head;
	for (int i = 0; i < 5; i++) {
		assert_int_equal(node->data, i);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_insert_after_custom_search_tests(void **state)
{
	struct list *head = NULL;
	struct data_obj obj1 = {0,1};
	struct data_obj obj2 = {1,2};
	struct data_obj obj3 = {2,3};
	struct data_obj obj4 = {3,4};
	struct data_obj obj5 = {4,5};
	list_append(&head, (void*)&obj1);
	list_append(&head, (void*)&obj2);
	list_append(&head, (void*)&obj3);
	list_append(&head, (void*)&obj5);
	struct data_obj obj_search = {2,3};
	list_instert_after(&head, (void *)&obj4, (void*)&obj_search, data_obj_search);
	struct list *node = head;
	for (int i = 0; i < 5; i++) {
		struct data_obj *obj = (struct data_obj *)node->data;
		assert_int_equal(obj->data1, i);
		assert_int_equal(obj->data2, i + 1);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_delete_tests(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void*)0);
	list_append(&head, (void*)1);
	list_append(&head, (void*)4);
	list_append(&head, (void*)2);
	list_delete(&head, (void*)4, NULL);
	struct list *node = head;
	for (int i = 0; i < 3; i++) {
		assert_int_equal(node->data, i);
		assert_int_not_equal(node->data, 4);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_delete_custom_search_tests(void **state)
{
	struct list *head = NULL;
	struct data_obj obj1 = {0,1};
	struct data_obj del  = {3,4};
	struct data_obj obj2 = {1,2};
	struct data_obj obj3 = {2,3};
	list_append(&head, (void*)&obj1);
	list_append(&head, (void*)&obj2);
	list_append(&head, (void*)&obj3);
	struct data_obj obj_search = {3,4};
	list_delete(&head, (void*)&obj_search, data_obj_search);
	struct list *node = head;
	for (int i = 0; i < 2; i++) {
		struct data_obj *obj = (struct data_obj *)node->data;
		assert_int_equal(obj->data1, i);
		assert_int_equal(obj->data2, i + 1);
		assert_int_not_equal(obj->data1, 3);
		assert_int_not_equal(obj->data2, 4);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_delete_nth_tests(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void*)1);
	list_append(&head, (void*)2);
	list_append(&head, (void*)5);
	list_append(&head, (void*)3);
	list_delete_nth(&head, 2);
	struct list *node = head;
	for (int i = 0; i < 3; i++) {
		assert_int_equal(node->data, i + 1);
		assert_int_not_equal(node->data, 5);
		node = node->next;
	}
	list_free(&head);
	assert_null(head);
}

void list_get_nth_test(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void*)1);
	list_append(&head, (void*)2);
	list_append(&head, (void*)3);
	assert_int_equal(list_get_nth(head, 1), 2);
	list_free(&head);
	assert_null(head);
}

void list_size_tests(void **state)
{
	struct list *head = NULL;
	list_append(&head, (void*)0);
	list_append(&head, (void*)1);
	list_append(&head, (void*)2);
	assert_int_equal(list_size(head), 3);
	list_free(&head);
	assert_null(head);
}

void list_uninitialized(void **state)
{
	expect_assert_failure(list_prepend(NULL, (void*)1));
	expect_assert_failure(list_instert_after(NULL, (void*)2, 0, NULL));
	expect_assert_failure(list_append(NULL, (void*)3));
	expect_assert_failure(list_delete(NULL, (void*)4, NULL));
	expect_assert_failure(list_delete_nth(NULL, 0));
	expect_assert_failure(list_get_nth(NULL, 3));
	expect_assert_failure(list_size(NULL));
}
