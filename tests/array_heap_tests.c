#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "array_heap.h"

#define HEAP_SIZE 3

void *sample_array[HEAP_SIZE] = { 0 };

int compare_value(void *value)
{
	return *((int *)value);
}

int setup_max(void **state)
{
	memset(sample_array, 0, sizeof(void *) * HEAP_SIZE);
	struct array_heap *heap = array_heap_init(
		sample_array, HEAP_SIZE, ARRAY_HEAP_MAX, compare_value);
	*state = heap;
	return 0;
}

int setup_min(void **state)
{
	memset(sample_array, 0, sizeof(void *) * HEAP_SIZE);
	struct array_heap *heap = array_heap_init(
		sample_array, HEAP_SIZE, ARRAY_HEAP_MIN, compare_value);
	*state = heap;
	return 0;
}

int teardown(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	array_heap_free(&heap);
	return 0;
}

void test_init_heap_null(void **state)
{
	struct array_heap *heap =
		array_heap_init(NULL, HEAP_SIZE, ARRAY_HEAP_MAX, compare_value);
	assert_null(heap);
	heap = array_heap_init(sample_array, HEAP_SIZE, ARRAY_HEAP_MAX, NULL);
	assert_null(heap);
}

void test_init_heap(void **state)
{
	struct array_heap *heap = array_heap_init(
		sample_array, HEAP_SIZE, ARRAY_HEAP_MAX, compare_value);
	assert_non_null(heap);
	*state = heap;
}

void test_free_heap_null(void **state)
{
	struct array_heap *heap = NULL;
	array_heap_free(NULL);
	array_heap_free(&heap);
}

void test_free_heap(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	array_heap_free(&heap);
	assert_null(heap);
}

void test_insert_heap_null(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	array_heap_insert(NULL, NULL);
	array_heap_insert(heap, NULL);
}

void test_insert_heap_max(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	int elements[3] = { 1, 2, 3 };
	int expected[3] = { 3, 1, 2 };
	for (int i = 0; i < 3; i++)
		array_heap_insert(heap, &elements[i]);
	for (int i = 0; i < 3; i++)
		assert_int_equal(expected[i], *((int *)sample_array[i]));
}

void test_insert_heap_min(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	int elements[3] = { 3, 1, 2 };
	int expected[3] = { 1, 3, 2 };
	for (int i = 0; i < 3; i++)
		array_heap_insert(heap, &elements[i]);
	for (int i = 0; i < 3; i++)
		assert_int_equal(expected[i], *((int *)sample_array[i]));
}

void test_insert_heap_overflow(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	int elements[3] = { 1, 2, 3 };
	int expected[3] = { 3, 1, 2 };
	int insert_overflow = 5;
	for (int i = 0; i < 3; i++)
		array_heap_insert(heap, &elements[i]);
	array_heap_insert(heap, &insert_overflow);
	for (int i = 0; i < 3; i++)
		assert_int_equal(expected[i], *((int *)sample_array[i]));
}

void test_delete_heap_null(void **state)
{
	void *deleted = array_heap_delete(NULL);
	assert_null(deleted);
}

void test_delete_heap_empty(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	void *deleted = NULL;
	deleted = array_heap_delete(heap);
	assert_null(deleted);
}

void test_delete_heap(void **state)
{
	struct array_heap *heap = (struct array_heap *)*state;
	int elements[3] = { 1, 2, 3 };
	int expected[3] = { 2, 1 };
	void *deleted = NULL;
	for (int i = 0; i < 3; i++)
		array_heap_insert(heap, &elements[i]);
	deleted = array_heap_delete(heap);
	for (int i = 0; i < 2; i++)
		assert_int_equal(expected[i], *((int *)sample_array[i]));
	assert_non_null(deleted);
	assert_int_equal(*((int *)deleted), 3);
}

void test_heapify_null(void **state)
{
	array_heap_heapify(NULL);
}

void test_heapify(void **state)
{
	int one = 1;
	int two = 2;
	int three = 3;
	int four = 4;
	int five = 5;
	void *to_heapify[5] = { &five, &one, &two, &four, &three };
	struct array_heap *heap =
		array_heap_init(to_heapify, 5, ARRAY_HEAP_MAX, compare_value);
	int expected[5] = { 5, 4, 2, 1, 3 };
	array_heap_heapify(heap);
	for (int i = 0; i < 5; i++)
		assert_int_equal(expected[i], *((int *)to_heapify[i]));
	*state = heap;
}

void test_heap_sort_null(void **state)
{
	array_heap_sort(NULL);
}

void test_heap_sort(void **state)
{
	int one = 1;
	int two = 2;
	int three = 3;
	int four = 4;
	int five = 5;
	void *to_sort[5] = { &two, &five, &three, &four, &one };
	struct array_heap *heap =
		array_heap_init(to_sort, 5, ARRAY_HEAP_MAX, compare_value);
	array_heap_sort(heap);
	for (int i = 0; i < 5; i++)
		assert_int_equal(*((int *)to_sort[i]), i + 1);
	*state = heap;
}

int main(void)
{
	struct CMUnitTest tests[] = {
		cmocka_unit_test(test_init_heap_null),
		cmocka_unit_test_teardown(test_init_heap, teardown),
		cmocka_unit_test(test_free_heap_null),
		cmocka_unit_test_setup(test_free_heap, setup_max),
		cmocka_unit_test_setup_teardown(test_insert_heap_null,
						setup_max, teardown),
		cmocka_unit_test_setup_teardown(test_insert_heap_max, setup_max,
						teardown),
		cmocka_unit_test_setup_teardown(test_insert_heap_min, setup_min,
						teardown),
		cmocka_unit_test_setup_teardown(test_insert_heap_overflow,
						setup_max, teardown),
		cmocka_unit_test(test_delete_heap_null),
		cmocka_unit_test_setup_teardown(test_delete_heap_empty,
						setup_max, teardown),
		cmocka_unit_test_setup_teardown(test_delete_heap, setup_max,
						teardown),
		cmocka_unit_test(test_heapify_null),
		cmocka_unit_test_teardown(test_heapify, teardown),
		cmocka_unit_test(test_heap_sort_null),
		cmocka_unit_test_teardown(test_heap_sort, teardown),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
