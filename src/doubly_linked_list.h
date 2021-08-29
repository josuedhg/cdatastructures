#ifndef __DOUBLY_LINKED_LIST__
#define __DOUBLY_LINKED_LIST__

#include "node.h"

struct doubly_linked_list;

/* List operations */
struct doubly_linked_list *doubly_linked_list_init(void);
int doubly_linked_list_empty(struct doubly_linked_list *list);
struct doubly_linked_node *doubly_linked_list_get_head(struct doubly_linked_list *list);
struct doubly_linked_node *doubly_linked_list_get_tail(struct doubly_linked_list *list);
int doubly_linked_list_get_size(struct doubly_linked_list *list);
void doubly_linked_list_free(struct doubly_linked_list **list);
void doubly_linked_list_free_nodes(struct doubly_linked_list *list);
void *doubly_linked_list_get_nth(struct doubly_linked_list *list, int nth);

void doubly_linked_list_prepend(struct doubly_linked_list *list, void *data);
void doubly_linked_list_append(struct doubly_linked_list *list, void *data);
int doubly_linked_list_insert_after(struct doubly_linked_list *list, void *data, void *after, search_fn search);
int doubly_linked_list_insert_before(struct doubly_linked_list *list, void *data, void *after, search_fn search);

void *doubly_linked_list_delete_first(struct doubly_linked_list *list);
void *doubly_linked_list_delete_last(struct doubly_linked_list *list);
void *doubly_linked_list_delete(struct doubly_linked_list *list, void *to_search, search_fn search);
void *doubly_linked_list_delete_nth(struct doubly_linked_list *list, int nth);

#endif /* end of include guard: __DOUBLY_LINKED_LIST__ */
