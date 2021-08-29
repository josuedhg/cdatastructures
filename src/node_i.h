#ifndef __NODE_I_H__
#define __NODE_I_H__

struct singly_linked_node {
	void *data;
	struct singly_linked_node *next;
};

struct doubly_linked_node {
	void *data;
	struct doubly_linked_node *prev;
	struct doubly_linked_node *next;
};

struct singly_linked_node *build_singly_linked_node(void *data);
struct doubly_linked_node *build_doubly_linked_node(void *data);

#endif /* end of include guard: __NODE_I_H__ */
