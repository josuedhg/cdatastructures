#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "btree.h"

int sample[] = { 2, 3, 4, 5, 1 };

struct collector {
	int collected[5];
	int collector_index;
};

struct collector delete_collector = { 0 };

static int search(void *a, void *b)
{
	return *((int *)a) - *((int *)b);
}

static void traversal_callback(void *data, void *user_data)
{
	int *node_data = (int *)data;
	struct collector *collector = (struct collector *)user_data;
	collector->collected[collector->collector_index++] = *node_data;
}

static void delete_fn(void *data)
{
	delete_collector.collected[delete_collector.collector_index++] =
		*((int *)data);
}

int setup(void **state)
{
	struct btree_node *root = NULL;
	for (int i = 0; i < 5; i++) {
		btree_insert(&root, &sample[i], search);
	}
	*state = root;
	return 0;
}

int teardown(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	btree_delete_nodes(&root, NULL);
	return 0;
}

void btree_insert_null(void **state)
{
	struct btree_node *root = NULL;
	expect_assert_failure(btree_insert(&root, NULL, NULL));
	expect_assert_failure(btree_insert(NULL, NULL, NULL));
}

void btree_insert_test(void **state)
{
	struct btree_node *root = NULL;
	int to_insert[5] = { 5, 2, 3, 1, 7 };
	for (int i = 0; i < 5; i++) {
		btree_insert(&root, &to_insert[i], search);
	}
	assert_int_equal(5, *((int *)root->data));
	assert_int_equal(2, *((int *)root->left->data));
	assert_int_equal(3, *((int *)root->left->right->data));
	assert_int_equal(1, *((int *)root->left->left->data));
	assert_int_equal(7, *((int *)root->right->data));
	*state = root;
}

void btree_delete_nodes_test(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	btree_delete_nodes(&root, NULL);
	assert_null(root);
}

void btree_delete_nodes_fn(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	int expected[] = { 1, 5, 4, 3, 2 };
	btree_delete_nodes(&root, delete_fn);
	assert_int_equal(delete_collector.collector_index, 5);
	for (int i = 0; i < 5; i++) {
		assert_int_equal(delete_collector.collected[i], expected[i]);
	}
	assert_null(root);
}

void btree_inorder_traversal_null(void **state)
{
	struct btree_node root;
	expect_assert_failure(btree_inorder_traversal(&root, NULL, NULL));
}

void btree_inorder_traversal_test(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	struct collector collector = { 0 };
	int expected[] = { 1, 2, 3, 4, 5 };
	btree_inorder_traversal(root, traversal_callback, &collector);
	assert_int_equal(collector.collector_index, 5);
	for (int i = 0; i < 5; i++) {
		assert_int_equal(collector.collected[i], expected[i]);
	}
}

void btree_preorder_traversal_null(void **state)
{
	struct btree_node root;
	expect_assert_failure(btree_preorder_traversal(&root, NULL, NULL));
}

void btree_preorder_traversal_test(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	struct collector collector = { 0 };
	int expected[] = { 2, 1, 3, 4, 5 };
	btree_preorder_traversal(root, traversal_callback, &collector);
	assert_int_equal(collector.collector_index, 5);
	for (int i = 0; i < 5; i++) {
		assert_int_equal(collector.collected[i], expected[i]);
	}
}

void btree_postorder_traversal_null(void **state)
{
	struct btree_node root;
	expect_assert_failure(btree_postorder_traversal(&root, NULL, NULL));
}

void btree_postorder_traversal_test(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	struct collector collector = { 0 };
	int expected[] = { 1, 5, 4, 3, 2 };
	btree_postorder_traversal(root, traversal_callback, &collector);
	assert_int_equal(collector.collector_index, 5);
	for (int i = 0; i < 5; i++) {
		assert_int_equal(collector.collected[i], expected[i]);
	}
}

void btree_search_null(void **state)
{
	expect_assert_failure(btree_search(NULL, NULL, NULL));
}

void btree_search_not_found(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	int target = 12;
	int *result = btree_search(root, &target, search);
	assert_null(result);
}

void btree_search_found(void **state)
{
	struct btree_node *root = (struct btree_node *)*state;
	int target = 3;
	int target2 = 1;
	int *result = btree_search(root, &target, search);
	assert_int_equal(*result, 3);
	result = btree_search(root, &target2, search);
	assert_int_equal(*result, 1);
}

int main()
{
	const struct CMUnitTest tests[] = {
		// Binary Tree tests
		cmocka_unit_test(btree_insert_null),
		cmocka_unit_test_teardown(btree_insert_test, teardown),
		cmocka_unit_test(btree_inorder_traversal_null),
		cmocka_unit_test_setup_teardown(btree_inorder_traversal_test,
						setup, teardown),
		cmocka_unit_test(btree_preorder_traversal_null),
		cmocka_unit_test_setup_teardown(btree_preorder_traversal_test,
						setup, teardown),
		cmocka_unit_test(btree_postorder_traversal_null),
		cmocka_unit_test_setup_teardown(btree_postorder_traversal_test,
						setup, teardown),
		cmocka_unit_test_setup(btree_delete_nodes_test, setup),
		cmocka_unit_test_setup(btree_delete_nodes_fn, setup),
		cmocka_unit_test(btree_search_null),
		cmocka_unit_test_setup_teardown(btree_search_not_found, setup,
						teardown),
		cmocka_unit_test_setup_teardown(btree_search_found, setup,
						teardown),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
