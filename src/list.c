#include <stdlib.h>
#include <assert.h>
#include "list.h"

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

static struct list *build_list_node(void *data)
{
	struct list *node =(struct list *)calloc(1, sizeof(struct list));
	node->data = data;
	return node;
}

void list_prepend(struct list **head, void *data)
{
	assert(head != NULL);
	struct list *node = build_list_node(data);
	node->next = *head;
	*head = node;
}

void list_instert_after(struct list **head, void *data, void *after, search_fn search)
{
	assert(head != NULL);
	struct list *new = build_list_node(data);
	struct list *node = *head;
	if (!*head)
	{
		*head = new;
		return;
	}
	while(node)
	{
		if (search) {
			if (search(node, after)) break;
		} else if (node->data == after) break;
		node = node->next;
	}
	if (!node)
	{
		free(new);
		return;
	}
	if (node->next)
		new->next = node->next;
	node->next = new;
}

void list_append(struct list **head, void *data)
{
	assert(head != NULL);
	struct list *new = build_list_node(data);
	struct list *node = *head;
	if (!*head)
	{
		*head = new;
		return;
	}
	while(node->next) node = node->next;
	node->next = new;
}

void list_delete(struct list **head, void *data, search_fn search)
{
	assert(head != NULL);
	struct list *node = *head;
	struct list *prev = NULL;
	while(node)
	{
		if (search) {
			if (search(node, data)) break;
		} else if (node->data == data) break;
		prev = node;
		node = node->next;
	}
	if (!node)
		return;
	if (prev)
		prev->next = node->next;
	else
		*head = node->next;
	free(node);
	node = NULL;
}
void list_delete_nth(struct list **head, int nth)
{
	assert(head != NULL);
	struct list *node = *head;
	struct list *prev = NULL;
	int n = 0;
	while(node && n++ != nth) {
		prev = node;
		node = node->next;
	}
	if (!node)
		return;
	if (prev)
		prev->next = node->next;
	free(node);
	node = NULL;
}

void *list_get_nth(struct list *head, int nth)
{
	assert(head != NULL);
	struct list *node = head;
	int n = 0;
	while(node && n++ != nth) node = node->next;
	if (!node)
		return NULL;
	return node->data;
}
int list_size(struct list *head)
{
	assert(head != NULL);
	struct list *node = head;
	int n = 0;
	while(node) {node = node->next; n++;}
	return n;
}

void list_free(struct list **head)
{
	while(*head)
	{
		struct list *tmp = (*head)->next;
		free(*head);
		*head = NULL;
		*head = tmp;
	}
}
