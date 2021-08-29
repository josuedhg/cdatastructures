#include <stdlib.h>
#include <assert.h>

#include "circular_linked_list.h"
#include "node_i.h"

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

struct circular_linked_list {
	struct singly_linked_node *tail;
	int length;
};

/* List operations */
struct circular_linked_list *circular_linked_list_init(void)
{
	struct circular_linked_list *list = (struct circular_linked_list *)calloc(1, sizeof(struct circular_linked_list));
	return list;
}

int circular_linked_list_empty(struct circular_linked_list *list)
{
	assert(list != NULL);
	return list->length == 0;
}

struct singly_linked_node *circular_linked_list_get_head(struct circular_linked_list *list)
{
	assert(list != NULL);
	if (list->tail == NULL) return NULL;
	return list->tail->next;
}

struct singly_linked_node *circular_linked_list_get_tail(struct circular_linked_list *list)
{
	assert(list != NULL);
	return list->tail;
}

int circular_linked_list_get_size(struct circular_linked_list *list)
{
	assert(list != NULL);
	return list->length;
}

void circular_linked_list_free(struct circular_linked_list **list)
{
	assert(list != NULL && *list != NULL);
	if (!circular_linked_list_empty(*list))
		return;
	free(*list);
	*list = NULL;
}

void *circular_linked_list_get_nth(struct circular_linked_list *list, int nth)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return NULL;
	struct singly_linked_node *node = list->tail->next;
	int done = 0;
	while (!done) {
		if (!(--nth)) break;
		done = node == list->tail;
		if (!done)
			node = node->next;
	}
	if (nth > 0)
		return NULL;
	return node->data;
}

void circular_linked_list_prepend(struct circular_linked_list *list, void *data)
{
	assert(list != NULL);
	struct singly_linked_node *new = build_singly_linked_node(data);
	if (circular_linked_list_empty(list)) {
		list->tail = new;
		list->tail->next = list->tail;
	} else {
		new->next = list->tail->next;
		list->tail->next = new;
	}
	list->length++;
}

void circular_linked_list_append(struct circular_linked_list *list, void *data)
{
	assert(list != NULL);
	struct singly_linked_node *new = build_singly_linked_node(data);
	if (circular_linked_list_empty(list)) {
		list->tail = new;
		list->tail->next = list->tail;
	} else {
		new->next = list->tail->next;
		list->tail->next = new;
		list->tail = list->tail->next;
	}
	list->length++;
}

static int default_search(void *data1, void *data2)
{
	return data1 == data2;
}

int circular_linked_list_insert_after(struct circular_linked_list *list, void *data, void *after, search_fn search)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return -1;
	if (search == NULL)
		search = default_search;
	struct singly_linked_node *new = build_singly_linked_node(data);
	struct singly_linked_node *node = list->tail->next;
	int done = 0;
	while (!done) {
		if (search(node->data, after)) break;
		done = node == list->tail;
		if (!done)
			node = node->next;
	}
	if (done) {
		free(new);
		return -1;
	}
	new->next = node->next;
	node->next = new;
	list->length++;
	return 0;
}

void *circular_linked_list_delete_first(struct circular_linked_list *list)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return NULL;
	if (list->tail == NULL)
		return NULL;

	struct singly_linked_node *node = list->tail->next;
	void *data = node->data;
	if (node == list->tail) {
		list->tail = NULL;
	} else {
		list->tail->next = node->next;
	}
	free(node);
	list->length--;
	return data;
}

void *circular_linked_list_delete_last(struct circular_linked_list *list)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return NULL;
	struct singly_linked_node *node = list->tail->next;
	void *data = list->tail->data;
	if (node == list->tail) {
		list->tail = NULL;
	} else {
		struct singly_linked_node *last = list->tail->next;
		while(last->next != list->tail) last = last->next;
		last->next = node->next;
	}
	free(node);
	list->length--;
	return data;
}

void circular_linked_list_free_nodes(struct circular_linked_list *list)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return;
	while(!circular_linked_list_empty(list))
		circular_linked_list_delete_first(list);
}

void *circular_linked_list_delete(struct circular_linked_list *list, void *to_search, search_fn search)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return NULL;
	if (search == NULL)
		search = default_search;
	struct singly_linked_node *prev = list->tail;
	struct singly_linked_node *node = list->tail->next;
	void *data = node->data;
	if (node == list->tail && search(node->data, to_search))
		list->tail = NULL;
	else {
		int done = 0;
		while (!done) {
			if (search(node->data, to_search)) break;
			done = node == list->tail;
			if (!done) {
				prev = node;
				node = node->next;
			}
		}
		if (done)
			return NULL;
		prev->next = node->next;
	}
	free(node);
	list->length--;
	return data;
}

void *circular_linked_list_delete_nth(struct circular_linked_list *list, int nth)
{
	assert(list != NULL);
	if (circular_linked_list_empty(list))
		return NULL;
	struct singly_linked_node *prev = list->tail;
	struct singly_linked_node *node = list->tail->next;
	void *data = NULL;
	if (node == list->tail && nth == 1)
	{
		list->tail = NULL;
	} else {
		int done = 0;
		while (!done) {
			if (!(--nth)) break;
			done = node == list->tail;
			if (!done) {
				prev = node;
				node = node->next;
			}
		}
		if (nth > 0) return NULL;
	}
	prev->next = node->next;
	data = node->data;
	free(node);
	list->length--;
	return data;
}
