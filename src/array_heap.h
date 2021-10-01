#ifndef __ARRAY_HEAP_H__
#define __ARRAY_HEAP_H__

struct array_heap;

enum heap_type { ARRAY_HEAP_MAX, ARRAY_HEAP_MIN };

typedef int (*get_value_fn)(void *);

struct array_heap *array_heap_init(void **, int size, enum heap_type,
				   get_value_fn);
void array_heap_free(struct array_heap **);
void array_heap_insert(struct array_heap *, void *);
void *array_heap_delete(struct array_heap *);
void array_heap_heapify(struct array_heap *);
void array_heap_sort(struct array_heap *);

#endif /* end of include guard: __ARRAY_HEAP_H__ */
