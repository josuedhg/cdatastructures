#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__

#include "node.h"

struct singly_linked_list;

/* List operations */
struct singly_linked_list *singly_linked_list_init(void);
int singly_linked_list_empty(struct singly_linked_list *list);
struct singly_linked_node *singly_linked_list_get_head(struct singly_linked_list *list);
struct singly_linked_node *singly_linked_list_get_tail(struct singly_linked_list *list);
int singly_linked_list_get_size(struct singly_linked_list *list);
void singly_linked_list_free(struct singly_linked_list **list);
void singly_linked_list_free_nodes(struct singly_linked_list *list);
void *singly_linked_list_get_nth(struct singly_linked_list *list, int nth);

void singly_linked_list_prepend(struct singly_linked_list *list, void *data);
void singly_linked_list_append(struct singly_linked_list *list, void *data);
int singly_linked_list_insert_after(struct singly_linked_list *list, void *data, void *after, search_fn search);

void *singly_linked_list_delete_first(struct singly_linked_list *list);
void *singly_linked_list_delete_last(struct singly_linked_list *list);
void *singly_linked_list_delete(struct singly_linked_list *list, void *to_search, search_fn search);
void *singly_linked_list_delete_nth(struct singly_linked_list *list, int nth);

#endif /* end of include guard: __SINGLY_LINKED_LIST_H__ */
