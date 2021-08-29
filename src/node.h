#ifndef __NODE_H__
#define __NODE_H__

struct singly_linked_node;
struct doubly_linked_node;

typedef int (*search_fn)(void *data1, void *data2);

/* Node operations */
void singly_linked_node_move_next(struct singly_linked_node **node);
void *singly_linked_node_get_data(struct singly_linked_node *node);

/* Node operations */
void doubly_linked_node_move_next(struct doubly_linked_node **node);
void doubly_linked_node_move_prev(struct doubly_linked_node **node);
void *doubly_linked_node_get_data(struct doubly_linked_node *node);


#endif /* end of include guard: __NODE_H__ */
