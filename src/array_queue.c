#include <stdlib.h>
#include <assert.h>

#include "array_queue.h"

#define INITIAL_VAL -1

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

int array_queue_enqueue(struct array_queue *queue, void *item)
{
	assert(queue != NULL);
	if (queue->amount >= queue->buffer_len)
		return -1;
	queue->buffer[(++queue->rear)%queue->buffer_len] = item;
	queue->amount++;
	if (queue->front == -1)
		queue->front = queue->rear;
	return 0;
}

void *array_queue_dequeue(struct array_queue *queue)
{
	assert(queue != NULL);
	if (array_queue_empty(queue))
		return NULL;
	queue->amount--;
	return queue->buffer[(queue->front++)%queue->buffer_len];
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
	return queue->buffer[queue->rear];
}

int array_queue_empty(struct array_queue *queue)
{
	assert(queue != NULL);
	return queue->amount == 0;
}

void array_queue_free(struct array_queue **queue)
{
	if (*queue == NULL)return;
	free((*queue)->buffer);
	free(*queue);
	*queue = NULL;
}
