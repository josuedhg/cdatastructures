#ifndef __BTREE_H__
#define __BTREE_H__

typedef int (*btree_search_fn)(void *, void *);
typedef void (*btree_travesal_fn)(void *, void *);
typedef void (*btree_delete_fn)(void *);

struct btree_node {
	void *data;
	struct btree_node *left;
	struct btree_node *right;
};

void btree_insert(struct btree_node **root, void *data, btree_search_fn search);
void btree_inorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			     void *user_data);
void btree_preorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			      void *user_data);
void btree_postorder_traversal(struct btree_node *root, btree_travesal_fn fn,
			       void *user_data);
void btree_delete_nodes(struct btree_node **root, btree_delete_fn fn);
void *btree_search(struct btree_node *root, void *target,
		   btree_search_fn search);

#endif /* end of include guard: __BTREE_H__ */
