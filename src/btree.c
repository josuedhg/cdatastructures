#include <stdlib.h>
#include <assert.h>

#include "btree.h"

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char *const expression,
			const char *const file, const int line);
#undef assert
#define assert(expression)                                                     \
	mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

void btree_insert(struct btree_node **root, void *data, btree_search_fn search)
{
	assert(root != NULL);
	assert(data != NULL);
	if (*root == NULL) {
		*root = calloc(1, sizeof(struct btree_node));
		(*root)->data = data;
	} else {
		int result = search((*root)->data, data);
		if (result > 0)
			btree_insert(&(*root)->left, data, search);
		else if (result < 0)
			btree_insert(&(*root)->right, data, search);
	}
}

void btree_inorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			     void *user_data)
{
	assert(fn != NULL);
	if (root == NULL)
		return;
	btree_inorder_traversal(root->left, fn, user_data);
	fn(root->data, user_data);
	btree_inorder_traversal(root->right, fn, user_data);
}

void btree_preorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			      void *user_data)
{
	assert(fn != NULL);
	if (root == NULL)
		return;
	fn(root->data, user_data);
	btree_preorder_traversal(root->left, fn, user_data);
	btree_preorder_traversal(root->right, fn, user_data);
}

void btree_postorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			       void *user_data)
{
	assert(fn != NULL);
	if (root == NULL)
		return;
	btree_postorder_traversal(root->left, fn, user_data);
	btree_postorder_traversal(root->right, fn, user_data);
	fn(root->data, user_data);
}

void btree_delete_nodes(struct btree_node **root, btree_delete_fn fn)
{
	if (*root == NULL)
		return;
	btree_delete_nodes(&(*root)->left, fn);
	btree_delete_nodes(&(*root)->right, fn);
	if (fn != NULL)
		fn((*root)->data);
	free(*root);
	*root = NULL;
}

void *btree_search(struct btree_node *root, void *target,
		   btree_search_fn search)
{
	assert(target != NULL && search != NULL);
	if (root == NULL)
		return NULL;
	int result = search(root->data, target);
	if (result == 0)
		return root->data;
	else if (result > 0)
		return btree_search(root->left, target, search);
	else if (result < 0)
		return btree_search(root->right, target, search);
	return NULL;
}
