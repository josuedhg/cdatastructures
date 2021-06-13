#include <stdlib.h>
#include <assert.h>

#include "array_queue.h"

#define INITIAL_VAL 0

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

struct array_queue
{
	void **buffer;
	int buffer_len;
	int front;
	int rear;
	int amount;
};

static int array_queue_next_index(int index, int len)
{
	return (index + 1) % len;
}

static int array_queue_previous_index(int index, int len)
{
	if (index == 0)
		return len - 1;
	return index - 1;
}

struct array_queue *array_queue_init(int queue_size)
{
	struct array_queue *queue = (struct array_queue *)malloc(sizeof(struct array_queue));
	queue->buffer = calloc(queue_size, sizeof(void *));
	queue->buffer_len = queue_size;
	queue->front = INITIAL_VAL;
	queue->rear = INITIAL_VAL;
	queue->amount = 0;
	return queue;
}

int array_queue_push_back(struct array_queue *queue, void *item)
{
	assert(queue != NULL);
	if (array_queue_full(queue))
		return -1;
	queue->buffer[queue->rear] = item;
	queue->rear = array_queue_next_index(queue->rear, queue->buffer_len);
	queue->amount++;
	return 0;
}

int array_queue_push_front(struct array_queue *queue, void *item)
{
	assert(queue!= NULL);
	if (array_queue_full(queue))
		return -1;
	queue->front = array_queue_previous_index(queue->front, queue->buffer_len);
	queue->buffer[queue->front] = item;
	queue->amount++;
	return 0;
}

int array_queue_enqueue(struct array_queue *queue, void *item)
{
	return array_queue_push_back(queue, item);
}

void *array_queue_pop_back(struct array_queue *queue)
{
	assert(queue != NULL);
	if (array_queue_empty(queue))
		return NULL;
	queue->rear = array_queue_previous_index(queue->rear, queue->buffer_len);
	void *value = queue->buffer[queue->rear];
	queue->amount--;
	return value;
}

void *array_queue_pop_front(struct array_queue *queue)
{
	assert(queue != NULL);
	if (array_queue_empty(queue))
		return NULL;
	void *value = queue->buffer[queue->front];
	queue->front = array_queue_next_index(queue->front, queue->buffer_len);
	queue->amount--;
	return value;
}

void *array_queue_dequeue(struct array_queue *queue)
{
	return array_queue_pop_front(queue);
}

void *array_queue_front(struct array_queue *queue)
{
	assert(queue != NULL);
	if (array_queue_empty(queue))
		return NULL;
	return queue->buffer[queue->front];
}

void *array_queue_rear(struct array_queue *queue)
{
	assert(queue != NULL);
	if (array_queue_empty(queue))
		return NULL;
	return queue->buffer[array_queue_previous_index(queue->rear, queue->buffer_len)];
}

int array_queue_empty(struct array_queue *queue)
{
	assert(queue != NULL);
	return queue->amount == 0;
}

int array_queue_full(struct array_queue *queue)
{
	assert(queue != NULL);
	return queue->amount >= queue->buffer_len;
}

void array_queue_free(struct array_queue **queue)
{
	if (*queue == NULL)return;
	free((*queue)->buffer);
	free(*queue);
	*queue = NULL;
}
