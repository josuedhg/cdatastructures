#include <stdlib.h>
#include <assert.h>

#include "doubly_linked_list.h"
#include "node_i.h"

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

struct doubly_linked_list {
	int length;
	struct doubly_linked_node *head;
	struct doubly_linked_node *tail;
};

struct doubly_linked_list *doubly_linked_list_init()
{
	struct doubly_linked_list *list = (struct doubly_linked_list *)calloc(1, sizeof(struct doubly_linked_list));
	return list;
}

void doubly_linked_list_free(struct doubly_linked_list **list)
{
	if (*list == NULL) return;
	free(*list);
	*list = NULL;
}

/* List operations */
int doubly_linked_list_empty(struct doubly_linked_list *list)
{
	assert(list != NULL);
	return list->length == 0;
}

struct doubly_linked_node *doubly_linked_list_get_head(struct doubly_linked_list *list)
{
	assert(list != NULL);
	return list->head;
}

struct doubly_linked_node *doubly_linked_list_get_tail(struct doubly_linked_list *list)
{
	assert(list != NULL);
	return list->tail;
}

int doubly_linked_list_get_size(struct doubly_linked_list *list)
{
	assert(list != NULL);
	return list->length;
}

void doubly_linked_list_free_nodes(struct doubly_linked_list *list)
{
	assert(list != NULL);
	while (!doubly_linked_list_empty(list)) doubly_linked_list_delete_first(list);
}

void *doubly_linked_list_get_nth(struct doubly_linked_list *list, int nth)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return NULL;
	struct doubly_linked_node *node = list->head;
	while(node != NULL && nth--) node = node->next;
	if (node == NULL)
		return NULL;
	return node->data;
}

void doubly_linked_list_prepend(struct doubly_linked_list *list, void *data)
{
	assert(list != NULL);
	struct doubly_linked_node *node = build_doubly_linked_node(data);
	if (doubly_linked_list_empty(list)) {
		list->tail = node;
	} else {
		node->next = list->head;
		list->head->prev = node;
	}
	list->head = node;
	list->length++;
}

void doubly_linked_list_append(struct doubly_linked_list *list, void *data)
{
	assert(list != NULL);
	struct doubly_linked_node *node = build_doubly_linked_node(data);
	if (doubly_linked_list_empty(list)) {
		list->head = node;
	} else {
		node->prev = list->tail;
		list->tail->next = node;
	}
	list->tail = node;
	list->length++;
}

static int default_search(void *data1, void *data2)
{
	return data1 == data2;
}

int doubly_linked_list_insert_after(struct doubly_linked_list *list, void *data, void *after, search_fn search)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return -1;
	if (search == NULL)
		search = default_search;
	struct doubly_linked_node *node = build_doubly_linked_node(data);
	struct doubly_linked_node *current = list->head;
	if (search(list->tail->data, after)) {
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	} else {
		while(current) {
			if (search(current->data, after)) break;
			current = current->next;
		}
		if (current == NULL) {
			free(node);
			return -1;
		}
		if (current->next != NULL) {
			current->next->prev = node;
			node->next = current->next;
		}
		node->prev = current;
		current->next = node;
	}
	list->length++;
	return 0;
}

int doubly_linked_list_insert_before(struct doubly_linked_list *list, void *data, void *after, search_fn search)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return -1;
	if (search == NULL)
		search = default_search;
	struct doubly_linked_node *node = build_doubly_linked_node(data);
	struct doubly_linked_node *current = list->head;
	if (search(list->head->data, after)) {
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	} else {
		while(current) {
			if (search(current->data, after)) break;
			current = current->next;
		}
		if (current == NULL) {
			free(node);
			return -1;
		}
		if (current->next != NULL) {
			current->prev->next = node;
			node->prev = current->prev;
		}
		node->next = current;
		current->prev = node;
	}
	list->length++;
	return 0;
}

void *doubly_linked_list_delete_first(struct doubly_linked_list *list)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return NULL;
	struct doubly_linked_node *node = list->head;
	void *data = list->head->data;
	if (list->length == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->head = node->next;
		if (node->next)
			node->next->prev = NULL;
	}
	free(node);
	list->length--;
	return data;
}

void *doubly_linked_list_delete_last(struct doubly_linked_list *list)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return NULL;
	struct doubly_linked_node *node = list->tail;
	void *data = list->tail->data;
	if (list->length == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->tail = node->prev;
		if (node->prev)
			node->prev->next = NULL;
	}
	free(node);
	list->length--;
	return data;
}
void *doubly_linked_list_delete(struct doubly_linked_list *list, void *to_search, search_fn search)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return NULL;
	if (search == NULL)
		search = default_search;
	struct doubly_linked_node *node = list->head;
	void *data = NULL;
	if (search(list->head->data, to_search)) return doubly_linked_list_delete_first(list);
	if (search(list->tail->data, to_search)) return doubly_linked_list_delete_last(list);

	while(node)
	{
		if (search(node->data, to_search)) break;
		node = node->next;
	}

	if (node == NULL) return NULL;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;

	data = node->data;
	free(node);
	node = NULL;
	list->length--;
	return data;
}

void *doubly_linked_list_delete_nth(struct doubly_linked_list *list, int nth)
{
	assert(list != NULL);
	if (doubly_linked_list_empty(list))
		return NULL;

	struct doubly_linked_node *node = list->head;
	void *data = NULL;
	int n = 0;

	if (nth == 0) return doubly_linked_list_delete_first(list);
	if (nth == list->length - 1) return doubly_linked_list_delete_last(list);

	while (node && n++ != nth) node = node->next;

	if (node == NULL) return NULL;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;

	data = node->data;
	free(node);
	node = NULL;
	list->length--;
	return data;
}
