#include <stdlib.h>
#include <assert.h>

#include "node.h"
#include "node_i.h"

struct singly_linked_node *build_singly_linked_node(void *data)
{
	struct singly_linked_node *node =(struct singly_linked_node *)calloc(1, sizeof(struct singly_linked_node));
	node->data = data;
	return node;
}

void singly_linked_node_move_next(struct singly_linked_node **node)
{
	assert(node != NULL && *node != NULL);
	*node = (*node)->next;
}

void *singly_linked_node_get_data(struct singly_linked_node *node)
{
	assert(node != NULL);
	return node->data;
}

struct doubly_linked_node *build_doubly_linked_node(void *data)
{
	struct doubly_linked_node *node = calloc(1, sizeof(struct doubly_linked_node));
	node->data = data;
	return node;
}

void doubly_linked_node_move_next(struct doubly_linked_node **node)
{
	assert(node != NULL && *node != NULL);
	*node = (*node)->next;
}

void doubly_linked_node_move_prev(struct doubly_linked_node **node)
{
	assert(node != NULL && *node != NULL);
	*node = (*node)->prev;
}

void *doubly_linked_node_get_data(struct doubly_linked_node *node)
{
	assert(node != NULL);
	return node->data;
}

