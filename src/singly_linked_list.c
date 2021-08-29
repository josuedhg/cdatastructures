#include <stdlib.h>
#include <assert.h>

#include "singly_linked_list.h"
#include "node_i.h"

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

struct singly_linked_list {
	struct singly_linked_node *head;
	struct singly_linked_node *tail;
	int length;
};

struct singly_linked_list *singly_linked_list_init()
{
	struct singly_linked_list *list = (struct singly_linked_list *)calloc(1, sizeof(struct singly_linked_list));
	return list;
}

int singly_linked_list_empty(struct singly_linked_list *list)
{
	return list->length == 0;
}

struct singly_linked_node *singly_linked_list_get_head(struct singly_linked_list *list)
{
	assert(list != NULL);
	return list->head;
}

struct singly_linked_node *singly_linked_list_get_tail(struct singly_linked_list *list)
{
	assert(list != NULL);
	return list->tail;
}

void singly_linked_list_prepend(struct singly_linked_list *list, void *data)
{
	assert(list != NULL);
	struct singly_linked_node *node = build_singly_linked_node(data);
	if (singly_linked_list_empty(list))
		list->tail = node;
	else
		node->next = list->head;
	list->head = node;
	list->length++;
}

void singly_linked_list_append(struct singly_linked_list *list, void *data)
{
	assert(list != NULL);
	struct singly_linked_node *node = build_singly_linked_node(data);
	if (singly_linked_list_empty(list))
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->length++;
}

static int default_search(void *data1, void *data2)
{
	return data1 == data2;
}

int singly_linked_list_insert_after(struct singly_linked_list *list, void *data, void *after, search_fn search)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return -1;

	if (search == NULL)
		search = default_search;

	struct singly_linked_node *node = build_singly_linked_node(data);
	struct singly_linked_node *current = list->head;
	if (search(list->tail->data, after)) {
		list->tail->next = node;
		list->tail = node;
	} else {
		while(current) {
			if (search(current->data, after)) break;
			current = current->next;
		}
		if (current == NULL) return -1;
		if (current->next != NULL) node->next = current->next;
		current->next = node;
	}
	list->length++;
	return 0;
}

void *singly_linked_list_delete_first(struct singly_linked_list *list)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;
	struct singly_linked_node *node = list->head;
	void *data = list->head->data;
	if (list->length == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else
		list->head = list->head->next;
	free(node);
	list->length--;
	return data;
}

static struct singly_linked_node *get_previous(struct singly_linked_list *list, struct singly_linked_node *node)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;
	if (list->length == 1)
		return NULL;
	struct singly_linked_node *prev = list->head;
	while(prev->next != node) prev = prev->next;
	return prev;
}

void *singly_linked_list_delete_last(struct singly_linked_list *list)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;
	struct singly_linked_node *node = list->tail;
	void *data = list->tail->data;
	if (list->length == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else
		list->tail = get_previous(list, list->tail);
	free(node);
	list->length--;
	return data;
}

void *singly_linked_list_delete(struct singly_linked_list *list, void *to_search, search_fn search)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;

	if (search == NULL)
		search = default_search;

	struct singly_linked_node *node = list->head;
	struct singly_linked_node *prev = NULL;
	void *data = NULL;
	if (search(list->head->data, to_search)) return singly_linked_list_delete_first(list);
	if (search(list->tail->data, to_search)) return singly_linked_list_delete_last(list);

	while(node)
	{
		if (search(node->data, to_search)) break;
		prev = node;
		node = node->next;
	}

	if (node == NULL) return NULL;
	if (prev != NULL) prev->next = node->next;

	data = node->data;
	free(node);
	node = NULL;
	list->length--;
	return data;
}

void *singly_linked_list_delete_nth(struct singly_linked_list *list, int nth)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;

	struct singly_linked_node *node = list->head;
	struct singly_linked_node *prev = NULL;
	void *data = NULL;
	int n = 0;

	if (nth == 0) return singly_linked_list_delete_first(list);
	if (nth == list->length - 1) return singly_linked_list_delete_last(list);

	while(node && n++ != nth) {
		prev = node;
		node = node->next;
	}
	if (node == NULL) return NULL;
	if (prev != NULL) prev->next = node->next;

	data = node->data;
	free(node);
	node = NULL;
	list->length--;
	return data;
}

void *singly_linked_list_get_nth(struct singly_linked_list *list, int nth)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return NULL;

	struct singly_linked_node *node = list->head;
	int n = 0;
	while(node && n++ != nth) node = node->next;
	if (node == NULL) return NULL;
	return node->data;
}

int singly_linked_list_get_size(struct singly_linked_list *list)
{
	assert(list != NULL);
	return list->length;
}

void singly_linked_list_free(struct singly_linked_list **list)
{
	assert(list != NULL && *list != NULL);
	if (!singly_linked_list_empty(*list))
		return;
	free(*list);
	*list = NULL;
}

void singly_linked_list_free_nodes(struct singly_linked_list *list)
{
	assert(list != NULL);
	if (singly_linked_list_empty(list))
		return;
	while(!singly_linked_list_empty(list)) singly_linked_list_delete_first(list);
}
