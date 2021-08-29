#ifndef __CIRCULAR_LINKED_LIST_H__
#define __CIRCULAR_LINKED_LIST_H__

#include "node.h"

struct circular_linked_list;

/* List operations */
struct circular_linked_list *circular_linked_list_init(void);
int circular_linked_list_empty(struct circular_linked_list *list);
struct singly_linked_node *circular_linked_list_get_head(struct circular_linked_list *list);
struct singly_linked_node *circular_linked_list_get_tail(struct circular_linked_list *list);
int circular_linked_list_get_size(struct circular_linked_list *list);
void circular_linked_list_free(struct circular_linked_list **list);
void circular_linked_list_free_nodes(struct circular_linked_list *list);
void *circular_linked_list_get_nth(struct circular_linked_list *list, int nth);

void circular_linked_list_prepend(struct circular_linked_list *list, void *data);
void circular_linked_list_append(struct circular_linked_list *list, void *data);
int circular_linked_list_insert_after(struct circular_linked_list *list, void *data, void *after, search_fn search);

void *circular_linked_list_delete_first(struct circular_linked_list *list);
void *circular_linked_list_delete_last(struct circular_linked_list *list);
void *circular_linked_list_delete(struct circular_linked_list *list, void *to_search, search_fn search);
void *circular_linked_list_delete_nth(struct circular_linked_list *list, int nth);

#endif /* end of include guard: __CIRCULAR_LINKED_LIST_H__ */
