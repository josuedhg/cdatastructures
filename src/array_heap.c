#include <stdlib.h>

#include "array_heap.h"

#define PARENT(i) ((i - 1) / 2)
#define LEFT_CHILD(i) ((2 * i) + 1)
#define RIGHT_CHILD(i) ((2 * i) + 2)

struct array_heap {
	get_value_fn get_value;
	void **heap_buffer;
	int heap_size;
	int buffer_size;
	enum heap_type type;
};

struct array_heap *array_heap_init(void **heap_buffer, int size,
				   enum heap_type type, get_value_fn get_value)
{
	if (heap_buffer == NULL || get_value == NULL)
		return NULL;

	struct array_heap *heap =
		(struct array_heap *)calloc(1, sizeof(struct array_heap));
	heap->get_value = get_value;
	heap->heap_buffer = heap_buffer;
	heap->buffer_size = size;
	heap->type = type;
	return heap;
}

void array_heap_free(struct array_heap **heap)
{
	if (heap == NULL || *heap == NULL)
		return;
	free(*heap);
	*heap = NULL;
}

static int compare(struct array_heap *heap, void *value1, void *value2)
{
	if (heap->type == ARRAY_HEAP_MAX) {
		return heap->get_value(value1) - heap->get_value(value2);
	} else {
		return heap->get_value(value2) - heap->get_value(value1);
	}
}

void array_heap_insert(struct array_heap *heap, void *data)
{
	if (heap == NULL || data == NULL)
		return;
	if (heap->heap_size >= heap->buffer_size)
		return;
	int index = heap->heap_size;
	heap->heap_buffer[index] = data;
	while (index > 0 && compare(heap, heap->heap_buffer[index],
				    heap->heap_buffer[PARENT(index)]) > 0) {
		heap->heap_buffer[index] = heap->heap_buffer[PARENT(index)];
		index = PARENT(index);
	}
	heap->heap_buffer[index] = data;
	heap->heap_size++;
}

static void array_heap_ajust(struct array_heap *heap, int index,
			     int buffer_size)
{
	void *temp = heap->heap_buffer[index];
	int j = LEFT_CHILD(index);
	while (j <= buffer_size - 1) {
		if (j < buffer_size - 1 &&
		    compare(heap, heap->heap_buffer[j + 1],
			    heap->heap_buffer[j]) > 0)
			j = j + 1;

		if (compare(heap, temp, heap->heap_buffer[j]) >= 0)
			break;

		heap->heap_buffer[PARENT(j)] = heap->heap_buffer[j];
		j = LEFT_CHILD(j);
	}
	heap->heap_buffer[PARENT(j)] = temp;
}

void *array_heap_delete(struct array_heap *heap)
{
	if (heap == NULL)
		return NULL;
	void *ret = heap->heap_buffer[0];
	heap->heap_buffer[0] = heap->heap_buffer[heap->heap_size - 1];
	heap->heap_size--;

	array_heap_ajust(heap, 0, heap->heap_size);

	return ret;
}

void array_heap_heapify(struct array_heap *heap)
{
	if (heap == NULL)
		return;
	for (int i = PARENT(heap->buffer_size - 1); i >= 0; i--)
		array_heap_ajust(heap, i, heap->buffer_size);
}

void array_heap_sort(struct array_heap *heap)
{
	if (heap == NULL)
		return;
	heap->heap_size = heap->buffer_size;
	array_heap_heapify(heap);
	for (int i = heap->buffer_size; i > 0; i--) {
		void *tmp = array_heap_delete(heap);
		heap->heap_buffer[i - 1] = tmp;
	}
}
