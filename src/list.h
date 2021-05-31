#ifndef __LIST_H__
#define __LIST_H__

struct list
{
	struct list *next;
	void *data;
};

typedef int (*search_fn)(struct list *node, void *data);

void list_prepend(struct list **head, void *data);
void list_instert_after(struct list **head, void *data, void *after, search_fn search);
void list_append(struct list **head, void *data);

void list_delete(struct list **head, void *data, search_fn search);
void list_delete_nth(struct list **head, int nth);

void *list_get_nth(struct list *head, int nth);
int list_size(struct list *head);

void list_free(struct list **head);

#endif /* end of include guard: __LIST_H__ */
